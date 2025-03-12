#include "appleorchard.h"

AppleOrchard::AppleOrchard(const QString& title,
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

void AppleOrchard::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (hasActivationValue(diceRoll)) {
        owner.addCoins(3);
        // Give money to the owner
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
