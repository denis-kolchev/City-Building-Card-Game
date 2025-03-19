#include "mainwindow.h"
#include "diceroller.h"

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
    , m_reserveCardsArea(new QScrollArea())
    , m_reserveScrollWidget(new CardScrollWidget())
    , m_reserveLayout(new QHBoxLayout(m_reserveScrollWidget))
    , m_tabWidget(new QTabWidget(this))
{
    m_canPressTwoDiceButton.resize(5, 0);
    m_canBuildAgainIfDubleRollDice.resize(5, 0);
    m_canRerollDice.resize(5, 0);

    QString configPath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    // define what card should go suppose to do the logic
    CardDataConfigReader cardReader(configPath);
    CardList reserveCards;
    for (uchar i = 0; i < m_numPlayers; ++i) {
        reserveCards += cardReader.readFromRange(10, 12);
    }
    for (uchar i = 0; i < 6; ++i) {
        reserveCards += cardReader.readFromRange(4, 9);
        reserveCards += cardReader.readFromRange(13, 18);
    }

    try {
        std::sort(reserveCards.begin(), reserveCards.end(), [](const std::shared_ptr<Card>& a, const std::shared_ptr<Card>& b) {
            return a->id() < b->id();
        });
    } catch (const std::out_of_range& e) {
        qCritical() << "Card activation values error:" << e.what();
        // Handle error
    }

    m_reserveScrollWidget->placeCards(reserveCards);
    m_reserveCardsArea->setWidget(m_reserveScrollWidget);
    m_reserveCardsArea->setWidgetResizable(true);

    // Add the QTabWidget to the main layout
    m_mainLayout->addWidget(m_reserveCardsArea);

    // Add the QTabWidget to the main layout
    m_mainLayout->addWidget(m_tabWidget);

    m_centralWidget->setLayout(m_mainLayout);
    setCentralWidget(m_centralWidget);

    setWindowTitle("City Building Card Game");
    setupStateMachine();
    resize(1366, 768);
    centerWindow();
    qDebug() << "2. mainWindow is made correctly";
}

MainWindow::~MainWindow()
{
}

