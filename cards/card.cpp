#include "card.h"
#include <QtCore/qdebug.h>

Card::Card(const QString& title,
           const QString& description,
           const QString& imagePath,
           const QSet<uchar>& activationValues,
           CardType type,
           uchar pack,
           uchar price,
           uchar id)
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

QSet<uchar> Card::activationValues() const {
    return m_activationValues;
}

QString Card::description() const {
    return m_description;
}

uchar Card::id() const {
    return m_id;
}

QString Card::imagePath() const {
    return m_imagePath;
}

bool Card::hasActivationValue(uchar diceRoll) const {
    return m_activationValues.find(diceRoll) != m_activationValues.end();
}

uchar Card::pack() const {
    return m_pack;
}

uchar Card::price() const {
    return m_price;
}

QString Card::title() const {
    return m_title;
}

CardType Card::type() const {
    return m_type;
}
