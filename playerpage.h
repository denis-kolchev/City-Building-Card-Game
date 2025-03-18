#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "carddataconfigreader.h"
#include "cardstackwidget.h"

using CardsList = QVector<std::shared_ptr<Card>>;
using CardsStacks = QMap<uchar, CardStackWidget*>;

class PlayerPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerPage(uchar playerId, const QString &configPath, QWidget *parent = nullptr);

    void setPlayerBalance(uchar balance);

    void setOneDiceResult(uchar result);

    void setTwoDiceResult(uchar dice1, uchar dice2);

    void setRollButtonsEnabled(bool rollOneEnabled, bool rollTwoEnabled);

    void setSkipButtonEnabled(bool enabled);

    const CardsStacks& getLandmarkCardStack() const;

    CardsStacks& getBuildCardStack();

    QHBoxLayout& getBuildsLayout() const;

    const QHBoxLayout& getLandmarksLayout() const;

    QPushButton& getOneDiceButton();

    QPushButton& getTwoDiceButton();

    QPushButton& getSkipButton();

signals:
    void rollOneDiceClicked(uchar playerId);

    void rollTwoDiceClicked(uchar playerId);

    void skipClicked(uchar playerId);

    void cardClicked(uchar uchar);

private:
    void setupUi();

    void readCardData(const QString &configPath);

    void placeCards(const CardsList &cards, QHBoxLayout *layout, CardsStacks &cardStack);

    uchar m_playerId;
    QVBoxLayout *m_mainLayout;
    QScrollArea *m_landmarksScrollArea;
    QWidget *m_landmarksScrollWidget;
    QHBoxLayout *m_landmarksLayout;
    QScrollArea *m_buildsScrollArea;
    QWidget *m_buildsScrollWidget;
    QHBoxLayout *m_buildsLayout;
    QPushButton *m_rollOneDiceButton;
    QPushButton *m_rollTwoDiceButton;
    QPushButton *m_skipButton;
    QLabel *m_playerBalanceLabel;
    QLabel *m_diceResultLabel;
    CardsStacks m_landmarkCardStacks;
    CardsStacks m_buildCardStacks;
};

#endif // PLAYERPAGE_H
