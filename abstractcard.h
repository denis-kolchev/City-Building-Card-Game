#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include "cardinfo.h"

class AbstractCard
{
    IncomeType virtual incomeType() = 0;
    CardVariation virtual variation() = 0;
    void virtual operate() = 0;
};

#endif // ABSTRACTCARD_H
