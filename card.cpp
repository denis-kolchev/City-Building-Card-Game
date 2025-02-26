#include "card.h"

Card::Card(CardInfo info, QObject *parent)
    : m_info(info), QObject(parent)
{
}

uchar Card::buildPrice()
{
    return m_info.buildPrice();
}

bool Card::canTrigger(uchar currentRoll)
{
    auto triggerRolls = this->triggerRolls();
    return triggerRolls.find(currentRoll) == triggerRolls.end();
}

IncomeType Card::incomeType()
{
    return m_info.incomeType();
}

QString Card::name()
{
    return m_info.name();
}

void Card::operate()
{

}

QString Card::operation()
{
    return m_info.operation();
}

QSet<uchar> Card::triggerRolls()
{
    return m_info.triggerRolls();
}

CardVariation Card::variation()
{
    return m_info.cardVariation();
}
