#include "mainwindow.h"
#include "cardwidget.h"
#include "diceroller.h"

#include <QDir>
#include <QLabel>
#include <QScrollArea>
#include <QVector>

#include <QTabWidget>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    connect(this, &MainWindow::rollButtonClicked,
            this, &MainWindow::updateDiceResultLabel);

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
    placeCards(cards, *m_buildsLayout[m_currentPlayerId]);
    update();
    emit updatedPlayersPanel();
}

void MainWindow::handleShowMainWindow(uchar numPlayers)
{
    m_numPlayers = numPlayers;
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(centralWidget);

    // Create a view for Card Reserve
    auto *bankCardsArea = new QScrollArea();

    auto *bankScrollWidget = new QWidget();
    auto *bankScrolllayout = new QHBoxLayout(bankScrollWidget);

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
    QVector<std::shared_ptr<Card>> cards = cardReader.readFromRange(4, 18);
    placeCards(cards, *bankScrolllayout);
    bankScrolllayout->addStretch();

    bankScrollWidget->setLayout(bankScrolllayout);
    bankCardsArea->setWidget(bankScrollWidget);
    bankCardsArea->setWidgetResizable(true);



    // Create a QTabWidget to hold player views
    auto *tabWidget = new QTabWidget(this);

    m_playerBalanceLabels.resize(m_numPlayers);
    m_diceResultLabels.resize(m_numPlayers);
    m_buildsLayout.resize(m_numPlayers);
    m_landmarksLayout.resize(m_numPlayers);
    m_rollOneDiceButtons.resize(m_numPlayers);
    m_rollTwoDiceButtons.resize(m_numPlayers);

    // Create a view for each player and add it as a tab
    char playerId = 'A';
    QVector<QString> playerNames(m_numPlayers);
    for (int i = 0; i < m_numPlayers; ++i, ++playerId) {
        auto *playerView = createPlayerView(i);
        tabWidget->addTab(playerView, QString("Player %1").arg(playerId));
        playerNames[i] = QString("Player %1").arg(playerId);
    }

    emit createPlayers(playerNames.toList());

    // Add the QTabWidget to the main layout
    mainLayout->addWidget(bankCardsArea);

    // Add the QTabWidget to the main layout
    mainLayout->addWidget(tabWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Card Game UI");
    show();
}

void MainWindow::startBuildStage()
{
    // unblock ability to click on cards and skip button
}

void MainWindow::updateCurrentPlayer(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;
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

    auto *bankScrollWidget = new QWidget();
    auto *bankScrolllayout = new QHBoxLayout(bankScrollWidget);

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
    placeCards(landmarkCards, *m_landmarksLayout[playerId]);

    landmarksScrollWidget->setLayout(m_landmarksLayout[playerId]);
    landmarksScrollArea->setWidget(landmarksScrollWidget);
    landmarksScrollArea->setWidgetResizable(true);

    auto *playersBuildsScrollWidget = new QWidget();
    m_buildsLayout[playerId] = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> playerCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    placeCards(playerCards, *m_buildsLayout[playerId]);

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
    m_rollTwoDiceButtons[playerId] = new QPushButton("Roll 2 dice");
    m_rollTwoDiceButtons[playerId]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto *skipButton = new QPushButton("Skip Build");
    skipButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(m_rollOneDiceButtons[playerId], &QPushButton::clicked, this, &MainWindow::onRollOneDiceClicked);
    connect(m_rollTwoDiceButtons[playerId], &QPushButton::clicked, this, &MainWindow::onRollTwoDiceClicked);
    connect(skipButton, &QPushButton::clicked, this, &MainWindow::onSkipClicked);

    buttonLayout->addWidget(m_rollOneDiceButtons[playerId]);
    buttonLayout->addWidget(m_rollTwoDiceButtons[playerId]);
    buttonLayout->addWidget(skipButton);

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