bool MainWindow::askForReroll(QWidget* parent)
{
    QString question = QString("Does the Player %1 want to re-roll the dice?")
    .arg(char(m_currentPlayerId + 'A'));

    QMessageBox msgBox(parent);
    msgBox.setWindowTitle("Re-roll?");
    msgBox.setText(question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    //msgBox.setDefaultButton(QMessageBox::Yes);

    return msgBox.exec() == QMessageBox::Yes;
}

void MainWindow::displayPlayerNewCard(std::shared_ptr<Card> card)
{
    m_playerPages.at(m_currentPlayerId)->placeCards(CardList{card});
    m_reserveScrollWidget->removeCards(CardList{card});

    if (m_canBuildAgainIfDubleRollDice[m_currentPlayerId]) {
        m_canBuildAgainIfDubleRollDice[m_currentPlayerId] = false;
        emit buildOneMoreBuilding();
    } else {
        emit updatedPlayersPanel();
    }
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
    QMessageBox::information(this, "Game Over", QString("Player %1 wins!").arg(char(currentPlayerId + 'A')));
    close(); // Optionally close the game
}

void MainWindow::handlePlayerCardActivatedBefore(uchar dice1, uchar dice2)
{
    if (m_stateMachine->configuration().contains(m_incomeState)) {
        if (m_canRerollDice[m_currentPlayerId]) {
            m_canRerollDice[m_currentPlayerId] = false;
            bool wantsReroll = askForReroll(this);
            if (wantsReroll) {
                emit rollButtonClickedWithCanReroll(dice1, dice2);
            } else {
                emit diceRollAccepted(dice1, dice2);
            }
        } else {
            emit diceRollAccepted(dice1, dice2);
        }
    } else {
        emit diceRollAccepted(dice1, dice2);
    }
}

void MainWindow::handleShowMainWindow(uchar numPlayers)
{
    qDebug() << "handleShowMainWindow starts";
    m_numPlayers = numPlayers;
    m_currentPlayerId = 0;

    // Create a view for each player and add it as a tab
    char playerId = 'A';
    QVector<QString> playerNames(m_numPlayers);
    for (int i = 0; i < m_numPlayers; ++i, ++playerId) {
        PlayerPage* playerPage = createPlayerPage(i);
        qDebug() << "append playerPage to m_playerPages starts";
        m_playerPages.append(playerPage);
        m_tabWidget->addTab(playerPage, QString("Player %1").arg(playerId));
        qDebug() << "added playerPage to tab";
        playerNames[i] = QString("Player %1").arg(playerId);
    }

    emit createPlayers(playerNames.toList());
    updateButtonStates();

    show();
}

void MainWindow::processDiceRoll(uchar dice1, uchar dice2)
{
    // 3 - id of Radio Tower
    emit checkPlayerCards(3, m_currentPlayerId, dice1, dice2);
}

void MainWindow::repaintPlayerPanel(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;
    if (m_tabWidget && currentPlayerId >= 0 && currentPlayerId < m_tabWidget->count()) {
        m_tabWidget->setCurrentIndex(currentPlayerId);
    }
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
    m_playerPages[m_currentPlayerId]->setPlayerBalance(balance);
}

void MainWindow::handleCardClick(uchar cardId)
{
    if (m_stateMachine->configuration().contains(m_buyingState) ||
        m_stateMachine->configuration().contains(m_buyOrRerollState))
    {
        qDebug() << "card is clicked!";
        emit takeCardSound();
        emit cardWidgetClicked(cardId);
    }
}

void MainWindow::onRollOneDiceClicked()
{
    emit buttonClickSound();

    uchar dice = DiceRoller{}.rollDice(1);
    qDebug() << "Roll One Dice button Clicked!";
    m_playerPages[m_currentPlayerId]->setDiceResult(dice);

    processDiceRoll(dice, 0);
}

void MainWindow::onRollTwoDiceClicked()
{
    emit buttonClickSound();

    uchar dice1 = DiceRoller{}.rollDice(1);
    uchar dice2 = DiceRoller{}.rollDice(1);
    qDebug() << "Roll Two Dice button Clicked!";
    m_playerPages[m_currentPlayerId]->setDiceResult(dice1, dice2);

    processDiceRoll(dice1, dice2);
}

void MainWindow::onSkipClicked()
{
    emit buttonClickSound();
    qDebug() << "Skip button Clicked!";
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


PlayerPage* MainWindow::createPlayerPage(uchar playerId)
{
    qDebug() << "createPlayerPage starts";
    QString configPath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    PlayerPage* playerPage = new PlayerPage(playerId, configPath);
    connect(playerPage, &PlayerPage::rollOneDiceClicked, this, &MainWindow::onRollOneDiceClicked);
    connect(playerPage, &PlayerPage::rollTwoDiceClicked, this, &MainWindow::onRollTwoDiceClicked);
    connect(playerPage, &PlayerPage::skipClicked, this, &MainWindow::onSkipClicked);
    connect(playerPage, &PlayerPage::cardClicked, this, &MainWindow::handleCardClick);

    qDebug() << "createPlayerPage finishes";
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
    qDebug() << "updateButtonStates starts";
    bool isIncomeState = m_stateMachine->configuration().contains(m_incomeState);
    bool isBuyingState = m_stateMachine->configuration().contains(m_buyingState);
    bool isBuyOrRerollState = m_stateMachine->configuration().contains(m_buyOrRerollState);

    for (int i = 0; i < m_numPlayers; ++i) {
        bool isActivePlayer = (i == m_currentPlayerId);

        m_playerPages[i]->getOneDiceButton().setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer);
        m_playerPages[i]->getTwoDiceButton().setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer & m_canPressTwoDiceButton[m_currentPlayerId]);
        m_playerPages[i]->getSkipButton().setEnabled((isBuyOrRerollState || isBuyingState) && isActivePlayer);
    }
    qDebug() << "updateButtonStates finishes";
}
