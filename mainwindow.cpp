#include "mainwindow.h"
#include "cardstackwidget.h"
#include "cardwidget.h"
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
    , m_reserveScrollWidget(new QWidget())
    , m_reserveLayout(new QHBoxLayout(m_reserveScrollWidget))
{
    setWindowTitle("City Building Card Game");
    setupStateMachine();

    resize(1366, 768);
    centerWindow();
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
    CardsList cards;
    cards.push_back(card);    
    placeCards(cards, *m_buildsLayout[m_currentPlayerId], m_playerCardStacks[m_currentPlayerId]);
    removeCards(cards, *m_reserveLayout, m_reserveCardsStack);
    update();
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
    m_numPlayers = numPlayers;
    m_currentPlayerId = 0;

    // Create several copies of player panel based on number of players
    // ToDo: make it a sepate function or a class
    m_playerBalanceLabels.resize(m_numPlayers);
    m_diceResultLabels.resize(m_numPlayers);
    m_buildsLayout.resize(m_numPlayers);
    m_landmarksLayout.resize(m_numPlayers);
    m_rollOneDiceButtons.resize(m_numPlayers);
    m_rollTwoDiceButtons.resize(m_numPlayers);
    m_skipButtons.resize(m_numPlayers);
    m_playerCardStacks.resize(m_numPlayers);
    m_landmarkCardStacks.resize(m_numPlayers);
    m_canPressTwoDiceButton.resize(m_numPlayers, false);
    m_canBuildAgainIfDubleRollDice.resize(m_numPlayers, false);
    m_canRerollDice.resize(m_numPlayers, false);
    m_playerViews.resize(m_numPlayers);
    m_viewCardsLayouts.resize(m_numPlayers);
    m_landmarksScrollAreas.resize(m_numPlayers);
    m_playersBuildsAreas.resize(m_numPlayers);
    m_landmarksScrollWidgets.resize(m_numPlayers);
    m_playersBuildsScrollWidgets.resize(m_numPlayers);
    m_buttonLayouts.resize(m_numPlayers);
    m_actionLayouts.resize(m_numPlayers);
    m_labelLayouts.resize(m_numPlayers);
    m_actionWidgets.resize(m_numPlayers);

    QString configPath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    // define what card should go suppose to do the logic

    CardDataConfigReader cardReader(configPath);
    CardsList reserveCards;
    for (uchar i = 0; i < m_numPlayers; ++i) {
        reserveCards += cardReader.readFromRange(10, 12);
    }
    for (uchar i = 0; i < 6; ++i) {
        reserveCards += cardReader.readFromRange(4, 9);
        reserveCards += cardReader.readFromRange(13, 18);
    }

    try {
        std::sort(reserveCards.begin(), reserveCards.end(), [](const std::shared_ptr<Card>& a, const std::shared_ptr<Card>& b) {
            // Use value() with default instead of at()
            int aVal = a->activationValues().values().value(0, 0);
            int bVal = b->activationValues().values().value(0, 0);
            return aVal < bVal;
        });
    } catch (const std::out_of_range& e) {
        qCritical() << "Card activation values error:" << e.what();
        // Handle error
    }

    placeCards(reserveCards, *m_reserveLayout, m_reserveCardsStack);
    //m_reserveLayout->addStretch();

    m_reserveScrollWidget->setLayout(m_reserveLayout);
    m_reserveCardsArea->setWidget(m_reserveScrollWidget);
    m_reserveCardsArea->setWidgetResizable(true);

    // Create a QTabWidget to hold player views
    m_tabWidget = new QTabWidget(this);

    // Create a view for each player and add it as a tab
    char playerId = 'A';
    QVector<QString> playerNames(m_numPlayers);
    for (int i = 0; i < m_numPlayers; ++i, ++playerId) {
        auto *playerView = createPlayerView(i);
        m_tabWidget->addTab(playerView, QString("Player %1").arg(playerId));
        playerNames[i] = QString("Player %1").arg(playerId);
    }

    emit createPlayers(playerNames.toList());

    // Add the QTabWidget to the main layout
    m_mainLayout->addWidget(m_reserveCardsArea);

    // Add the Landmarks to the main layout
    //mainLayout->addWidget(landmarksCardsArea);

    // Add the QTabWidget to the main layout
    m_mainLayout->addWidget(m_tabWidget);

    m_centralWidget->setLayout(m_mainLayout);
    setCentralWidget(m_centralWidget);

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

    auto id= card->id();
    CardWidget* landmark = m_landmarkCardStacks[m_currentPlayerId][id]->at(id);
    if (!landmark) {
        return;
    }

    if (id == 0) {
        landmark->landmarkUnlocked(); // changes the color
        m_canPressTwoDiceButton[m_currentPlayerId] = true;
    } else if (id == 1) {
        landmark->landmarkUnlocked(); // changes the color
        //m_canBuildAgainIfDubleRollDice[m_currentPlayerId] = true;
    } else if (id == 2) {
        landmark->landmarkUnlocked();
    } else if (id == 3) {
        landmark->landmarkUnlocked();
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
        m_rollTwoDiceButtons[m_currentPlayerId]->setEnabled(true);
    }
}

