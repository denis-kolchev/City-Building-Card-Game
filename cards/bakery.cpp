#include "bakery.h"

Bakery::Bakery(const QString& title,
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

void Bakery::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        activePlayer.addCoins(1);
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
