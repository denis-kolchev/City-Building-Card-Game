#include "mainwindow.h"
#include "cardfactory.h"
#include "cardwidget.h"
#include "gamelogic.h"

#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

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
    auto *bankScrolllayout = new QHBoxLayout(bankScrollWidget);

    qsizetype nBankPlaceholders = 3;

    // find a way to config file
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir sourceDir(executablePath);
    sourceDir.cd("../../../"); // Move on 3 levels up
    QString configPath = sourceDir.absolutePath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    // read card data from config
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
    CardFactory* cardFactory = new CardFactory();

    QVector<QString> cardNames = {
        "Wheat Field",
        "Bakery",
        "Cafe"
    };

    QVector<CardType> cardTypes {
        CardType::Agricultiral,
        CardType::Shop,
        CardType::Dining
    };

    // Add cards and landmarks to players
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < cards.size(); ++j) {
            game.getPlayer(i).addCard(cards[j]);
        }
    }


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
