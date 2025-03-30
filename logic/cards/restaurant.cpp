#include "restaurant.h"

Restaurant::Restaurant(const QString& title,
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

void Restaurant::activate(QVector<std::shared_ptr<Player>>& players,
                          Player& owner,
                          Player& activePlayer,
                          int dice1,
                          int dice2)
{
    if (hasActivationValue(dice1 + dice2) && &owner != &activePlayer) {
        int available = activePlayer.balance();
        int nCoinsToTake = 2;
        if (available >= nCoinsToTake) {
            activePlayer.deductMoney(nCoinsToTake);
            owner.addCoins(nCoinsToTake);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << available;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << available;
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << 2;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 2;
        }
    }
}
