#include "mainwindow.h"
#include "cardstackwidget.h"
#include "cardwidget.h"
#include "diceroller.h"

#include <QDir>
#include <QLabel>
#include <QScrollArea>
#include <QVector>

#include <QTabWidget>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , m_stateMachine(new QStateMachine(this))
{
    connect(this, &MainWindow::rollButtonClicked,
            this, &MainWindow::updateDiceResultLabel);

    setupStateMachine();

    setWindowTitle("City Building Card Game");

    //connect(this, &MainWindow::buyButtonClicked);

    // // Initialize game logic
    // GameLogic game(playerNames);

    // // Add cards and landmarks to players
    // for (int i = 0; i < playerNames.size(); ++i) {
    //     for (int j = 0; j < cards.size(); ++j) {
    //         game.getPlayer(i).addCard(cards[j]);
    //     }
    // }

    // // Play a few turns
    // for (int i = 0; i < 39; ++i) {
    //     game.playTurn();

    //     for (int j = 0; j < playerNames.size(); ++j) {
    //         qDebug() << game.getPlayer(j).name() << " has coins " << game.getPlayer(j).coins();
    //     }
    //     qDebug() << "\n";
    // }
}

MainWindow::~MainWindow()
{
}

void MainWindow::displayPlayerNewCard(std::shared_ptr<Card> card)
{
    // m_currentPlayerId .. let's do stuff here of displaying it
    CardsList cards;
    cards.push_back(card);    
    placeCards(cards, *m_buildsLayout[m_currentPlayerId], m_playerCardStacks[m_currentPlayerId]);
    removeCards(cards, *m_reserveLayout, m_reserveCardsStack);
    update();
    emit updatedPlayersPanel();
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

    // Read card data from config
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir sourceDir(executablePath);
    sourceDir.cd("../../../"); // Move on 3 levels up
    QString configPath = sourceDir.absolutePath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    CardDataConfigReader cardReader(configPath);

    // Creating persistent part of game - card reserve and landmarks
    // ToDo: create it before the numer of players known
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(centralWidget);

    // Create a view for Card Reserve
    auto *reserveCardsArea = new QScrollArea();

    auto *reserveScrollWidget = new QWidget();
    auto *m_reserveLayout = new QHBoxLayout(reserveScrollWidget);

    // define what card should go suppose to do the logic

    CardsList reserveCards;
    for (uchar i = 0; i < m_numPlayers; ++i) {
        reserveCards += cardReader.readFromRange(10, 12);
    }
    for (uchar i = 0; i < 6; ++i) {
        reserveCards += cardReader.readFromRange(4, 9);
        reserveCards += cardReader.readFromRange(13, 18);
    }
    std::sort(reserveCards.begin(), reserveCards.end(), [](const std::shared_ptr<Card>& a, const std::shared_ptr<Card>& b) {
        return a->activationValues().values().at(0) < b->activationValues().values().at(0);
    });

    placeCards(reserveCards, *m_reserveLayout, m_reserveCardsStack);
    //m_reserveLayout->addStretch();

    reserveScrollWidget->setLayout(m_reserveLayout);
    reserveCardsArea->setWidget(reserveScrollWidget);
    reserveCardsArea->setWidgetResizable(true);

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
    mainLayout->addWidget(reserveCardsArea);

    // Add the Landmarks to the main layout
    //mainLayout->addWidget(landmarksCardsArea);

    // Add the QTabWidget to the main layout
    mainLayout->addWidget(m_tabWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    updateButtonStates();

    show();
}

void MainWindow::startBuildStage()
{
    // unblock ability to click on cards and skip button
}

void MainWindow::updateCurrentPlayer(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;
    if (m_tabWidget && currentPlayerId >= 0 && currentPlayerId < m_tabWidget->count()) {
        m_tabWidget->setCurrentIndex(currentPlayerId);
    }
    // Todo: add checking of QTabWidget to the new currentPlayer
    updateButtonStates();
    // redraw menu making it available for the next player
}

void MainWindow::updateDiceResultLabel(uchar dice)
{

}

void MainWindow::updatePlayerBalanceLabel(uchar balance)
{
    m_playerBalanceLabels[m_currentPlayerId]->setText(QString("Coins: %1").arg(balance));
}

void MainWindow::handleCardClick(QString cardTitle)
{
    qDebug() << "card is clicked!";
    emit cardWidgetClicked(cardTitle);
}

void MainWindow::onRollOneDiceClicked()
{
    uchar dice = DiceRoller{}.rollDice(1);
    qDebug() << "Roll One Dice button Clicked!";
    m_diceResultLabels[m_currentPlayerId]->setText(QString("Dice result: %1").arg(dice));
    emit rollButtonClicked(dice);
}

void MainWindow::onRollTwoDiceClicked()
{
    uchar dice = DiceRoller{}.rollDice(2);
    qDebug() << "Roll Two Dice button Clicked!";
    m_diceResultLabels[m_currentPlayerId]->setText(QString("Dice result: %1").arg(dice));
    emit rollButtonClicked(dice);
}

void MainWindow::onSkipClicked()
{
    qDebug() << "Skip button Clicked!";
    emit skipClicked();
}

QWidget* MainWindow::createPlayerView(uchar playerId)
{
    auto *playerView = new QWidget();

    auto *viewCardsLayout = new QVBoxLayout(playerView);

    auto *landmarksLabel = new QLabel("Landmarks");
    auto *landmarksScrollArea = new QScrollArea();
    auto *playersBuilds = new QLabel("Builds");
    auto *playersBuildsArea = new QScrollArea();

    // Read card data from config
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir sourceDir(executablePath);
    sourceDir.cd("../../../"); // Move on 3 levels up
    QString configPath = sourceDir.absolutePath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    CardDataConfigReader cardReader(configPath);


    auto *landmarksScrollWidget = new QWidget();
    m_landmarksLayout[playerId] = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 3);
    //QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 18);
    placeCards(landmarkCards, *m_landmarksLayout[playerId], m_landmarkCardStacks[playerId]);

    landmarksScrollWidget->setLayout(m_landmarksLayout[playerId]);
    landmarksScrollArea->setWidget(landmarksScrollWidget);
    landmarksScrollArea->setWidgetResizable(true);

    auto *playersBuildsScrollWidget = new QWidget();
    m_buildsLayout[playerId] = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> playerCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    placeCards(playerCards, *m_buildsLayout[playerId], m_playerCardStacks[playerId]);

    playersBuildsScrollWidget->setLayout(m_buildsLayout[playerId]);
    playersBuildsArea->setWidget(playersBuildsScrollWidget);
    playersBuildsArea->setWidgetResizable(true);

    viewCardsLayout->addWidget(landmarksLabel);
    viewCardsLayout->addWidget(landmarksScrollArea);
    viewCardsLayout->addWidget(playersBuilds);
    viewCardsLayout->addWidget(playersBuildsArea);

    // Create a horizontal layout for buttons
    auto *buttonLayout = new QHBoxLayout();
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

    buttonLayout->addWidget(m_rollOneDiceButtons[playerId]);
    buttonLayout->addWidget(m_rollTwoDiceButtons[playerId]);
    buttonLayout->addWidget(m_skipButtons[playerId]);

    // Create a horizontal layout for labels
    auto *labelLayout = new QHBoxLayout();
    m_playerBalanceLabels[playerId] = new QLabel("Coins: 3");
    m_playerBalanceLabels[playerId]->setAlignment(Qt::AlignLeft);
    m_diceResultLabels[playerId] = new QLabel("Dice result: 0");
    m_diceResultLabels[playerId]->setAlignment(Qt::AlignLeft);

    labelLayout->addWidget(m_playerBalanceLabels[playerId]);
    labelLayout->addWidget(m_diceResultLabels[playerId]);
    labelLayout->setAlignment(Qt::AlignLeft);

    // Add both horizontal layouts to the actionLayout
    auto *actionLayout = new QVBoxLayout();
    actionLayout->addLayout(buttonLayout); // Add button layout
    actionLayout->addLayout(labelLayout); // Add label layout
    actionLayout->setAlignment(Qt::AlignLeft);

    auto *actionWidget = new QWidget(playerView);
    actionWidget->setLayout(actionLayout);

    viewCardsLayout->addWidget(actionWidget);

    playerView->setLayout(viewCardsLayout);

    return playerView;
}

