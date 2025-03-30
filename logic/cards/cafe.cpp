#include "cafe.h"

Cafe::Cafe(const QString& title,
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


void Cafe::activate(QVector<std::shared_ptr<Player>>& players,
                    Player& owner,
                    Player& activePlayer,
                    int dice1,
                    int dice2)
{
    if (&activePlayer == &owner) {
        return; // active player doesn't get income for ownership of this card
    }

    const int MONET_TO_TAKE = 1;
    if (hasActivationValue(dice1 + dice2)) {
        int available = activePlayer.balance();
        if (available >= MONET_TO_TAKE) {
            activePlayer.deductMoney(MONET_TO_TAKE);
            owner.addCoins(1);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << MONET_TO_TAKE;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << MONET_TO_TAKE;
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " loose coins: " << available;
            qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << available;
        }

    }
}
