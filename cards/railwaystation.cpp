#include "railwaystation.h"

RailwayStation::RailwayStation(const QString& title,
                               const QString& description,
                               const QString& imagePath,
                               const QSet<uchar>& activationValues,
                               CardType type,
                               uchar pack,
                               uchar price)
    : Card(title,
           description,
           imagePath,
           activationValues,
           type,
           pack,
           price)
{
}

void RailwayStation::activate(Player& owner, Player& activePlayer, int diceRoll) {
    activePlayer.activateRollTwoDice();
    qDebug() << m_title << " activated! " << owner.name();
}
