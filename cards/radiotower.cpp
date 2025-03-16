#include "radiotower.h"

RadioTower::RadioTower(const QString& title,
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

void RadioTower::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (&owner == &activePlayer) {
        activePlayer.activateRerollDice();
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
