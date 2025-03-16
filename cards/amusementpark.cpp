#include "amusementpark.h"

AmusementPark::AmusementPark(const QString& title,
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

void AmusementPark::activate(QVector<std::shared_ptr<Player>> players, Player& owner, Player& activePlayer, uchar dice1, uchar dice2) {
    if (dice1 == dice2 && &owner == &activePlayer) {
        activePlayer.activateOneMoreBuild();
        qDebug() << m_title << " activated! " << owner.name() << " gains income.\n";
    }
}
