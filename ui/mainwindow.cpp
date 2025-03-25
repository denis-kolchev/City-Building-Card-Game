#include "mainwindow.h"
#include "../logic/diceroller.h"

#include <QDir>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include <QVector>

#include <QTabWidget>
#include <QtWidgets/qapplication.h>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , m_stateMachine(new QStateMachine(this))
    , m_incomeState(new QState())
    , m_buyingState(new QState())
    , m_buyOrRerollState(new QState())
    , m_finalState(new QFinalState())
    , m_centralWidget(new QWidget(this))
    , m_mainLayout(new QHBoxLayout(m_centralWidget))
    , m_bankCardsArea(new QScrollArea())
    , m_bankScrollWidget(new CardScrollWidget())
    , m_bankLayout(new QHBoxLayout())
    , m_tabWidget(new QTabWidget(this))
    , m_canPressTwoDiceButton(5, 0)
    , m_canBuildAgainIfDubleRollDice(5, 0)
    , m_canRerollDice(5, 0)
{
    m_bankCardsArea->setWidget(m_bankScrollWidget);
    m_bankCardsArea->setWidgetResizable(true);

    m_mainLayout->addWidget(m_bankCardsArea);
    m_mainLayout->addWidget(m_tabWidget);

    m_centralWidget->setLayout(m_mainLayout);

    // Animation of cards when in buy state depending on palyer balance
    connect(this, &MainWindow::activateCardsHighlighting, m_bankScrollWidget,
            [this](int playerBalance) { emit m_bankScrollWidget->activateCardsHighlighting(playerBalance); });

    connect(this, &MainWindow::deactivateCardsHighlighting, m_bankScrollWidget,
            [this](){ emit m_bankScrollWidget->deactivateCardsHighlighting(); });

    connect(this, &MainWindow::skipClicked, m_bankScrollWidget,
            [this](){ emit m_bankScrollWidget->deactivateCardsHighlighting(); });
    // Animation end

    // handle card clickes
    connect(m_bankScrollWidget, &CardScrollWidget::cardSignalClicked,
            this, &MainWindow::handleCardClick);

    setCentralWidget(m_centralWidget);

    setWindowTitle("City Building Card Game");
    resize(1366, 768);
}

MainWindow::~MainWindow()
{
}

CardScrollWidget* MainWindow::getBankScrollWidget() const
{
    return m_bankScrollWidget;
}

