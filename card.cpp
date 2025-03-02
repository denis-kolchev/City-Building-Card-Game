#include "card.h"

Card::Card(QString name,
           QString description,
           IncomeType incomeType,
           CardType cardType,
           ActionSource actionSource,
           uchar price,
           QSet<uchar> triggerRolls,
           QObject *parent)
    : m_name(name)
    , m_description(description)
    , m_incomeType(incomeType)
    , m_cardType(cardType)
    , m_price(price)
    , m_triggerRolls(triggerRolls)
    , m_actionSource(actionSource)
    , QObject(parent)
{
}

Card::~Card()
{
}

void Card::action(Player& activePlayer,
                  QVector<Player*>& otherPlayers)
{
    emit applyAction(activePlayer, otherPlayers, m_actionSource);
}

bool Card::canTrigger(uchar currentRoll)
{
    auto triggerRolls = m_triggerRolls;
    return triggerRolls.find(currentRoll) == triggerRolls.end();
}

QString Card::description()
{
    return m_description;
}

QString Card::name()
{
    return m_name;
}

uchar Card::price()
{
    return m_price;
}
