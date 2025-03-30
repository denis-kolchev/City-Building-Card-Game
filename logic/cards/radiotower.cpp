#include "radiotower.h"

RadioTower::RadioTower(const QString& title,
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

void RadioTower::activate(QVector<std::shared_ptr<Player>>& players,
                          Player& owner,
                          Player& activePlayer,
                          int dice1,
                          int dice2)
{
    if (&owner == &activePlayer) {
        //activePlayer.activateRerollDice();
        qDebug() << "--- " << m_title << " - " << owner.name() << " can reroll the dice once";
    }
}
