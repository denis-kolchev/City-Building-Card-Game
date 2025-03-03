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

#include "diceroller.h"
#include "player.h"

#include <QVector>
#include <QDebug>

class GameLogic {
public:
    GameLogic(const QVector<QString>& playerNames);

    Player& getPlayer(int id);

    void playTurn();

private:
    QVector<Player> m_players;
    int m_currentPlayerId;
    DiceRoller m_roller;

};

#endif // GAMELOGIC_H
