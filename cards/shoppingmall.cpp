#include "shoppingmall.h"

ShoppingMall::ShoppingMall(const QString& name, CardType type, int activationValue)
    : Card(name, type, activationValue) {}

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

    qDebug() << m_name << " activated! Landmark effect triggered.\n";
}
