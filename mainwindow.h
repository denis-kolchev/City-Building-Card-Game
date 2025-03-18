#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFinalState>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStateMachine>
#include <QVBoxLayout>
#include <QtWidgets/qscrollarea.h>

#include "carddataconfigreader.h"
#include "cardstackwidget.h"

using CardsLayout = QHBoxLayout;
using CardsList = QVector<std::shared_ptr<Card>>;
using CardsStack = QMap<uchar, CardStackWidget*>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();

public slots:
    bool askForReroll(QWidget* parent);

    void displayPlayerNewCard(std::shared_ptr<Card> card);

    void displayWorningWindow(QString message);

    void finishGame(int currentPlayerId);

    void handlePlayerCardActivatedBefore(uchar dice1, uchar dice2);

    void handleShowMainWindow(uchar numPlayers);

    void processDiceRoll(uchar dice1, uchar dice2);

    void repaintPlayerPanel(int currentPlayerId);

    void unlockBuildAgainIfDubleRollDice();

    void unlockDiceReroll();

    void unlockPlayerLandmark(std::shared_ptr<Card> card);

    void unlockRollTwoDiceButton();

    void updateDiceResultLabel(uchar dice);

    void updatePlayerBalanceLabel(uchar balance, int playerId);

signals:
    void buildOneMoreBuilding();

    void buttonClickSound();

    void buyButtonClicked();

    void cardFailSound();

    void cardTurnSound();

    void cardWidgetClicked(uchar cardId);

    void checkPlayerCards(uchar cardId, int playerId, uchar dice1, uchar dice2);

    void createPlayers(QList<QString> playerNames);

    void diceRollAccepted(uchar dice1, uchar dice2);

    void rollButtonClicked(uchar dice1, uchar dice2);

    void rollButtonClickedWithCanReroll(uchar dice1, uchar dice2);

    void skipClicked();

    void takeCardSound();

    void updatedPlayersPanel();

private slots:
    void handleCardClick(uchar cardId);

    void onRollOneDiceClicked();

    void onRollTwoDiceClicked();

    void onSkipClicked();

private:
    void centerWindow();

    QWidget* createPlayerView(uchar playerId);

    void placeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack);

    void removeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack);

    void setupStateMachine();

    void updateButtonStates();

private:
    int m_numPlayers;
    int m_currentPlayerId;

    QStateMachine *m_stateMachine;
    QState *m_incomeState;
    QState *m_buyingState;
    QState *m_buyOrRerollState;
    QFinalState *m_finalState;

    QWidget *m_centralWidget; // this
    QHBoxLayout *m_mainLayout; // m_centralWidget
    QScrollArea *m_reserveCardsArea;
    QWidget *m_reserveScrollWidget;
    QHBoxLayout* m_reserveLayout; // reserveScrollWidget

    QVector<QWidget*> m_playerViews;

    CardsStack m_reserveCardsStack;
    QVector<QVBoxLayout*> m_viewCardsLayouts;
    QVector<QScrollArea*> m_landmarksScrollAreas;
    QVector<QScrollArea*> m_playersBuildsAreas;
    QVector<QWidget*> m_landmarksScrollWidgets;
    QVector<QWidget*> m_playersBuildsScrollWidgets;
    QVector<QHBoxLayout*> m_buttonLayouts;
    QVector<QVBoxLayout*> m_actionLayouts;
    QVector<QHBoxLayout*> m_labelLayouts;
    QVector<QWidget*> m_actionWidgets;

    QVector<CardsStack> m_landmarkCardStacks;
    QVector<CardsStack> m_playerCardStacks;
    QVector<QLabel*> m_playerBalanceLabels;
    QVector<QLabel*> m_diceResultLabels;
    QVector<QHBoxLayout*> m_buildsLayout;
    QVector<QHBoxLayout*> m_landmarksLayout;
    QVector<QPushButton*> m_rollOneDiceButtons;
    QVector<QPushButton*> m_rollTwoDiceButtons;
    QVector<QPushButton*> m_skipButtons;
    QVector<bool> m_canPressTwoDiceButton;
    QVector<bool> m_canBuildAgainIfDubleRollDice;
    QVector<bool> m_canRerollDice;
    QTabWidget *m_tabWidget;
};
#endif // MAINWINDOW_H
