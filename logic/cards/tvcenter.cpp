#include "tvcenter.h"

TVCenter::TVCenter(const QString& title,
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

void TVCenter::activate(QVector<std::shared_ptr<Player>>& players,
                        Player& owner,
                        Player& activePlayer,
                        int dice1,
                        int dice2)
{
    // First, takes money from the richest player
    int MONEY_TO_TAKE = 5;
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        if (players.size() == 0) {
            return;
        }

        auto richestPlayer = players.at(0);
        for (auto player : players) {
            if (player->balance() > richestPlayer->balance() && richestPlayer->name() != activePlayer.name()) {
                richestPlayer = player;
            }
        }

        int availableCoins = richestPlayer->balance();
        if (availableCoins >= MONEY_TO_TAKE) {
            richestPlayer->deductMoney(MONEY_TO_TAKE);
            activePlayer.addCoins(MONEY_TO_TAKE);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " gain coins: " << MONEY_TO_TAKE;
            qDebug() << "--- " << m_title << " - " << richestPlayer->name() << " loose income: " << MONEY_TO_TAKE;
        } else {
            richestPlayer->deductMoney(availableCoins);
            activePlayer.addCoins(availableCoins);
            qDebug() << "--- " << m_title << " - " << activePlayer.name() << " gain coins: " << availableCoins;
            qDebug() << "--- " << m_title << " - " << richestPlayer->name() << " loose income: " << availableCoins;
        }

    }
}
