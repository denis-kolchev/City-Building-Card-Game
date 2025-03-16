#include "forest.h"

Forest::Forest(const QString& title,
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

void Forest::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll)) {
        owner.addCoins(1);
        // Give money to the owner
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
