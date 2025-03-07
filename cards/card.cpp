#include "card.h"

Card::Card(const QString& name,
           const QString& description,
           CardType type,
           int activationValue)
    : m_name(name)
    , m_description(description)
    , m_type(type)
    , m_activationValue(activationValue) {}

int Card::activationValue() const {
    return m_activationValue;
}

QString Card::description() const {
    return m_description;
}

QString Card::name() const {
    return m_name;
}

CardType Card::type() const {
    return m_type;
}