void MainWindow::updateDiceResultLabel(uchar dice)
{

}

void MainWindow::updatePlayerBalanceLabel(uchar balance, int playerId)
{
    m_playerBalanceLabels[playerId]->setText(QString("Coins: %1").arg(balance));
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
    m_diceResultLabels[m_currentPlayerId]->setText(QString("Dice result: %1").arg(dice));

    processDiceRoll(dice, 0);
}

void MainWindow::onRollTwoDiceClicked()
{
    emit buttonClickSound();

    uchar dice1 = DiceRoller{}.rollDice(1);
    uchar dice2 = DiceRoller{}.rollDice(1);
    qDebug() << "Roll Two Dice button Clicked!";
    m_diceResultLabels[m_currentPlayerId]->setText(
        QString("Dice result: %1 + %2 = %3").arg(dice1).arg(dice2).arg(dice1 + dice2)
    );

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


QWidget* MainWindow::createPlayerView(uchar playerId)
{
    if (playerId >= m_playerViews.size()) {
        qFatal("Player ID %d exceeds allocated vector size", playerId);
    }

    m_playerViews[playerId] = new QWidget();
    m_viewCardsLayouts[playerId] = new QVBoxLayout(m_playerViews[playerId]);

    m_landmarksScrollAreas[playerId] = new QScrollArea();
    m_playersBuildsAreas[playerId] = new QScrollArea();

    QString configPath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    CardDataConfigReader cardReader(configPath);


    m_landmarksScrollWidgets[playerId] = new QWidget();
    m_landmarksLayout[playerId] = new QHBoxLayout(m_landmarksScrollWidgets[playerId]);

    QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 3);
    //QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 18);
    placeCards(landmarkCards, *m_landmarksLayout[playerId], m_landmarkCardStacks[playerId]);

    m_landmarksScrollWidgets[playerId]->setLayout(m_landmarksLayout[playerId]);
    m_landmarksScrollAreas[playerId]->setWidget(m_landmarksScrollWidgets[playerId]);
    m_landmarksScrollAreas[playerId]->setWidgetResizable(true);

    m_playersBuildsScrollWidgets[playerId] = new QWidget();
    m_buildsLayout[playerId] = new QHBoxLayout(m_landmarksScrollWidgets[playerId]);

    QVector<std::shared_ptr<Card>> playerCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    placeCards(playerCards, *m_buildsLayout[playerId], m_playerCardStacks[playerId]);

    m_playersBuildsScrollWidgets[playerId]->setLayout(m_buildsLayout[playerId]);
    m_playersBuildsAreas[playerId]->setWidget(m_playersBuildsScrollWidgets[playerId]);
    m_playersBuildsAreas[playerId]->setWidgetResizable(true);

    m_viewCardsLayouts[playerId]->addWidget(new QLabel("Landmarks"));
    m_viewCardsLayouts[playerId]->addWidget(m_landmarksScrollAreas[playerId]);
    m_viewCardsLayouts[playerId]->addWidget(new QLabel("Builds"));
    m_viewCardsLayouts[playerId]->addWidget(m_playersBuildsAreas[playerId]);

    // Create a horizontal layout for buttons
    m_buttonLayouts[playerId] = new QHBoxLayout();
    m_rollOneDiceButtons[playerId] = new QPushButton("Roll 1 dice");
    m_rollOneDiceButtons[playerId]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_rollOneDiceButtons[playerId]->setEnabled(false);
    m_rollTwoDiceButtons[playerId] = new QPushButton("Roll 2 dice");
    m_rollTwoDiceButtons[playerId]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_rollTwoDiceButtons[playerId]->setEnabled(false);
    m_skipButtons[playerId] = new QPushButton("Skip Build");
    m_skipButtons[playerId]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_skipButtons[playerId]->setEnabled(false);

    connect(m_rollOneDiceButtons[playerId], &QPushButton::clicked, this, &MainWindow::onRollOneDiceClicked);
    connect(m_rollTwoDiceButtons[playerId], &QPushButton::clicked, this, &MainWindow::onRollTwoDiceClicked);
    connect(m_skipButtons[playerId], &QPushButton::clicked, this, &MainWindow::onSkipClicked);

    m_buttonLayouts[playerId]->addWidget(m_rollOneDiceButtons[playerId]);
    m_buttonLayouts[playerId]->addWidget(m_rollTwoDiceButtons[playerId]);
    m_buttonLayouts[playerId]->addWidget(m_skipButtons[playerId]);

    // Create a horizontal layout for labels
    m_labelLayouts[playerId] = new QHBoxLayout();
    m_playerBalanceLabels[playerId] = new QLabel("Coins: 3");
    m_playerBalanceLabels[playerId]->setAlignment(Qt::AlignLeft);
    m_diceResultLabels[playerId] = new QLabel("Dice result: 0");
    m_diceResultLabels[playerId]->setAlignment(Qt::AlignLeft);

    m_labelLayouts[playerId]->addWidget(m_playerBalanceLabels[playerId]);
    m_labelLayouts[playerId]->addWidget(m_diceResultLabels[playerId]);
    m_labelLayouts[playerId]->setAlignment(Qt::AlignLeft);

    // Add both horizontal layouts to the actionLayout
    m_actionLayouts[playerId] = new QVBoxLayout();
    m_actionLayouts[playerId]->addLayout(m_actionLayouts[playerId]); // Add button layout
    m_actionLayouts[playerId]->addLayout(m_labelLayouts[playerId]); // Add label layout
    m_actionLayouts[playerId]->setAlignment(Qt::AlignLeft);

    m_actionWidgets[playerId] = new QWidget(m_playerViews[playerId]);
    m_actionWidgets[playerId]->setLayout(m_actionLayouts[playerId]);

    m_viewCardsLayouts[playerId]->addWidget(m_actionWidgets[playerId]);

    m_playerViews[playerId]->setLayout(m_viewCardsLayouts[playerId]);

    return m_playerViews[playerId];
}

