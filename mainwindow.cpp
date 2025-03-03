#include "mainwindow.h"
#include "gamelogic.h"

#include "cards/bakery.h"
#include "cards/cafe.h"
#include "cards/shoppingmall.h"
#include "cards/wheatfield.h"

#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createCards();

    auto *centralWidget = new QWidget(this);

    auto *mainLayout = new QHBoxLayout(centralWidget);

    auto *viewCardsLayout = new QVBoxLayout();

    auto *bankLabel = new QLabel("Bank:");
    auto *bankCardsArea = new QScrollArea();
    auto *landmarksLabel = new QLabel("Landmarks:");
    auto *landmarksScrollArea = new QScrollArea();
    auto *playersBuilds = new QLabel("My builds:");
    auto *playersBuildsArea = new QScrollArea();

    auto *bankScrollWidget = new QWidget();
    auto *bankScrolllayout = new QHBoxLayout(bankScrollWidget );

    qsizetype nBankPlaceholders = 10;
    for (int i = 1; i <= nBankPlaceholders; ++i) {
        QLabel *label = new QLabel(QString("Card %1").arg(i));
        label->setAlignment(Qt::AlignCenter);
        bankScrolllayout->addWidget(label);
    }

    bankScrollWidget->setLayout(bankScrolllayout);
    bankCardsArea->setWidget(bankScrollWidget);
    bankCardsArea->setWidgetResizable(true);

    auto *landmarksScrollWidget = new QWidget();
    auto *landmarksScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    qsizetype nlandmarkPlaceholders = 10;
    for (int i = 1; i <= nlandmarkPlaceholders; ++i) {
        QLabel *label = new QLabel(QString("Card %1").arg(i));
        label->setAlignment(Qt::AlignCenter);
        landmarksScrollLayout->addWidget(label);
    }

    landmarksScrollWidget->setLayout(landmarksScrollLayout);
    landmarksScrollArea->setWidget(landmarksScrollWidget);
    landmarksScrollArea->setWidgetResizable(true);

    auto *playersBuildsScrollWidget = new QWidget();
    auto *playersBuildsScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    qsizetype nplayerBuildsPlaceholders = 10;
    for (int i = 1; i <= nplayerBuildsPlaceholders; ++i) {
        QLabel *label = new QLabel(QString("Card %1").arg(i));
        label->setAlignment(Qt::AlignCenter);
        playersBuildsScrollLayout->addWidget(label);
    }

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

    auto *viewOpponentCardsButton = new QPushButton("View opponent cards");
    auto *rollOneDiceButton = new QPushButton("Roll 1 dice");
    auto *rollTwoDiceButton = new QPushButton("Roll 2 dice");
    auto *playerMoneyLabel = new QLabel("My money: 30");
    playerMoneyLabel->setAlignment(Qt::AlignCenter);
    actionLayout->addStretch();
    actionLayout->addWidget(viewOpponentCardsButton);
    actionLayout->addWidget(rollOneDiceButton);
    actionLayout->addWidget(rollTwoDiceButton);
    actionLayout->addWidget(playerMoneyLabel);

    auto *viewCardsWidget = new QWidget(centralWidget);
    viewCardsWidget->setLayout(viewCardsLayout);

    auto *actionWidget = new QWidget(centralWidget);
    actionWidget->setLayout(actionLayout);

    mainLayout->addWidget(viewCardsWidget);
    mainLayout->addWidget(actionWidget);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("Card Game UI");

    GameLogic game({"Alice", "Bob", "Carl"});

    auto wheatField = std::make_shared<WheatField>("Wheat Field", CardType::Agricultiral, 1);
    auto cafe = std::make_shared<Cafe>("Cafe", CardType::Dining, 3);
    auto shop = std::make_shared<Bakery>("Bakey", CardType::Shop, 2);
    auto lendmark = std::make_shared<ShoppingMall>("Mall", CardType::Landmark, 51);

    // Add cards and landmarks to players
    game.getPlayer(0).addCard(wheatField);
    game.getPlayer(0).addCard(shop);
    game.getPlayer(0).addCard(cafe);
    game.getPlayer(0).addCard(lendmark);

    game.getPlayer(1).addCard(wheatField);
    game.getPlayer(1).addCard(shop);
    game.getPlayer(1).addCard(cafe);

    game.getPlayer(2).addCard(wheatField);
    game.getPlayer(2).addCard(shop);
    game.getPlayer(2).addCard(cafe);


    // Play a few turns
    for (int i = 0; i < 39; ++i) {
        game.playTurn();

        for (int i = 0; i < 3; ++i) {
            qDebug() << game.getPlayer(i).name() << " has coin s" << game.getPlayer(i).coins();
        }
        qDebug() << "\n";
    }

}

MainWindow::~MainWindow()
{
}

void MainWindow::createCards()
{

}
