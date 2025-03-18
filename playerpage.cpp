#include "playerpage.h"

#include <QDebug>
#include <QDir>
#include <QFile>

PlayerPage::PlayerPage(uchar playerId, const QString &configPath, QWidget *parent)
    : QWidget(parent), m_playerId(playerId)
{
    setupUi();
    readCardData(configPath);
}

void PlayerPage::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);

    // Landmarks Section
    m_landmarksScrollArea = new QScrollArea();
    m_landmarksScrollWidget = new QWidget();
    m_landmarksLayout = new QHBoxLayout(m_landmarksScrollWidget);
    m_landmarksScrollWidget->setLayout(m_landmarksLayout);
    m_landmarksScrollArea->setWidget(m_landmarksScrollWidget);
    m_landmarksScrollArea->setWidgetResizable(true);

    // Builds Section
    m_buildsScrollArea = new QScrollArea();
    m_buildsScrollWidget = new QWidget();
    m_buildsLayout = new QHBoxLayout(m_buildsScrollWidget);
    m_buildsScrollWidget->setLayout(m_buildsLayout);
    m_buildsScrollArea->setWidget(m_buildsScrollWidget);
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

    // Connect signals
    connect(m_rollOneDiceButton, &QPushButton::clicked, this, [this]() { emit rollOneDiceClicked(m_playerId); });
    connect(m_rollTwoDiceButton, &QPushButton::clicked, this, [this]() { emit rollTwoDiceClicked(m_playerId); });
    connect(m_skipButton, &QPushButton::clicked, this, [this]() { emit skipClicked(m_playerId); });
}

void PlayerPage::readCardData(const QString &configPath)
{
    if (!QFile::exists(configPath)) {
        qDebug() << "Config file not found:" << configPath;
        return;
    }

    CardDataConfigReader cardReader(configPath);
    CardsList landmarkCards = cardReader.readFromRange(0, 3);
    placeCards(landmarkCards, m_landmarksLayout, m_landmarkCardStacks);

    CardsList buildCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    placeCards(buildCards, m_buildsLayout, m_buildCardStacks);
}

void PlayerPage::placeCards(const CardsList &cards, QHBoxLayout *layout, CardsStacks &cardStack)
{
    for (int i = 0; i < cards.size(); ++i) {
        auto *cardWidget = new CardWidget(cards[i]->imagePath(),
                                          cards[i]->activationValues(),
                                          cards[i]->title(),
                                          cards[i]->description(),
                                          QString::number(cards[i]->price()),
                                          QString::number(cards[i]->pack()),
                                          cards[i]->type(),
                                          cards[i]->id());

        connect(cardWidget, &CardWidget::clicked, this, [this, &cards, &i]() { emit cardClicked(cards[i]->id()); });
        layout->addWidget(cardWidget);
        cardStack[cards[i]->id()]->addCard(cardWidget);
    }
}

void PlayerPage::setPlayerBalance(uchar balance)
{
    m_playerBalanceLabel->setText(QString("Coins: %1").arg(balance));
}

void PlayerPage::setOneDiceResult(uchar result)
{
    m_diceResultLabel->setText(QString("Dice result: %1").arg(result));
}

void PlayerPage::setTwoDiceResult(uchar dice1, uchar dice2)
{
    m_diceResultLabel->setText(
        QString("Dice result: %1 + %2 = %3").arg(dice1).arg(dice2).arg(dice1 + dice2)
    );
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

const CardsStacks& PlayerPage::getLandmarkCardStack() const
{
    return m_landmarkCardStacks;
}

CardsStacks& PlayerPage::getBuildCardStack()
{
    return m_buildCardStacks;
}

QHBoxLayout& PlayerPage::getBuildsLayout() const
{
    return *m_buildsLayout;
}

const QHBoxLayout& PlayerPage::getLandmarksLayout() const
{
    return *m_landmarksLayout;
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