#ifdef false
void MainWindow::placeCards(CardsList &cards, CardsLayout &layout)
{
    for (int i = 0; i < cards.size(); ++i) {
        auto* customWidget = new CardWidget(cards[i]->imagePath(),
                                            cards[i]->activationValues(),
                                            cards[i]->title(),
                                            cards[i]->description(),
                                            QString::number(cards[i]->price()),
                                            QString::number(cards[i]->pack()),
                                            cards[i]->type());
        layout.addWidget(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
    }
}
#endif
void MainWindow::placeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack)
{
    for (int i = 0; i < cards.size(); ++i) {
        auto *customWidget = new CardWidget(cards[i]->imagePath(),
                                            cards[i]->activationValues(),
                                            cards[i]->title(),
                                            cards[i]->description(),
                                            QString::number(cards[i]->price()),
                                            QString::number(cards[i]->pack()),
                                            cards[i]->type());

        // Find or create a pile for this card type
        QString cardTitle = cards[i]->title();
        if (!cardStack.contains(cardTitle)) {
            cardStack[cardTitle] = new CardStackWidget();
            layout.addWidget(cardStack[cardTitle]); // Add the pile to the layout
        }

        // Add the card to the appropriate pile
        cardStack[cardTitle]->addCard(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
        update();
    }
}

void MainWindow::removeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack)
{
    for (int i = 0; i < cards.size(); ++i) {
        QString cardTitle = cards[i]->title();

        // Check if the stack exists
        if (cardStack.contains(cardTitle)) {
            CardStackWidget *stackWidget = cardStack[cardTitle];

            if (!stackWidget->isEmpty()) {
                stackWidget->removeCard(); // Remove a card from the stack
            }

            // If the stack becomes empty, remove it from the layout and delete it
            if (stackWidget->isEmpty()) {
                layout.removeWidget(stackWidget);
                delete stackWidget;
                cardStack.remove(cardTitle);
            }
        }
    }
    update();
}