bool MainWindow::askForReroll(QWidget* parent)
{
    QString question = QString("Does the Player %1 want to re-roll the dice?")
    .arg(char(m_currentPlayerId + 'A'));

    QMessageBox msgBox(parent);
    msgBox.setWindowTitle("Re-roll?");
    msgBox.setText(question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    return msgBox.exec() == QMessageBox::Yes;
}

void MainWindow::displayBankGetsCard(std::shared_ptr<Card> card)
{
    if (card->activationValues().contains(0)) {
        for (int i = 0; i < m_numPlayers; ++i) {
            m_playerPages[i]->placeCards(CardList{card});
        }
    } else {
        m_bankScrollWidget->placeCards(CardList{card});
    }
}

void MainWindow::displayBankLoosesCard(std::shared_ptr<Card> card)
{
    m_bankScrollWidget->removeCards(CardList{card});
}

void MainWindow::displayPlayerGetsCard(int playerId, std::shared_ptr<Card> card)
{
    emit deactivateCardsHighlighting(); // problem with playerId
    // TODO stop handling playerID
    m_playerPages.at(playerId)->placeCards(CardList{card});

    if (m_canBuildAgainIfDubleRollDice[playerId]) {
        m_canBuildAgainIfDubleRollDice[playerId] = false;
        emit buildOneMoreBuilding();
    } else {
        emit updatedPlayersPanel();
    }
}

void MainWindow::displayPlayerLoosesCard(int playerId, std::shared_ptr<Card> card)
{
    m_playerPages[playerId]->removeCards(CardList{card});
}

void MainWindow::displayWorningWindow(QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning!"); // Set the title of the window
    msgBox.setText(message); // Set the message text
    msgBox.setStandardButtons(QMessageBox::Ok); // Add an "OK" button
    msgBox.setDefaultButton(QMessageBox::Ok); // Set "OK" as the default button
    msgBox.exec();
}

void MainWindow::finishGame(int currentPlayerId)
{
    //QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(char(currentPlayerId + 'A')));
    //close(); // Optionally close the game
}

void MainWindow::handlePlayerCardActivatedBefore(uchar dice1, uchar dice2)
{
    if (m_stateMachine->configuration().contains(m_incomeState)) {
        if (m_canRerollDice[m_currentPlayerId]) {
            m_canRerollDice[m_currentPlayerId] = false;
            bool wantsReroll = askForReroll(this);
            if (wantsReroll) {
                emit rollButtonClickedWithCanReroll(dice1, dice2);
                emit activateCardsHighlighting(m_playerPages[m_currentPlayerId]->balance());
            } else {
                emit diceRollAccepted(dice1, dice2);
                emit activateCardsHighlighting(m_playerPages[m_currentPlayerId]->balance());
            }
        } else {
            emit diceRollAccepted(dice1, dice2);
            emit activateCardsHighlighting(m_playerPages[m_currentPlayerId]->balance());
        }
    } else {
        emit diceRollAccepted(dice1, dice2);
        emit activateCardsHighlighting(m_playerPages[m_currentPlayerId]->balance());
    }
}

void MainWindow::handleShowMainWindow(uchar numPlayers)
{
    m_numPlayers = numPlayers;
    m_currentPlayerId = 0;

#ifdef false
    // Should go to the function which hendles changes of the bank
    // bank is a new name for bank
    try {
        std::sort(bankCards.begin(), bankCards.end(), [](const std::shared_ptr<Card>& a, const std::shared_ptr<Card>& b) {
            return a->id() < b->id();
        });
    } catch (const std::out_of_range& e) {
        qCritical() << "Card activation values error:" << e.what();
        // Handle error
    }
#endif

    // Create a view for each player and add it as a tab
    char playerId = 'A';
    QVector<QString> playerNames(m_numPlayers);
    for (int i = 0; i < m_numPlayers; ++i, ++playerId) {
        PlayerPage* playerPage = createPlayerPage(i);

        m_playerPages.append(playerPage);
        m_tabWidget->addTab(playerPage, QString("Player %1").arg(playerId));

        connect(this, &MainWindow::activateCardsHighlighting, m_playerPages[i],
                [this, i](int playerBalance) { emit m_playerPages[i]->activateCardsHighlighting(playerBalance);
        });

        connect(this, &MainWindow::deactivateCardsHighlighting, m_playerPages[i],
                [this, i]() { emit m_playerPages[i]->deactivateCardsHighlighting();
        });

        if (i == 0) {
            m_tabWidget->setTabIcon(i, createCircleIcon(QColor(72, 181, 163)));
        } else {
            m_tabWidget->setTabIcon(i, createCircleIcon(QColor(252, 169, 133)));
        }

        //qDebug() << "added playerPage to tab";
        playerNames[i] = QString("Player %1").arg(playerId);
    }

    emit createPlayers(playerNames.toList());
    setupStateMachine();
    updateButtonStates();

    show();
}

void MainWindow::processDiceRoll(uchar dice1, uchar dice2)
{
    const int radioTowerId = 3;
    emit checkPlayerCards(radioTowerId, m_currentPlayerId, dice1, dice2);
}

void MainWindow::repaintPlayerPanel(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;
    if (m_tabWidget && currentPlayerId >= 0 && currentPlayerId < m_tabWidget->count()) {
        m_tabWidget->setCurrentIndex(currentPlayerId);
    }

    QIcon activeIcon = createCircleIcon(QColor(72, 181, 163), 128);
    QIcon notActiveIcon = createCircleIcon(QColor(252, 169, 133), 128);
    for (int playerId = 0; playerId < m_numPlayers; ++playerId) {
        m_tabWidget->setTabIcon(playerId, notActiveIcon);
    }
    m_tabWidget->setTabIcon(currentPlayerId, activeIcon);

    updateButtonStates();
}

void MainWindow::unlockBuildAgainIfDubleRollDice()
{
    if (m_currentPlayerId >= 0 && m_currentPlayerId < m_numPlayers) {
        m_canBuildAgainIfDubleRollDice[m_currentPlayerId] = true;
    }
}

void MainWindow::unlockDiceReroll()
{
    if (m_currentPlayerId >= 0 && m_currentPlayerId < m_numPlayers) {
        m_canRerollDice[m_currentPlayerId] = true;
    }
}

void MainWindow::unlockPlayerLandmark(std::shared_ptr<Card> card)
{
    emit deactivateCardsHighlighting();
    emit cardTurnSound();

    auto id = card->id();
    m_playerPages[m_currentPlayerId]->turnOnCardStack(id);

    if (id == 0) {
        m_canPressTwoDiceButton[m_currentPlayerId] = true;
    }

    update();
    if (m_canBuildAgainIfDubleRollDice[m_currentPlayerId]) {
        m_canBuildAgainIfDubleRollDice[m_currentPlayerId] = false;
        emit buildOneMoreBuilding();
    } else {
        emit updatedPlayersPanel(); // the look of it
    }
}

void MainWindow::unlockRollTwoDiceButton()
{
    if (m_currentPlayerId >= 0 && m_currentPlayerId < m_numPlayers) {
        m_playerPages[m_currentPlayerId]->setRollButtonsEnabled(true, true);
    }
}

void MainWindow::updatePlayerBalanceLabel(uchar balance, int playerId)
{
    m_playerPages[playerId]->setPlayerBalance(balance);
    update();
}

void MainWindow::handleCardClick(uchar cardId)
{
    //qDebug() << "HandleCardClick!";
    if (m_stateMachine->configuration().contains(m_buyingState) ||
        m_stateMachine->configuration().contains(m_buyOrRerollState))
    {
        //qDebug() << "card is clicked!";
        emit takeCardSound();
        emit cardWidgetClicked(cardId);
    }
}

void MainWindow::onRollOneDiceClicked()
{
    emit buttonClickSound();

    uchar dice = DiceRoller{}.rollDice(1);
    //qDebug() << "Roll One Dice button Clicked!";
    m_playerPages[m_currentPlayerId]->setDiceResult(dice);

    processDiceRoll(dice, 0);
}

void MainWindow::onRollTwoDiceClicked()
{
    emit buttonClickSound();

    uchar dice1 = DiceRoller{}.rollDice(1);
    uchar dice2 = DiceRoller{}.rollDice(1);
    //qDebug() << "Roll Two Dice button Clicked!";
    m_playerPages[m_currentPlayerId]->setDiceResult(dice1, dice2);

    processDiceRoll(dice1, dice2);
}

void MainWindow::onSkipClicked()
{
    emit buttonClickSound();
    //qDebug() << "Skip button Clicked!";
    if (m_canBuildAgainIfDubleRollDice[m_currentPlayerId]) {
        m_canBuildAgainIfDubleRollDice[m_currentPlayerId] = false;
        emit buildOneMoreBuilding();
    } else {
        emit skipClicked();
    }
}

void MainWindow::centerWindow()
{
    // Get the screen geometry
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Calculate the center position
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    // Move the window to the center
    move(x, y);
    hide();
}

QIcon MainWindow::createCircleIcon(const QColor color, qsizetype size)
{
    QPixmap iconPixmap(size, size);
    iconPixmap.fill(Qt::transparent);
    QPainter painter(&iconPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(0, 0, size, size);
    return QIcon(iconPixmap);
}

PlayerPage* MainWindow::createPlayerPage(uchar playerId)
{
    PlayerPage* playerPage = new PlayerPage(playerId);
    connect(playerPage, &PlayerPage::rollOneDiceClicked, this, &MainWindow::onRollOneDiceClicked);
    connect(playerPage, &PlayerPage::rollTwoDiceClicked, this, &MainWindow::onRollTwoDiceClicked);
    connect(playerPage, &PlayerPage::skipClicked, this, &MainWindow::onSkipClicked);
    //connect(playerPage, &PlayerPage::)

    connect(playerPage, &PlayerPage::cardClicked, this, [this](uchar cardId) {
        qDebug() << "[MainWindow] Handling ID:" << cardId; // Debug
        handleCardClick(cardId);
    });

    //qDebug() << "createPlayerPage finishes";
    return playerPage;
}

void MainWindow::setupStateMachine()
{

    // Define transitions
    m_incomeState->addTransition(this, &MainWindow::diceRollAccepted, m_buyingState);
    m_incomeState->addTransition(this, &MainWindow::rollButtonClickedWithCanReroll, m_buyOrRerollState);
    m_buyingState->addTransition(this, &MainWindow::buildOneMoreBuilding, m_buyingState);
    m_buyingState->addTransition(this, &MainWindow::skipClicked, m_incomeState);
    m_buyingState->addTransition(this, &MainWindow::updatedPlayersPanel, m_incomeState);
    m_buyOrRerollState->addTransition(this, &MainWindow::diceRollAccepted, m_buyingState);

    // Add states to the state machine
    m_stateMachine->addState(m_incomeState);
    m_stateMachine->addState(m_buyingState);
    m_stateMachine->addState(m_buyOrRerollState);
    m_stateMachine->addState(m_finalState);

    // Set the initial state
    m_stateMachine->setInitialState(m_incomeState);

    // Connect state entered signals to update button states
    connect(m_incomeState, &QState::entered, this, &MainWindow::updateButtonStates);
    connect(m_buyingState, &QState::entered, this, &MainWindow::updateButtonStates);
    connect(m_buyOrRerollState, &QState::entered, this, &MainWindow::updateButtonStates);

    // Start the state machine
    m_stateMachine->start();
}

void MainWindow::updateButtonStates()
{
    //qDebug() << "updateButtonStates starts";
    bool isIncomeState = m_stateMachine->configuration().contains(m_incomeState);
    bool isBuyingState = m_stateMachine->configuration().contains(m_buyingState);
    bool isBuyOrRerollState = m_stateMachine->configuration().contains(m_buyOrRerollState);

    for (int i = 0; i < m_numPlayers; ++i) {
        bool isActivePlayer = (i == m_currentPlayerId);

        m_playerPages[i]->getOneDiceButton().setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer);
        m_playerPages[i]->getTwoDiceButton().setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer & m_canPressTwoDiceButton[m_currentPlayerId]);
        m_playerPages[i]->getSkipButton().setEnabled((isBuyOrRerollState || isBuyingState) && isActivePlayer);
    }
    //qDebug() << "updateButtonStates finishes";
}
