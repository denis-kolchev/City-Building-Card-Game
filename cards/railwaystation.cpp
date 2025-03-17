#include "railwaystation.h"

RailwayStation::RailwayStation(const QString& title,
                               const QString& description,
                               const QString& imagePath,
                               const QSet<uchar>& activationValues,
                               CardType type,
                               uchar pack,
                               uchar price,
                               uchar id)
    : Card(title,
           description,
           imagePath,
           activationValues,
           type,
           pack,
           price,
           id)
{
}

void RailwayStation::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    activePlayer.activateRollTwoDice();
    qDebug() << m_title << " activated! " << owner.name();
}