void MainWindow::placeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack)
{
    for (int i = 0; i < cards.size(); ++i) {
        auto *customWidget = new CardWidget(cards[i]->imagePath(),
                                            cards[i]->activationValues(),
                                            cards[i]->title(),
                                            cards[i]->description(),
                                            QString::number(cards[i]->price()),
                                            QString::number(cards[i]->pack()),
                                            cards[i]->type(),
                                            cards[i]->id());

        // Find or create a pile for this card type
        auto cardId = cards[i]->id();
        if (!cardStack.contains(cardId)) {
            cardStack[cardId] = new CardStackWidget();
            layout.addWidget(cardStack[cardId]); // Add the pile to the layout
        }

        // Add the card to the appropriate pile
        cardStack[cardId]->addCard(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
        update();
    }
}

void MainWindow::removeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack)
{
    for (int i = 0; i < cards.size(); ++i) {
        uchar cardId = cards[i]->id();

        // Check if the stack exists
        if (cardStack.contains(cardId)) {
            CardStackWidget *stackWidget = cardStack[cardId];

            if (!stackWidget->isEmpty()) {
                stackWidget->removeCard(); // Remove a card from the stack
            }

            // If the stack becomes empty, remove it from the layout and delete it
            if (stackWidget->isEmpty()) {
                //layout.removeWidget(stackWidget);
                stackWidget->deleteLater();
                cardStack.remove(cardId);
            }
        }
    }
    update();
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
    bool isIncomeState = m_stateMachine->configuration().contains(m_incomeState);
    bool isBuyingState = m_stateMachine->configuration().contains(m_buyingState);
    bool isBuyOrRerollState = m_stateMachine->configuration().contains(m_buyOrRerollState);

    for (int i = 0; i < m_numPlayers; ++i) {
        bool isActivePlayer = (i == m_currentPlayerId);

        m_rollOneDiceButtons[i]->setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer);
        m_rollTwoDiceButtons[i]->setEnabled((isBuyOrRerollState || isIncomeState) && isActivePlayer & m_canPressTwoDiceButton[m_currentPlayerId]);
        m_skipButtons[i]->setEnabled((isBuyOrRerollState || isBuyingState) && isActivePlayer);
    }
}
