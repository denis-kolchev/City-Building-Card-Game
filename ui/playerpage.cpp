#include "playerpage.h"

#include <QDebug>
#include <QDir>
#include <QFile>

PlayerPage::PlayerPage(int playerId, QWidget *parent)
    : m_playerId(playerId)
    , m_landmarksScrollArea(new QScrollArea())
    , m_buildsScrollArea(new QScrollArea())
    , m_landmarkScrollWidget(new CardScrollWidget())
    , m_buildScrollWidget(new CardScrollWidget())
    , QWidget(parent)
{
    setupUi();

    connect(this, &PlayerPage::activateCardsHighlighting, m_landmarkScrollWidget,
            [this](int playerBalance) { emit m_landmarkScrollWidget->activateCardsHighlighting(playerBalance); });

    connect(this, &PlayerPage::deactivateCardsHighlighting, m_landmarkScrollWidget,
            [this](){ emit m_landmarkScrollWidget->deactivateCardsHighlighting(); });

    connect(this, &PlayerPage::skipClicked, m_landmarkScrollWidget,
            [this](){ emit m_landmarkScrollWidget->deactivateCardsHighlighting(); });
}

int PlayerPage::balance()
{
    return m_playerBalance;
}

void PlayerPage::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);

    // Landmarks Section
    m_landmarksScrollArea->setWidget(m_landmarkScrollWidget);
    m_landmarksScrollArea->setWidgetResizable(true);

    // Builds Section
    m_buildsScrollArea->setWidget(m_buildScrollWidget);
    m_buildsScrollArea->setWidgetResizable(true);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_rollOneDiceButton = new QPushButton("Roll 1 dice");
    m_rollTwoDiceButton = new QPushButton("Roll 2 dice");
    m_skipButton = new QPushButton("Skip Build");
    m_rollOneDiceButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_rollTwoDiceButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_skipButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    buttonLayout->addWidget(m_rollOneDiceButton);
    buttonLayout->addWidget(m_rollTwoDiceButton);
    buttonLayout->addWidget(m_skipButton);

    // Labels
    QHBoxLayout *labelLayout = new QHBoxLayout();
    m_playerBalanceLabel = new QLabel("Coins: 3");
    m_diceResultLabel = new QLabel("Dice result: 0");
    labelLayout->addWidget(m_playerBalanceLabel);
    labelLayout->addWidget(m_diceResultLabel);

    // Action Layout
    QVBoxLayout *actionLayout = new QVBoxLayout();
    actionLayout->addLayout(buttonLayout);
    actionLayout->addLayout(labelLayout);

    QWidget *actionWidget = new QWidget();
    actionWidget->setLayout(actionLayout);

    // Add all to main layout
    m_mainLayout->addWidget(new QLabel("Landmarks"));
    m_mainLayout->addWidget(m_landmarksScrollArea);
    m_mainLayout->addWidget(new QLabel("Builds"));
    m_mainLayout->addWidget(m_buildsScrollArea);
    m_mainLayout->addWidget(actionWidget);

    //qDebug() << "Do my objects exist?";
    //qDebug() << "m_landmarkScrollWidget:" << m_landmarkScrollWidget;
    //qDebug() << "m_buildScrollWidget:" << m_buildScrollWidget;
    //qDebug() << "finish existange check";

    bool connected1 = connect(m_landmarkScrollWidget, &CardScrollWidget::cardSignalClicked, this, [this](CardId cardId) {
        //qDebug() << "[PlayerPage] Received ID:" << cardId; // Debug
        emit cardClicked(cardId); // Emit PlayerPage::cardClicked
    });
    //qDebug() << "Build Scroll Widget connected:" << connected1;
    bool connected2 = connect(m_buildScrollWidget, &CardScrollWidget::cardSignalClicked, this, [this](CardId cardId) {
        //qDebug() << "[PlayerPage] Received ID:" << cardId; // Debug
        emit cardClicked(cardId); // Emit PlayerPage::cardClicked
    });
    //qDebug() << "m_landmarkScrollWidget Parent:" << m_landmarkScrollWidget->parent();
    //qDebug() << "m_buildScrollWidget Parent:" << m_buildScrollWidget->parent();

    //qDebug() << "Build Scroll Widget connected:" << connected2;
    connect(m_rollOneDiceButton, &QPushButton::clicked, this, [this]() { emit rollOneDiceClicked(m_playerId); });
    connect(m_rollTwoDiceButton, &QPushButton::clicked, this, [this]() { emit rollTwoDiceClicked(m_playerId); });
    connect(m_skipButton, &QPushButton::clicked, this, [this]() { emit skipClicked(m_playerId); });
}

