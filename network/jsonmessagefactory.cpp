#include "jsonmessagefactory.h"

QJsonObject JsonMessageFactory::createGameInit(const QString& sender,
                                               int playerCount)
{
    QJsonObject data;
    data["player_count"] = playerCount;

    return createBaseMessage("game_init", sender, data);
}

QJsonObject JsonMessageFactory::createPlayerTurnChange(const QString& sender,
                                                       int playerId)
{
    QJsonObject data;
    data["player_id"] = playerId;

    return createBaseMessage("player_turn_change", sender, data);
}

QJsonObject JsonMessageFactory::createGameOver(const QString& sender,
                                               int winnerId)
{
    QJsonObject data;
    data["winner_id"] = winnerId;

    return createBaseMessage("game_over", sender, data);
}

// Card Operations
QJsonObject JsonMessageFactory::createCardTransfer(const QString& sender,
                                                   const QString& from,
                                                   const QString& to,
                                                   int cardId,
                                                   const QString& cardType,
                                                   const QString& cardName,
                                                   int cardValue)
{
    QJsonObject card;
    card["id"] = cardId;
    card["type"] = cardType;
    card["name"] = cardName;
    card["value"] = cardValue;

    QJsonObject data;
    data["from"] = from;
    data["to"] = to;
    data["card"] = card;

    return createBaseMessage("card_transfer", sender, data);
}

QJsonObject JsonMessageFactory::createCardPurchaseAttempt(const QString& sender,
                                                          int playerId,
                                                          int cardId)
{
    QJsonObject data;
    data["player_id"] = playerId;
    data["card_id"] = cardId;

    return createBaseMessage("card_purchase_attempt", sender, data);
}

QJsonObject JsonMessageFactory::createCardPurchaseFailed(const QString& sender,
                                                         int playerId,
                                                         int cardId,
                                                         const QString& reason)
{
    QJsonObject data;
    data["player_id"] = playerId;
    data["card_id"] = cardId;
    data["reason"] = reason;

    return createBaseMessage("card_purchase_failed", sender, data);
}

// Dice Operations
QJsonObject JsonMessageFactory::createDiceRollRequest(const QString& sender,
                                                      int playerId,
                                                      int diceCount)
{
    QJsonObject data;
    data["player_id"] = playerId;
    data["dice_count"] = diceCount;

    return createBaseMessage("dice_roll_request", sender, data);
}

QJsonObject JsonMessageFactory::createDiceRollResult(const QString& sender,
                                                     int playerId,
                                                     const QList<int>& results,
                                                     int total)
{
    QJsonArray resultsArray;
    for (int result : results) {
        resultsArray.append(result);
    }

    QJsonObject data;
    data["player_id"] = playerId;
    data["results"] = resultsArray;
    data["total"] = total;

    return createBaseMessage("dice_roll_result", sender, data);
}

QJsonObject JsonMessageFactory::createDiceRerollConfirmation(const QString& sender,
                                                             int playerId,
                                                             const QList<int>& originalRoll,
                                                             bool confirmed)
{
    QJsonArray originalRollArray;
    for (int roll : originalRoll) {
        originalRollArray.append(roll);
    }

    QJsonObject data;
    data["player_id"] = playerId;
    data["original_roll"] = originalRollArray;
    data["confirmed"] = confirmed;

    return createBaseMessage("dice_reroll_confirmation", sender, data);
}

// Player Actions
QJsonObject JsonMessageFactory::createBalanceChange(const QString& sender,
                                                    int playerId,
                                                    double amount,
                                                    double newBalance)
{
    QJsonObject data;
    data["player_id"] = playerId;
    data["amount"] = amount;
    data["new_balance"] = newBalance;

    return createBaseMessage("balance_change", sender, data);
}

QJsonObject JsonMessageFactory::createPlayerStateChange(const QString& sender,
                                                        int playerId,
                                                        const QString& newState)
{
    QJsonObject data;
    data["player_id"] = playerId;
    data["new_state"] = newState;

    return createBaseMessage("player_state_change", sender, data);
}

QJsonObject JsonMessageFactory::createBaseMessage(const QString& type,
                                                  const QString& sender,
                                                  const QJsonObject& data)
{
    QJsonObject message;
    message["type"] = type;
    message["timestamp"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs);
    message["sender"] = sender;
    message["data"] = data;
    return message;
}
