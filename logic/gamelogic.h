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

#include "../carddataconfigreader.h"
#include "bank.h"
#include "diceroller.h"
#include "player.h"

#include <QObject>
#include <QVector>
#include <QDebug>

// Make unable buttons invisible
class GameLogic : public QObject
{
    Q_OBJECT

public:
    explicit GameLogic(QObject *parent = nullptr);

    ~GameLogic();

signals:
    void gameWon(int playerId);

    void requestCardData(CardId startCardId,
                         CardId finishCardId,
                         std::shared_ptr<CardDataHandler> handler);

    void requestDiceRerollConfirmation(int playerId, QVector<int> rools);

    void sendBankGetsCard(std::shared_ptr<Card> card);

    void sendBankLoosesCard(std::shared_ptr<Card> card);

    void sendCardPurchaseFailed(int playerId, CardId cardId, QString message);

    void sendDiceRollResult(QVector<int> rolls);

    void sendPlayerBalanceChanged(int playerId, int balance);

    void sendPlayerGetsCard(int playerId, std::shared_ptr<Card> card);

    void sendPlayerLoosesCard(int playerId, std::shared_ptr<Card> card);

    void sendRollTwoDiceAvailable(int playerId);

    void switchToPlayerTurn(int playerId);

    void finishIncomeState(int playerId);

    void finishPurchaseState(int playerId);

    void finishWaitState(int playerId);

public slots:
    void handleCardClickedForPurchase(CardId cardId);

    void handleConfigDataReadyToRead();

    void handleCreatePlayers(int playerCount);

    void handleRollDiceButtonClicked(int diceRollCount);

    void handleSkipButtonClicked();

    void receiveDiceRerollResponse(QVector<int> rollResults, bool confirmed);

private:
    void activatePlayersCards(QVector<int> rollResults);

    void checkWinCondition();

    void purchaseCard(std::shared_ptr<Card> card);

    void resetPlayerTurnState();

    void rollDice(int diceRollCount);

    void setupCurrentPlayerSpecialAbilities();

private:
    std::shared_ptr<Bank> m_bank;
    QVector<std::shared_ptr<Player>> m_players;
    DiceRoller m_diceRoller;
    QVector<CardId> m_cardToWinIds;
    int m_currentPlayerId;
};

#endif // GAMELOGIC_H
