#include "cardinfo.h"

CardInfo::CardInfo(QString name, QString operation, CardVariation cardVariation,
                   IncomeType incomeType, CardType cardType, int buildPrice,
                   uchar triggerRoll, bool isBuild)
    : m_name(name), m_operation(operation), m_cardVariation(cardVariation),
    m_incomeType(incomeType), m_cardType(cardType), m_buildPrice(buildPrice),
    m_triggerRoll(triggerRoll)
{

}
