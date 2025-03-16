#include "stadium.h"

Stadium::Stadium(const QString& title,
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

void Stadium::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    uchar MONEY_TO_TAKE = 2;
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        if (players.size() == 0) {
            return;
        }

        for (auto player : players) {
            if (player->name() != activePlayer.name()) {
                continue;
            }

            if (player->coins() >= MONEY_TO_TAKE) {
                player->deductMoney(MONEY_TO_TAKE);
                activePlayer.addCoins(MONEY_TO_TAKE);
            } else {
                auto availableCoins = player->coins();
                player->deductMoney(availableCoins);
                activePlayer.addCoins(availableCoins);
            }
        }
    }
}
