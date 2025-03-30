#include "stadium.h"

Stadium::Stadium(const QString& title,
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

void Stadium::activate(QVector<std::shared_ptr<Player>>& players,
                       Player& owner,
                       Player& activePlayer,
                       int dice1,
                       int dice2)
{
    int MONEY_TO_TAKE = 2;
    if (hasActivationValue(dice1 + dice2) && &owner == &activePlayer) {
        if (players.size() == 0) {
            return;
        }

        for (auto player : players) {
            if (player->name() != activePlayer.name()) {
                continue;
            }

            if (player->balance() >= MONEY_TO_TAKE) {
                player->deductMoney(MONEY_TO_TAKE);
                activePlayer.addCoins(MONEY_TO_TAKE);
                qDebug() << "--- " << m_title << " - " << activePlayer.name() << " gain coins: " << MONEY_TO_TAKE;
                qDebug() << "--- " << m_title << " - " << player->name() << " loose income: " << MONEY_TO_TAKE;
            } else {
                auto availableCoins = player->balance();
                player->deductMoney(availableCoins);
                activePlayer.addCoins(availableCoins);
                qDebug() << "--- " << m_title << " - " << activePlayer.name() << " gain coins: " << availableCoins;
                qDebug() << "--- " << m_title << " - " << player->name() << " loose income: " << availableCoins;
            }
        }
    }
}
