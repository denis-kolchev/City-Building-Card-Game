#include "bakery.h"

Bakery::Bakery(const QString& title,
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

void Bakery::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        activePlayer.addCoins(1);
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
