#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "cardscrollwidget.h"

class PlayerPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerPage(uchar playerId, const QString &configPath, QWidget *parent = nullptr);

    void setPlayerBalance(uchar balance);

    void setDiceResult(uchar dice1, uchar dice2 = 0);

    void setRollButtonsEnabled(bool rollOneEnabled, bool rollTwoEnabled);

    void setSkipButtonEnabled(bool enabled);

    void placeCards(CardList cards);

    void removeCards(CardList cards);

    void turnOnCardStack(uchar id);

    void turnOffCardStack(uchar id);

    QPushButton& getOneDiceButton();

    QPushButton& getTwoDiceButton();

    QPushButton& getSkipButton();

    CardScrollWidget* getLandmarkScrollWidget();

    CardScrollWidget* getBuildScrollWidget();

signals:
    void rollOneDiceClicked(uchar playerId);

    void rollTwoDiceClicked(uchar playerId);

    void skipClicked(uchar playerId);

    void cardClicked(uchar id);

public slots:
    void handleCardClicked(uchar id);

    void buttonBlocked();

private:
    void setupUi();

    void readCardData(const QString &configPath); // initial card set maybe shouldn't be here

    uchar m_playerId;
    QVBoxLayout *m_mainLayout;
    QScrollArea *m_landmarksScrollArea;
    QScrollArea *m_buildsScrollArea;
    QPushButton *m_rollOneDiceButton;
    QPushButton *m_rollTwoDiceButton;
    QPushButton *m_skipButton;
    QLabel *m_playerBalanceLabel;
    QLabel *m_diceResultLabel;
    CardScrollWidget* m_landmarkScrollWidget;
    CardScrollWidget* m_buildScrollWidget;
};

#endif // PLAYERPAGE_H
