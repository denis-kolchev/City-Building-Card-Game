#include "cafe.h"

Cafe::Cafe(const QString& title,
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


void Cafe::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (hasActivationValue(dice1 + dice2) && &owner != &activePlayer) {
        int available = activePlayer.coins();
        if (available >= 1) {
            activePlayer.deductMoney(1);
            owner.addCoins(1);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << 1;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 1;
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << available;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << available;
        }

    }
}
