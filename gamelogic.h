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

#include <QObject>

#include "diceroller.h"
#include "cardreserve.h"
#include "player.h"

enum class ActionType
{
    RollDice,
    BuyCard,
    // ...
};

class Player;

class GameLogic final : public QObject
{
    Q_OBJECT
public:
    GameLogic(QObject *parent = nullptr);



    //getPlayerStates(Player *player);

    void processTurn();

    void updateGameState();

    //bool isGameFinished();

signals:
    void endGame();

public slots:
    void handleCardEffect(Player *m_activePlayer, Player* m_players);

private:
    void setNextPlayer();

    void applyDiceResult(int result, Player *player = nullptr);

    void performPlayerAction(ActionType, Player *player = nullptr);

private:
    QVector<Player*> m_players;
    Player* m_activePlayer;
    CardReserve* m_reserve;
    DiceRoller m_roller;
};

#endif // GAMELOGIC_H
