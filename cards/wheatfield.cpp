#include "wheatfield.h"

WheatField::WheatField(const QString& name,
                       const QString& description,
                       CardType type, int activationValue)
    : Card(name, description, type, activationValue) {}

void WheatField::activate(Player& owner, Player& activePlayer, int diceRoll) {
    if (diceRoll == m_activationValue) {
        owner.addCoins(1);
        // Give money to the owner
        qDebug() << m_name << " activated! " << owner.name() << " gains income.\n";
    }
}
