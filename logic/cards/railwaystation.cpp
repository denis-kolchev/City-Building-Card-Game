#include "railwaystation.h"

RailwayStation::RailwayStation(const QString& title,
                               const QString& description,
                               const QString& imagePath,
                               const QSet<int>& activationValues,
                               CardType type,
                               int pack,
                               int price,
                               CardId id)
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

void RailwayStation::activate(QVector<std::shared_ptr<Player>>& players,
                              Player& owner,
                              Player& activePlayer,
                              int dice1,
                              int dice2)
{
    //activePlayer.activateRollTwoDice();
    qDebug() << "--- " << m_title << " - " << owner.name() << " can drop the dice 2 times";
}
