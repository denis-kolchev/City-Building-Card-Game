#include "diceroller.h"

#include <QRandomGenerator>

DiceRoller::DiceRoller()
{
}

int DiceRoller::rollDice(int diceNumber)
{
    int total = 0;
    int maxDiceNumber = (INT_MAX / m_diceSidesNumber > diceNumber) ? diceNumber : 42;
    for (int i = 0; i < diceNumber; ++i) {
        int roll = QRandomGenerator::global()->bounded(1, m_diceSidesNumber + 1);
        total += static_cast<int>(roll);
    }
    return total;
}
