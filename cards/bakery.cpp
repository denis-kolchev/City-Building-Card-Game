#include "bakery.h"

Bakery::Bakery(const QString& name, CardType type, int activationValue)
    : Card(name, type, activationValue) {}

void Bakery::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (diceRoll == m_activationValue && &owner == &activePlayer) {
        activePlayer.addCoins(1);
        qDebug() << m_name << " activated! " << owner.name() << " gains income.\n";
    }
}
