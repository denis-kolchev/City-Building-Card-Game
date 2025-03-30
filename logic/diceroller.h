#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <QtTypes>

class DiceRoller
{
public:
    DiceRoller();

    int rollDice(int diceNumber = 6);

private:
    const int m_diceSidesNumber = 6;

};

#endif // DICEROLLER_H