void MainWindow::setupStateMachine()
{
    m_incomeState = new QState();
    m_buyingState = new QState();
    m_finalState = new QFinalState();

    // Define transitions
    m_incomeState->addTransition(this, &MainWindow::rollButtonClicked, m_buyingState);
    m_buyingState->addTransition(this, &MainWindow::skipClicked, m_incomeState);
    m_buyingState->addTransition(this, &MainWindow::cardWidgetClicked, m_incomeState);

    // Add states to the state machine
    m_stateMachine->addState(m_incomeState);
    m_stateMachine->addState(m_buyingState);
    m_stateMachine->addState(m_finalState);

    // Set the initial state
    m_stateMachine->setInitialState(m_incomeState);

    // Connect state entered signals to update button states
    connect(m_incomeState, &QState::entered, this, &MainWindow::updateButtonStates);
    connect(m_buyingState, &QState::entered, this, &MainWindow::updateButtonStates);

    // Start the state machine
    m_stateMachine->start();
}

void MainWindow::updateButtonStates()
{
    bool isIncomeState = m_stateMachine->configuration().contains(m_incomeState);
    bool isBuyingState = m_stateMachine->configuration().contains(m_buyingState);

    for (int i = 0; i < m_numPlayers; ++i) {
        bool isActivePlayer = (i == m_currentPlayerId);

        m_rollOneDiceButtons[i]->setEnabled(isIncomeState && isActivePlayer);
        m_rollTwoDiceButtons[i]->setEnabled(isIncomeState && isActivePlayer);
        m_skipButtons[i]->setEnabled(isBuyingState && isActivePlayer);
    }
}
