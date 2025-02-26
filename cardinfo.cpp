#include "cardinfo.h"

CardInfo::CardInfo(QString name, QString operation, CardVariation cardVariation,
                   IncomeType incomeType, CardType cardType, int buildPrice,
                   QSet<uchar> triggerRolls)
    : m_name(name), m_operation(operation), m_cardVariation(cardVariation),
    m_incomeType(incomeType), m_cardType(cardType), m_buildPrice(buildPrice),
    m_triggerRolls(triggerRolls)
{
}

int CardInfo::buildPrice()
{
    return m_buildPrice;
}

bool CardInfo::canTrigger(uchar currentRoll)
{
    return m_triggerRolls.find(currentRoll) == m_triggerRolls.end();
}

CardType CardInfo::cardType()
{
    return m_cardType;
}

CardVariation CardInfo::cardVariation()
{
    return m_cardVariation;
}

IncomeType CardInfo::incomeType()
{
    return m_incomeType;
}

QString CardInfo::name()
{
    return m_name;
}

QString CardInfo::operation()
{
    return m_operation;
}

QSet<uchar> CardInfo::triggerRolls()
{
    return m_triggerRolls;
}
