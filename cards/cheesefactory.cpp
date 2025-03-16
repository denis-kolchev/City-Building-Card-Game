#include "cheesefactory.h"

CheeseFactory::CheeseFactory(const QString& title,
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

void CheeseFactory::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        auto cards = owner.getCardsTable();
        for (auto it = cards.begin(), ite = cards.end(); it != ite; ++it) {
            uchar times = it.value();
            if (it.key()->type() == CardType::Farm) {
                activePlayer.addCoins(3 * times);
            }
        }
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
