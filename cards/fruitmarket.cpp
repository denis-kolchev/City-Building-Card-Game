#include "fruitmarket.h"

FruitMarket::FruitMarket(const QString& title,
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

void FruitMarket::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        auto cards = owner.getCards();
        for (auto it = cards.begin(), ite = cards.end(); it != ite; ++it) {
            uchar times = it.value();
            if (it.key()->type() == CardType::Agricultural) {
                activePlayer.addCoins(2 * times);
            }
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 2 * times;
        }
    }
}
