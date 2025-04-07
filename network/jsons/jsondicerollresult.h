#ifndef JSONDICEROLLRESULT_H
#define JSONDICEROLLRESULT_H

#include "abstractjsonstrategy.h"

class JsonDiceRollResult : public AbstractJsonStrategy
{
public:
    JsonDiceRollResult(int playerId, QVector<int> diceResult);

    QJsonObject json() override;

private:
    int m_playerId;
    QVector<int> m_diceResult;
};

#endif // JSONDICEROLLRESULT_H
