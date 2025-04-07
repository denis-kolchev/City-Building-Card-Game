#ifndef JSONGAMEOVER_H
#define JSONGAMEOVER_H

#include "abstractjsonstrategy.h"

class JsonGameOver : public AbstractJsonStrategy
{
public:
    JsonGameOver(int winnderId);

    QJsonObject json() override;

private:
    int m_winnderId;
};

#endif // JSONGAMEOVER_H
