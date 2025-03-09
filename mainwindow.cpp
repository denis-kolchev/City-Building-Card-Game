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
