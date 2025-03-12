#ifndef GAMELOGIC_H
#define GAMELOGIC_H

/**
 * @brief The GameLogic class
 * The game logic class is responsible for managing the game state,
 * processing player actions and handling win/loss conditions.
 *
 * Maybe add
 * Game State Management
 * initializeGame() → Sets up players, the board, and initial conditions.
 * resetGame() → Resets the game state for a new session.
 * getGameState() → Returns the current game state for UI updates.
 *
 * Player & Turn Management
 * nextTurn() → Advances the turn to the next player.
 * getCurrentPlayer() → Returns the player whose turn it is.
 * getPlayerStats(Player *player) → information like money, cards, or score.
 *
 * Utility & Event Handling
 * onPlayerAction(ActionType action) → when a player interacts with the UI.
 * checkWinCondition() → Determines if someone has won the game.
 */

#include "cardreserve.h"
#include "diceroller.h"
#include "player.h"

#include <QObject>
#include <QVector>
#include <QDebug>

class GameLogic : public QObject {
    Q_OBJECT

public:
    explicit GameLogic(QObject *parent = nullptr);

    ~GameLogic();

    int currentPlayerId() const;

    bool isGameIsFinished();

    Player& getPlayer(int id);

    void playTurn();

signals:
    void buildStageFinished(int currentPlayerId);

    void incomeStageFinished();

    void playerBalanceChanged(uchar balance);

    void playerBuildNewBuilding(std::shared_ptr<Card> card);

    void tryToBuyCard(QString cardTitle, uchar playerBalance);

public slots:
    void checkCoinBalanceForCard(QString cardTitle);

    void giveCardToPlayer(std::shared_ptr<Card> card);

    void handleCreatePlayers(QList<QString> playerNames);

    void handleRollButtonClicked(uchar diceRoll);

    void handleTryToBuyCard(QString cardTitle);

    void prepateNextTurn();

private:
    CardReserve* m_cardReserve;
    QVector<std::shared_ptr<Card>> m_cardsToWin;
    QVector<Player> m_players;
    DiceRoller m_roller;
    int m_currentPlayerId;
};

#endif // GAMELOGIC_H
