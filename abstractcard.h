#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include "cardinfo.h"
#include "gamestate.h"

class AbstractCard
{
    uchar virtual buildPrice() = 0;

    bool virtual canTrigger(uchar currentRoll) = 0;

    IncomeType virtual incomeType() = 0;

    QString virtual name() = 0;

    void virtual operate(GameState gameState) = 0;

    QString virtual operation() = 0;

    QSet<uchar> virtual triggerRolls() = 0;

    CardVariation virtual variation() = 0;
};

#endif // ABSTRACTCARD_H
