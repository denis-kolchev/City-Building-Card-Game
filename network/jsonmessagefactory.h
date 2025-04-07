#ifndef JSONMESSAGEFACTORY_H
#define JSONMESSAGEFACTORY_H

#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

class JsonMessageFactory {
public:
    // ----------------------- Game State Management -----------------------
    static QJsonObject createGameInit(const QString& sender,
                                      int playerCount);

    static QJsonObject createPlayerTurnChange(const QString& sender,
                                              int playerId);

    static QJsonObject createGameOver(const QString& sender,
                                      int winnerId);

    // -------------------------- Card Operations --------------------------
    static QJsonObject createCardTransfer(const QString& sender,
                                          const QString& from,
                                          const QString& to,
                                          int cardId,
                                          const QString& cardType,
                                          const QString& cardName,
                                          int cardValue);

    static QJsonObject createCardPurchaseAttempt(const QString& sender,
                                                 int playerId,
                                                 int cardId);

    static QJsonObject createCardPurchaseFailed(const QString& sender,
                                                int playerId,
                                                int cardId,
                                                const QString& reason);

    // -------------------------- Dice Operations --------------------------
    static QJsonObject createDiceRollRequest(const QString& sender,
                                             int playerId,
                                             int diceCount);

    static QJsonObject createDiceRollResult(const QString& sender,
                                            int playerId,
                                            const QList<int>& results,
                                            int total);

    static QJsonObject createDiceRerollConfirmation(const QString& sender,
                                                    int playerId,
                                                    const QList<int>& originalRoll,
                                                    bool confirmed);

    // Player Actions
    static QJsonObject createBalanceChange(const QString& sender,
                                           int playerId,
                                           double amount,
                                           double newBalance);

    static QJsonObject createPlayerStateChange(const QString& sender,
                                               int playerId,
                                               const QString& newState);

private:
    static QJsonObject createBaseMessage(const QString& type,
                                         const QString& sender,
                                         const QJsonObject& data);
};

#endif // JSONMESSAGEFACTORY_H
