#include "shop.h"

Shop::Shop(const QString& title,
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

void Shop::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        activePlayer.addCoins(3);
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
