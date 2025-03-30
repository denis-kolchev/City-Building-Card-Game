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
    explicit PlayerPage(int playerId, QWidget *parent = nullptr);

    int balance();

    void setPlayerBalance(int balance);

    void setDiceResult(int dice1, int dice2 = 0);

    void setRollButtonsEnabled(bool rollOneEnabled, bool rollTwoEnabled);

    void setSkipButtonEnabled(bool enabled);

    void placeCards(CardList cards);

    void removeCards(CardList cards);

    void turnOnCardStack(CardId id);

    void turnOffCardStack(CardId id);

    QPushButton& getOneDiceButton();

    QPushButton& getTwoDiceButton();

    QPushButton& getSkipButton();

    CardScrollWidget* getLandmarkScrollWidget();

    CardScrollWidget* getBuildScrollWidget();

signals:
    void activateCardsHighlighting(int playerBalance);

    void deactivateCardsHighlighting();

    void rollOneDiceClicked(int playerId);

    void rollTwoDiceClicked(int playerId);

    void skipClicked(int playerId);

    void cardClicked(CardId id);

public slots:
    void handleCardClicked(CardId id);

    void buttonBlocked();

private:
    void setupUi();

    int m_playerId;
    int m_playerBalance;
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
