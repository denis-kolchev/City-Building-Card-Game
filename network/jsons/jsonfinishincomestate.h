#ifndef JSONFINISHINCOMESTATE_H
#define JSONFINISHINCOMESTATE_H

#include "abstractjsonstrategy.h"

class JsonFinishIncomeState : public AbstractJsonStrategy
{
public:
    JsonFinishIncomeState(int playerId);

    QJsonObject json() override;

private:
    int m_playerId;

};

#endif // JSONFINISHINCOMESTATE_H
