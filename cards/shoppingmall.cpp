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


void ShoppingMall::activate(Player& owner, Player& activePlayer, int diceRoll) {
    // Landmark-specific logic
    auto allCards = owner.getCards();
    int count = 0;
    for (auto& card : allCards) {
        if (card->type() == CardType::Dining || card->type() == CardType::Shop) {
            count++;
        }
    }

    owner.addCoins(count);

    qDebug() << m_title << " activated! Landmark effect triggered.\n";
}
