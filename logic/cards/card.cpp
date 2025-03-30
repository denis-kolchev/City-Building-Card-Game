#include "card.h"
#include <QtCore/qdebug.h>

Card::Card(const QString& title,
           const QString& description,
           const QString& imagePath,
           const QSet<int>& activationValues,
           CardType type,
           int pack,
           int price,
           CardId id)
    : m_title(title)
    , m_description(description)
    , m_imagePath(imagePath)
    , m_activationValues(activationValues)
    , m_type(type)
    , m_pack(pack)
    , m_price(price)
    , m_id(id)
{
}

QSet<int> Card::activationValues() const {
    return m_activationValues;
}

QString Card::description() const {
    return m_description;
}

CardId Card::id() const {
    return m_id;
}

QString Card::imagePath() const {
    return m_imagePath;
}

bool Card::hasActivationValue(int diceRoll) const {
    return m_activationValues.find(diceRoll) != m_activationValues.end();
}

int Card::pack() const {
    return m_pack;
}

int Card::price() const {
    return m_price;
}

QString Card::title() const {
    return m_title;
}

CardType Card::type() const {
    return m_type;
}
