#include "mainwindow.h"
#include "cardfactory.h"
#include "cardwidget.h"
#include "gamelogic.h"

#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVector>

#include <QTabWidget>

MainWindow::MainWindow(int numPlayers, QWidget *parent)
    : m_numPlayers(numPlayers)
    , QMainWindow(parent)
{
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(centralWidget);

    // Create a QTabWidget to hold player views
    auto *tabWidget = new QTabWidget(this);

    char playerId = 'A';
    // Create a view for each player and add it as a tab
    QVector<QString> playerNames(m_numPlayers);
    for (int i = 0; i < m_numPlayers; ++i, ++playerId) {
        auto *playerView = createPlayerView();
        tabWidget->addTab(playerView, QString("Player %1").arg(playerId));
        playerNames[i] = QString("Player %1").arg(playerId);
    }

    // Add the QTabWidget to the main layout
    mainLayout->addWidget(tabWidget);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Card Game UI");

    // Initialize game logic
    GameLogic game(playerNames);

    // Add cards and landmarks to players
    // for (int i = 0; i < playerNames.size(); ++i) {
    //     for (int j = 0; j < cards.size(); ++j) {
    //         game.getPlayer(i).addCard(cards[j]);
    //     }
    // }

    // Play a few turns
    for (int i = 0; i < 39; ++i) {
        game.playTurn();

        for (int j = 0; j < playerNames.size(); ++j) {
            qDebug() << game.getPlayer(j).name() << " has coins " << game.getPlayer(j).coins();
        }
        qDebug() << "\n";
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleCardClick()
{
    qDebug() << "card is clicked!";
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


QWidget* MainWindow::createPlayerView()
{
    auto *playerView = new QWidget();

    auto *viewCardsLayout = new QVBoxLayout(playerView);

    auto *bankLabel = new QLabel("Bank:");
    auto *bankCardsArea = new QScrollArea();
    auto *landmarksLabel = new QLabel("Landmarks:");
    auto *landmarksScrollArea = new QScrollArea();
    auto *playersBuilds = new QLabel("My builds:");
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
    QVector<std::shared_ptr<Card>> cards = cardReader.readFromRange(4, 18);
    placeCards(cards, *bankScrolllayout);

    bankScrollWidget->setLayout(bankScrolllayout);
    bankCardsArea->setWidget(bankScrollWidget);
    bankCardsArea->setWidgetResizable(true);

    auto *landmarksScrollWidget = new QWidget();
    auto *landmarksScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 3);
    placeCards(landmarkCards, *landmarksScrollLayout);

    landmarksScrollWidget->setLayout(landmarksScrollLayout);
    landmarksScrollArea->setWidget(landmarksScrollWidget);
    landmarksScrollArea->setWidgetResizable(true);

    auto *playersBuildsScrollWidget = new QWidget();
    auto *playersBuildsScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> playerCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    placeCards(playerCards, *playersBuildsScrollLayout);

    playersBuildsScrollWidget->setLayout(playersBuildsScrollLayout);
    playersBuildsArea->setWidget(playersBuildsScrollWidget);
    playersBuildsArea->setWidgetResizable(true);

    viewCardsLayout->addWidget(bankLabel);
    viewCardsLayout->addWidget(bankCardsArea);
    viewCardsLayout->addWidget(landmarksLabel);
    viewCardsLayout->addWidget(landmarksScrollArea);
    viewCardsLayout->addWidget(playersBuilds);
    viewCardsLayout->addWidget(playersBuildsArea);

    auto *actionLayout = new QVBoxLayout();

    auto *rollOneDiceButton = new QPushButton("Roll 1 dice");
    auto *rollTwoDiceButton = new QPushButton("Roll 2 dice");
    auto *playerMoneyLabel = new QLabel("Coins: 3");
    playerMoneyLabel->setAlignment(Qt::AlignCenter);
    actionLayout->addStretch();
    actionLayout->addWidget(rollOneDiceButton);
    actionLayout->addWidget(rollTwoDiceButton);
    actionLayout->addWidget(playerMoneyLabel);

    auto *actionWidget = new QWidget(playerView);
    actionWidget->setLayout(actionLayout);

    viewCardsLayout->addWidget(actionWidget);

    playerView->setLayout(viewCardsLayout);

    return playerView;
}
