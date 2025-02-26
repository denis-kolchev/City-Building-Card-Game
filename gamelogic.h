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

    void endGame();

    //getPlayerStates(Player *player);

    void processTurn();

    void updateGameState();


private:
    void applyDiceResult(int result, Player *player = nullptr);

    void performPlayerAction(ActionType, Player *player = nullptr);
};

#endif // GAMELOGIC_H
