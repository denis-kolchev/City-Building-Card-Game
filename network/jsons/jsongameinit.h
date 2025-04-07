#ifndef JSONGAMEINIT_H
#define JSONGAMEINIT_H

#include "abstractjsonstrategy.h"

class JsonGameInit : public AbstractJsonStrategy
{
public:
    JsonGameInit(int playerCount);

    QJsonObject json() override;

private:
    int m_playerCount;
};

#endif // JSONGAMEINIT_H
