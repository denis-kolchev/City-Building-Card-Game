#include "diceroller.h"

#include <QRandomGenerator>

DiceRoller::DiceRoller()
{
}

uchar DiceRoller::rollDice(uchar diceNumber)
{
    uchar total = 0;
    uchar maxDiceNumber = (UCHAR_MAX / m_diceSidesNumber > diceNumber) ? diceNumber : 42;
    for (uchar i = 0; i < diceNumber; ++i) {
        int roll = QRandomGenerator::global()->bounded(1, m_diceSidesNumber + 1);
        total += static_cast<uchar>(roll);
    }
    return total;
}
