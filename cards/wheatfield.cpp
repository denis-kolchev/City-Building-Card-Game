#include "wheatfield.h"

WheatField::WheatField(const QString& name, CardType type, int activationValue)
    : Card(name, type, activationValue) {}

void WheatField::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (diceRoll == m_activationValue) {
        owner.addCoins(1);
        // Give money to the owner
        qDebug() << m_name << " activated! " << owner.name() << " gains income.\n";
    }
}
