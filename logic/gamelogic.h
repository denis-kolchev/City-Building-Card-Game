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

    std::shared_ptr<Player> getPlayer(int id);

    void playTurn(uchar dice1, uchar dice2);

signals:
    void buildStageFinished(int currentPlayerId);

    void gameIsFinished(int playerId);

    void playerCardActivatedBefore(uchar dice1, uchar dice2);

    void playerHasAmusementPark();

    void playerHasNotEnoughCoins(QString message);

    void playerHasRadioTower();

    void playerHasRailwayStation();

    void playerBalanceChanged(uchar balance, int playerId);

    void playerBuildLandmark(std::shared_ptr<Card> card);

    void playerBuildNewBuilding(std::shared_ptr<Card> card);

    void requestCardData(int begin, int end, std::shared_ptr<CardDataHandler> handler);

    void requestReadFromRange(int begin, int end);

    void tryToBuyCard(uchar cardId, uchar playerBalance);

public slots:
    void checkCoinBalanceForCard(uchar cardId);

    void processCheckPlayerCards(uchar cardId, int playerId, uchar dice1, uchar dice2);

    void giveCardToPlayer(std::shared_ptr<Card> card);

    void handleCardDataReceived(QVector<std::shared_ptr<Card>> data);

    void handleConfigDataReady();

    void handleCreatePlayers(QList<QString> playerNames);

    void handlePlayerHasAmusementPark();

    void handlePlayerHasRadioTower();

    void handlePlayerHasRailwayStation();

    void handleRollButtonClicked(uchar dice1, uchar dice2);

    void handleTryToBuyCard(uchar cardId);

    void moveToNextPlaer();

    void prepateNextTurn();

private:
    std::shared_ptr<CardInventory> m_bank;
    QVector<std::shared_ptr<Card>> m_cardsToWin;
    QVector<std::shared_ptr<Player>> m_players;
    DiceRoller m_roller;
    int m_currentPlayerId;
};

#endif // GAMELOGIC_H
