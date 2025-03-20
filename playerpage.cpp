#include "playerpage.h"
#include "carddataconfigreader.h"

#include <QDebug>
#include <QDir>
#include <QFile>

PlayerPage::PlayerPage(uchar playerId, const QString &configPath, QWidget *parent)
    : m_playerId(playerId)
    , m_landmarksScrollArea(new QScrollArea())
    , m_buildsScrollArea(new QScrollArea())
    , m_landmarkScrollWidget(new CardScrollWidget())
    , m_buildScrollWidget(new CardScrollWidget())
    , QWidget(parent)
{
    setupUi();
    readCardData(configPath);
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

    qDebug() << "Do my objects exist?";
    qDebug() << "m_landmarkScrollWidget:" << m_landmarkScrollWidget;
    qDebug() << "m_buildScrollWidget:" << m_buildScrollWidget;
    qDebug() << "finish existange check";

    bool connected1 = connect(m_landmarkScrollWidget, &CardScrollWidget::cardSignalClicked, this, [this](uchar cardId) {
        qDebug() << "[PlayerPage] Received ID:" << cardId; // Debug
        emit cardClicked(cardId); // Emit PlayerPage::cardClicked
    });
    qDebug() << "Build Scroll Widget connected:" << connected1;
    bool connected2 = connect(m_buildScrollWidget, &CardScrollWidget::cardSignalClicked, this, [this](uchar cardId) {
        qDebug() << "[PlayerPage] Received ID:" << cardId; // Debug
        emit cardClicked(cardId); // Emit PlayerPage::cardClicked
    });
    qDebug() << "m_landmarkScrollWidget Parent:" << m_landmarkScrollWidget->parent();
    qDebug() << "m_buildScrollWidget Parent:" << m_buildScrollWidget->parent();

    qDebug() << "Build Scroll Widget connected:" << connected2;
    connect(m_rollOneDiceButton, &QPushButton::clicked, this, [this]() { emit rollOneDiceClicked(m_playerId); });
    connect(m_rollTwoDiceButton, &QPushButton::clicked, this, [this]() { emit rollTwoDiceClicked(m_playerId); });
    connect(m_skipButton, &QPushButton::clicked, this, [this]() { emit skipClicked(m_playerId); });
}

// initial card set maybe shouldn't be here
void PlayerPage::readCardData(const QString &configPath)
{
    if (!QFile::exists(configPath)) {
        qDebug() << "Config file not found:" << configPath;
        return;
    }

    CardDataConfigReader cardReader(configPath);
    auto landmarkCards = cardReader.readFromRange(0, 3); // it's a game logic!
    m_landmarkScrollWidget->placeCards(landmarkCards);

    // these data also a part of a game logic!
    // It should be inside of the settings ini file
    // TODO create such file
    auto buildCards = cardReader.readFromRange(4, 4) + cardReader.readFromRange(6, 6);
    m_buildScrollWidget->placeCards(buildCards);
}

void PlayerPage::setPlayerBalance(uchar balance)
{
    m_playerBalanceLabel->setText(QString("Coins: %1").arg(balance));
}

void PlayerPage::setDiceResult(uchar dice1, uchar dice2)
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
        if (cards[i]->id() <= 3 && cards[i]->id() >= 0) {
            m_landmarkScrollWidget->placeCards(CardList{cards[i]});
        } else if (cards[i]->id() <= 18 && cards[i]->id() >= 4) {
            m_buildScrollWidget->placeCards(CardList{cards[i]});
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

void PlayerPage::turnOnCardStack(uchar id)
{
    if (id >= 0 && id <= 3) {
        m_landmarkScrollWidget->turnOn(id);
    } else {
        m_buildScrollWidget->turnOn(id);
    }
}

void PlayerPage::turnOffCardStack(uchar id)
{
    if (id >= 0 && id <= 3) {
        m_landmarkScrollWidget->turnOff(id);
    } else {
        m_buildScrollWidget->turnOff(id);
    }
}

void PlayerPage::handleCardClicked(uchar id)
{
    qDebug() << "PlayerPage::cardClicked";
    emit cardClicked(id); // Emit PlayerPage::cardClicked
}

void PlayerPage::buttonBlocked()
{
    qDebug() << "m_landmarkScrollWidget Parent:" << m_landmarkScrollWidget->parent();
    qDebug() << "m_buildScrollWidget Parent:" << m_buildScrollWidget->parent();
}
