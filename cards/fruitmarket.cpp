#include "fruitmarket.h"

FruitMarket::FruitMarket(const QString& title,
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

void FruitMarket::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        auto cards = owner.getCardsTable();
        for (auto it = cards.begin(), ite = cards.end(); it != ite; ++it) {
            uchar times = it.value();
            if (it.key()->type() == CardType::Agricultiral) {
                activePlayer.addCoins(2 * times);
            }
        }
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
