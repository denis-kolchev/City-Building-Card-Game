#include "cafe.h"

Cafe::Cafe(const QString& name, CardType type, int activationValue)
    : Card(name, type, activationValue) {}

void Cafe::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (diceRoll == m_activationValue && &owner != &activePlayer) {
        int available = activePlayer.coins();
        if (available >= 1) {
            activePlayer.deductMoney(1);
            owner.addCoins(1);
        } else {
            activePlayer.deductMoney(available);
            owner.addCoins(available);
        }

        qDebug() << m_name << " activated! " << activePlayer.name() << " pays " << owner.name() << ".\n";
    }
}
