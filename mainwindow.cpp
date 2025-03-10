#include "mainwindow.h"
#include "carddataconfigreader.h"
#include "cardfactory.h"
#include "cardwidget.h"
#include "gamelogic.h"

#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
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
    auto *bankScrolllayout = new QHBoxLayout(bankScrollWidget );

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

    for (int i = 0; i < cards.size(); ++i) {
        const QString& imagePath = cards[i]->imagePath();
        QSet<uchar> triggers = cards[i]->activationValues();
        const QString& title = cards[i]->title();
        const QString& description = cards[i]->description();
        const QString& price = QString::number(cards[i]->price());
        const QString& pack = QString::number(cards[i]->pack());
        auto* customWidget = new CardWidget(imagePath,
                                            triggers,
                                            title,
                                            description,
                                            price,
                                            pack,
                                            cards[i]->type());
        bankScrolllayout->addWidget(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
    }

    bankScrollWidget->setLayout(bankScrolllayout);
    bankCardsArea->setWidget(bankScrollWidget);
    bankCardsArea->setWidgetResizable(true);

    auto *landmarksScrollWidget = new QWidget();
    auto *landmarksScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> landmarkCards = cardReader.readFromRange(0, 3);
    for (int i = 0; i < landmarkCards.size(); ++i) {
        const QString& imagePath = landmarkCards[i]->imagePath();
        QSet<uchar> triggers = landmarkCards[i]->activationValues();
        const QString& title = landmarkCards[i]->title();
        const QString& description = landmarkCards[i]->description();
        const QString& price = QString::number(landmarkCards[i]->price());
        const QString& pack = QString::number(landmarkCards[i]->pack());
        auto* customWidget = new CardWidget(imagePath,
                                            triggers,
                                            title,
                                            description,
                                            price,
                                            pack,
                                            landmarkCards[i]->type());
        landmarksScrollLayout->addWidget(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
    }


    landmarksScrollWidget->setLayout(landmarksScrollLayout);
    landmarksScrollArea->setWidget(landmarksScrollWidget);
    landmarksScrollArea->setWidgetResizable(true);

    auto *playersBuildsScrollWidget = new QWidget();
    auto *playersBuildsScrollLayout = new QHBoxLayout(landmarksScrollWidget);

    QVector<std::shared_ptr<Card>> playerCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    for (int i = 0; i < playerCards.size(); ++i) {
        const QString& imagePath = playerCards[i]->imagePath();
        QSet<uchar> triggers = playerCards[i]->activationValues();
        const QString& title = playerCards[i]->title();
        const QString& description = playerCards[i]->description();
        const QString& price = QString::number(playerCards[i]->price());
        const QString& pack = QString::number(playerCards[i]->pack());
        auto* customWidget = new CardWidget(imagePath,
                                            triggers,
                                            title,
                                            description,
                                            price,
                                            pack,
                                            playerCards[i]->type());
        playersBuildsScrollLayout->addWidget(customWidget);
        connect(customWidget, &CardWidget::clicked, this, &MainWindow::handleCardClick);
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

    // QVector<std::shared_ptr<Card>> cards(cardNames.size());
    // for (int i = 0; i < cardNames.size(); ++i) {
    //     cards[i] = cardFactory->createCard(titles[i],
    //                                        descriptions[i],
    //                                        cardTypes[i],
    //                                        triggerNumbers[i].toInt());
    // }

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
