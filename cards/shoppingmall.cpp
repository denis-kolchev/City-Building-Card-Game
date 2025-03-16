#include "shoppingmall.h"

ShoppingMall::ShoppingMall(const QString& title,
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


void ShoppingMall::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    auto allCards = owner.getCardsTable();
    int count = 0;
    for (auto it = allCards.begin(), ite = allCards.end(); it != ite; ++it) {
        if ((it.key()->type() == CardType::Dining ||
             it.key()->type() == CardType::Shop) &&
             it.key()->hasActivationValue(dice1 + dice2))
        {
            count++;
        }
    }

    owner.addCoins(count);

    qDebug() << m_title << " activated! Landmark effect triggered.\n";
}
