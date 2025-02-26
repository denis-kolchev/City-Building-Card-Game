#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <QtCore/qtypes.h>

class DiceRoller
{
public:
    DiceRoller();

    uchar rollDice(uchar diceNumber);

private:
    const uchar m_diceSidesNumber = 6;

};

#endif // DICEROLLER_H
