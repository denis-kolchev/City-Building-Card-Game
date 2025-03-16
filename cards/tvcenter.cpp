#include "tvcenter.h"

TVCenter::TVCenter(const QString& title,
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

void TVCenter::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    // First, takes money from the richest player
    uchar MONEY_TO_TAKE = 5;
    if (hasActivationValue(diceRoll) && &owner == &activePlayer) {
        if (players.size() == 0) {
            return;
        }

        auto richestPlayer = players.at(0);
        for (auto player : players) {
            if (player->coins() > richestPlayer->coins() && richestPlayer->name() != activePlayer.name()) {
                richestPlayer = player;
            }
        }

        int availableCoins = richestPlayer->coins();
        if (availableCoins >= MONEY_TO_TAKE) {
            richestPlayer->deductMoney(MONEY_TO_TAKE);
            activePlayer.addCoins(MONEY_TO_TAKE);
            qDebug() << m_title << " activated! " << owner.name() << " gains " << MONEY_TO_TAKE << " income.\n";
        } else {
            richestPlayer->deductMoney(availableCoins);
            activePlayer.addCoins(availableCoins);
            qDebug() << m_title << " activated! " << owner.name() << " gains " << availableCoins << " income.\n";
        }

    }
}
