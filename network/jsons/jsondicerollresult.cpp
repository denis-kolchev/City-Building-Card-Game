#include "jsondicerollresult.h"

#include <QJsonArray>
#include <QVariantList>

JsonDiceRollResult::JsonDiceRollResult(int playerId, QVector<int> diceResult)
    : m_playerId(playerId)
    , m_diceResult(diceResult)
    , AbstractJsonStrategy("dice_roll_result")
{
}

QJsonObject JsonDiceRollResult::json()
{
    // Convert QVector<int> to QJsonArray
    QJsonArray resultsArray;
    for (int value : std::as_const(m_diceResult)) {
        resultsArray.append(value);
    }

    return {
        {"type", type()},
        {"timestamp", QDateTime::currentDateTime().toString(Qt::ISODate)},
        {"data", QJsonObject {
                     {"player_id", m_playerId},
                     {"results", resultsArray}
                 }}
    };
}
