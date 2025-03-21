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
    if (&owner != &activePlayer) {
        auto diningCards = owner.getCardsTableOfType(CardType::Dining);
        if (!diningCards.empty()) {
            int diningCount = 0;
            for (auto it = diningCards.begin(), ite = diningCards.end(); it != ite; ++it) {
                if (it.key()->activationValues().contains(dice1 + dice2)) {
                    diningCount += it.value(); // amount of cars in stack
                }
            }
            int moneyToTake = std::min(activePlayer.coins(), diningCount);
            activePlayer.deductMoney(moneyToTake);
            owner.addCoins(moneyToTake);

            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << moneyToTake;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << moneyToTake;
        }
    }

    if (&owner == &activePlayer) {
        auto shopCards = activePlayer.getCardsTableOfType(CardType::Shop);
        if (!shopCards.empty()) {
            int shopCount = 0;
            for (auto it = shopCards.begin(), ite = shopCards.end(); it != ite; ++it) {
                if (it.key()->activationValues().contains(dice1 + dice2)) {
                    shopCount += it.value(); // amount of cars in stack
                }
            }
            activePlayer.addCoins(shopCount);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " gain income: " << shopCount;
        }
    }
}
