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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow();

    CardScrollWidget* getBankScrollWidget() const;

public slots:
    bool askForReroll(QWidget* parent);

    void displayBankGetsCard(std::shared_ptr<Card> card);

    void displayBankLoosesCard(std::shared_ptr<Card> card);

    void displayPlayerGetsCard(int playerId, std::shared_ptr<Card> card);

    void displayPlayerLoosesCard(int playerId, std::shared_ptr<Card> card);

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

    void updatePlayerBalanceLabel(uchar balance, int playerId);

signals:
    void activateCardsHighlighting(int playerBalance);

    void buildOneMoreBuilding();

    void buttonClickSound();

    void buyButtonClicked();

    void cardFailSound();

    void cardTurnSound();

    void cardWidgetClicked(uchar cardId);

    void checkPlayerCards(uchar cardId, int playerId, uchar dice1, uchar dice2);

    void createPlayers(QList<QString> playerNames);

    void deactivateCardsHighlighting();

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

    QIcon createCircleIcon(const QColor color, qsizetype size = 32);

private:
    void centerWindow();

    PlayerPage* createPlayerPage(uchar playerId);

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
    QScrollArea *m_bankCardsArea;
    CardScrollWidget* m_bankScrollWidget;
    QHBoxLayout* m_bankLayout; // bankScrollWidget

    QVector<PlayerPage*> m_playerPages;

    QVector<int> m_canPressTwoDiceButton;
    QVector<int> m_canBuildAgainIfDubleRollDice;
    QVector<int> m_canRerollDice;
    QTabWidget *m_tabWidget;
};
#endif // MAINWINDOW_H