void PlayerPage::setPlayerBalance(int balance)
{
    m_playerBalanceLabel->setText(QString("Coins: %1").arg(balance));
    m_playerBalance = balance;
}

void PlayerPage::setDiceResult(int dice1, int dice2)
{
    if (dice2 == 0) {
        m_diceResultLabel->setText(QString("Dice result: %1").arg(dice1));
    } else {
        m_diceResultLabel->setText(
            QString("Dice result: %1 + %2 = %3").arg(dice1).arg(dice2).arg(dice1 + dice2)
        );
    }
}

void PlayerPage::setRollButtonsEnabled(bool rollOneEnabled, bool rollTwoEnabled)
{
    m_rollOneDiceButton->setEnabled(rollOneEnabled);
    m_rollTwoDiceButton->setEnabled(rollTwoEnabled);
}

void PlayerPage::setSkipButtonEnabled(bool enabled)
{
    m_skipButton->setEnabled(enabled);
}

void PlayerPage::placeCards(CardList cards)
{
    // Cards logic. Again!
    for (qsizetype i = 0; i < cards.size(); ++i) {
        if (cards[i]->id() <= CardId::RadioTower && cards[i]->id() >= CardId::RailwayStation) {
            m_landmarkScrollWidget->placeCards(CardList{cards[i]});
        } else if (cards[i]->id() <= CardId::FruitMarket && cards[i]->id() >= CardId::WheatField) {
            m_buildScrollWidget->placeCards(CardList{cards[i]});
        }
    }
    updateGeometry();
    update();
}

void PlayerPage::removeCards(CardList cards)
{
    // Cards logic. Again!
    for (qsizetype i = 0; i < cards.size(); ++i) {
        if (cards[i]->id() <= CardId::RadioTower && cards[i]->id() >= CardId::RailwayStation) {
            m_landmarkScrollWidget->removeCards(CardList{cards[i]});
        } else if (cards[i]->id() <= CardId::FruitMarket && cards[i]->id() >= CardId::WheatField) {
            m_buildScrollWidget->removeCards(CardList{cards[i]});
        }
    }
    updateGeometry();
    update();
}

QPushButton& PlayerPage::getOneDiceButton()
{
    return *m_rollOneDiceButton;
}

QPushButton& PlayerPage::getTwoDiceButton()
{
    return *m_rollTwoDiceButton;
}

QPushButton& PlayerPage::getSkipButton()
{
    return *m_skipButton;
}

void PlayerPage::turnOnCardStack(CardId id)
{
    if (id >= CardId::RailwayStation && id <= CardId::RadioTower) {
        m_landmarkScrollWidget->turnOn(id);
    } else {
        m_buildScrollWidget->turnOn(id);
    }
}

void PlayerPage::turnOffCardStack(CardId id)
{
    if (id >= CardId::RailwayStation && id <= CardId::RadioTower) {
        m_landmarkScrollWidget->turnOff(id);
    } else {
        m_buildScrollWidget->turnOff(id);
    }
}

CardScrollWidget* PlayerPage::getLandmarkScrollWidget()
{
    return m_landmarkScrollWidget;
}

CardScrollWidget* PlayerPage::getBuildScrollWidget()
{
    return m_buildScrollWidget;
}

void PlayerPage::handleCardClicked(CardId id)
{
    qDebug() << "PlayerPage::cardClicked";
    emit cardClicked(id); // Emit PlayerPage::cardClicked
}

void PlayerPage::buttonBlocked()
{
    qDebug() << "m_landmarkScrollWidget Parent:" << m_landmarkScrollWidget->parent();
    qDebug() << "m_buildScrollWidget Parent:" << m_buildScrollWidget->parent();
}
