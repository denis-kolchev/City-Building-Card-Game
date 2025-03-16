#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFinalState>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStateMachine>
#include <QVBoxLayout>

#include "carddataconfigreader.h"
#include "cardstackwidget.h"
#include "soundmanager.h"

using CardsLayout = QHBoxLayout;
using CardsList = QVector<std::shared_ptr<Card>>;
using CardsStack = QMap<QString, CardStackWidget*>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();

public slots:
    void displayPlayerNewCard(std::shared_ptr<Card> card);

    void finishGame(int currentPlayerId);

    void handleShowMainWindow(uchar numPlayers);

    void repaintPlayerPanel(int currentPlayerId);

    void unlockBuildAgainIfDubleRollDice();

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

    void cardWidgetClicked(QString cardTitle);

    void createPlayers(QList<QString> playerNames);

    void rollButtonClicked(uchar dice1, uchar dice2);

    void skipClicked();

    void takeCardSound();

    void updatedPlayersPanel();

private slots:
    void handleCardClick(QString cardTitle);

    void onRollOneDiceClicked();

    void onRollTwoDiceClicked();

    void onSkipClicked();

private:
    QWidget* createPlayerView(uchar playerId);

    void placeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack);

    void removeCards(CardsList &cards, CardsLayout &layout, CardsStack &cardStack);

    void setupStateMachine();

    void updateButtonStates();

private:
    SoundManager *m_soundManager;

    QStateMachine *m_stateMachine;
    QState *m_incomeState;
    QState *m_buyingState;
    QFinalState *m_finalState;

    CardsStack m_reserveCardsStack;
    QVector<CardsStack> m_landmarkCardStacks;
    QVector<CardsStack> m_playerCardStacks;
    QVector<QLabel*> m_playerBalanceLabels;
    QVector<QLabel*> m_diceResultLabels;
    QHBoxLayout* m_reserveLayout;
    QVector<QHBoxLayout*> m_buildsLayout;
    QVector<QHBoxLayout*> m_landmarksLayout;
    QVector<QPushButton*> m_rollOneDiceButtons;
    QVector<QPushButton*> m_rollTwoDiceButtons;
    QVector<QPushButton*> m_skipButtons;
    QVector<bool> m_canPressTwoDiceButton;
    QVector<bool> m_canBuildAgainIfDubleRollDice;
    QTabWidget *m_tabWidget;
    int m_numPlayers;
    int m_currentPlayerId;
};
#endif // MAINWINDOW_H
