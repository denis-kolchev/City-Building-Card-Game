#include "bakery.h"

Bakery::Bakery(const QString& name, const QString& description, CardType type, int activationValue)
    : Card(name, description, type, activationValue) {}

void Bakery::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (diceRoll == m_activationValue && &owner == &activePlayer) {
        activePlayer.addCoins(1);
        qDebug() << m_name << " activated! " << owner.name() << " gains income.\n";
    }
}
