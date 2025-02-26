#include "card.h"

Card::Card(CardInfo info, QObject *parent)
    : m_info(info), QObject(parent)
{}


void Card::operate()
{

}
