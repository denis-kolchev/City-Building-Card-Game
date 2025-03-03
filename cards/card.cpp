#include "card.h"

Card::Card(const QString& name, CardType type, int activationValue)
    : m_name(name), m_type(type), m_activationValue(activationValue) {}

int Card::activationValue() const {
    return m_activationValue;
}

QString Card::name() const {
    return m_name;
}

CardType Card::type() const {
    return m_type;
}
