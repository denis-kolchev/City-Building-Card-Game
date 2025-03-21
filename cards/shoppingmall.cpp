#include "shoppingmall.h"

ShoppingMall::ShoppingMall(const QString& title,
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


void ShoppingMall::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    auto allCards = owner.getCardsTable();
    int diningCount = 0;
    int shopCount = 0;
    for (auto it = allCards.begin(), ite = allCards.end(); it != ite; ++it) {
        if (it.key()->hasActivationValue(dice1 + dice2) && it.key()->type() == CardType::Dining) {
            diningCount++;
        }
        if (&owner == &activePlayer && it.key()->type() == CardType::Shop) {
            shopCount++;
        }
    }

    owner.addCoins(shopCount);

    if (&owner != &activePlayer) {
        int balance = activePlayer.coins();
        if (balance >= diningCount) {
            activePlayer.deductMoney(diningCount);
            owner.addCoins(diningCount);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << diningCount;
        } else {
            activePlayer.deductMoney(balance);
            owner.addCoins(balance);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << balance;
        }
    }

    qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << diningCount + shopCount;
}
