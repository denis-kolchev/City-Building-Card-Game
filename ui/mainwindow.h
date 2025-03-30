#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFinalState>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStateMachine>
#include <QVBoxLayout>
#include <QtWidgets/qscrollarea.h>

#include "../carddataconfigreader.h"
#include "playerpage.h"

using CardsLayout = QHBoxLayout;

#ifdef false
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();
};
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();

public slots:
    void handleFinishIncomeState(int playerId); // set purchase state

    void handleFinishPurchaseState(int playerId); // set wait state

    void handleFinishWaitState(int playerId); // set income state

    void handleGameWon(int playerId);

    void handleRequestDiceRerollConfirmation(int playerId, QVector<int> rools);

    void handleShowMainWindow(int playersCount);

    void handleSwitchToPlayerTurn(int playerId); // set incomestate

    void receiveBankLoosesCard(std::shared_ptr<Card> card);

    void receiveBankGetsCard(std::shared_ptr<Card> card);

    void receiveCardPurchaseFailed(int playerId, CardId cardId, QString message);

    void receiveDiceRollResult(QVector<int> rolls);

    void receivePlayerBalanceChanged(int playerId, int balance);

    void receivePlayerGetsCard(int playerId, std::shared_ptr<Card> card);

    void receivePlayerLoosesCard(int playerId, std::shared_ptr<Card> card);

    void receiveRollTwoDiceAvailable(int playerId);

signals:
    void cardClickedForPurchase(CardId cardId);

    void createPlayers(int playerCount);

    void rollDiceButtonClicked(int diceRollCount);

    void sendDiceRerollResponse(QVector<int> rollResults, bool confirmed);

    void skipButtonClicked();

private:
    void centerWindow();

    QIcon createCircleIcon(const QColor color, qsizetype size = 32);

    PlayerPage* createPlayerPage(uchar playerId);

    void setupStateMachines();

    void setupTransitionsForPlayer(int playerId);

private slots:
    void handleCardClick(CardId id);

signals:
    void setIncomeState(int playerId);

    void setPurchaseState(int playerId);

    void setWaitState(int playerId);

private:
    struct PlayerStateMachine {
        QState *m_waitState;
        QState *m_incomeState;
        QState *m_purchaseState;
        QStateMachine *m_stateMachine;

        // Transitions
        QSignalTransition* toWaitState;
        QSignalTransition* toIncomeState;
        QSignalTransition* toPurchaseState;
    };

    QVector<PlayerStateMachine> m_playerStateMachines;

    QWidget *m_centralWidget; // this
    QHBoxLayout *m_mainLayout; // m_centralWidget
    QScrollArea *m_bankCardsArea;
    CardScrollWidget* m_bankScrollWidget;
    QHBoxLayout* m_bankLayout; // bankScrollWidget

    QVector<PlayerPage*> m_playerPages;

    QTabWidget *m_tabWidget;
    //QLabel* m_diceResult;

    QColor m_activePlayerColor = QColor(72, 181, 163);
    QColor m_inactivePlayerColor = QColor(252, 169, 133);
};


#endif // MAINWINDOW_H
