#include "cafe.h"

Cafe::Cafe(const QString& title,
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


void Cafe::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner != &activePlayer) {
        int available = activePlayer.coins();
        if (available >= 1) {
            activePlayer.deductMoney(1);
            owner.addCoins(1);
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
        }

        qDebug() << m_title << " activated! " << activePlayer.name() << " pays " << owner.name() << ".\n";
    }
}
