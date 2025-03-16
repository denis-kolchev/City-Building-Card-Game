#include "restaurant.h"

Restaurant::Restaurant(const QString& title,
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

void Restaurant::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner != &activePlayer) {
        int available = activePlayer.coins();
        uchar nCoinsToTake = 2;
        if (available >= nCoinsToTake) {
            activePlayer.deductMoney(nCoinsToTake);
            owner.addCoins(nCoinsToTake);
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
        }

        qDebug() << m_title << " activated! " << activePlayer.name() << " pays " << owner.name() << ".\n";
    }
}
