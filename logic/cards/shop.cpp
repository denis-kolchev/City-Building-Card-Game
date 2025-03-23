#include "shop.h"

Shop::Shop(const QString& title,
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

void Shop::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        activePlayer.addCoins(3);
        qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 3;
    }
}
