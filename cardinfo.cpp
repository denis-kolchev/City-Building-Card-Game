#include "cardinfo.h"

CardInfo::CardInfo(QString name, QString operation, CardVariation cardVariation,
                   IncomeType incomeType, CardType cardType, int buildPrice,
                   uchar triggerRoll)
    : m_name(name), m_operation(operation), m_cardVariation(cardVariation),
    m_incomeType(incomeType), m_cardType(cardType), m_buildPrice(buildPrice),
    m_triggerRoll(triggerRoll)
{
}

int CardInfo::buildPrice()
{
    return m_buildPrice;
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

uchar CardInfo::triggerRoll()
{
    return m_triggerRoll;
}
