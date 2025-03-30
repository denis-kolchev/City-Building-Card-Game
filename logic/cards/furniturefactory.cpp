#include "furniturefactory.h"

FurnitureFactory::FurnitureFactory(const QString& title,
                                   const QString& description,
                                   const QString& imagePath,
                                   const QSet<int>& activationValues,
                                   CardType type,
                                   int pack,
                                   int price,
                                   CardId id)
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

void FurnitureFactory::activate(QVector<std::shared_ptr<Player>>& players,
                                Player& owner,
                                Player& activePlayer,
                                int dice1,
                                int dice2)
{
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        auto cards = owner.getCards();
        for (auto it = cards.begin(), ite = cards.end(); it != ite; ++it) {
            int times = it.value();
            if (it.key()->type() == CardType::Mining) {
                activePlayer.addCoins(3 * times);
            }
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 3 * times;
        }
    }
}
