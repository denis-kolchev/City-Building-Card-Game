#include "carddataconfigreader.h"

CardDataConfigReader::CardDataConfigReader(const QString& configFilePath)
    : m_settings(configFilePath, QSettings::IniFormat)
{
}

QVector<std::shared_ptr<Card>> CardDataConfigReader::readFromRange(uchar begin, uchar end) {
    QVector<std::shared_ptr<Card>> cards;

    for (uchar id = begin; id <= end; ++id) {
        // Construct the section name (e.g., "Card_04", "Card_05", etc.)
        QString sectionName = QString("Card_%1").arg(id, 2, 10, QChar('0'));

        if (!m_settings.childGroups().contains(sectionName)) {
            continue;
        }

        m_settings.beginGroup(sectionName);

        // Read card properties
        QString title = m_settings.value("title").toString();
        QString description = m_settings.value("description").toString();
        QString imagePath = m_settings.value("image").toString();
        uchar price = static_cast<uchar>(m_settings.value("price").toInt());
        QString typeStr = m_settings.value("type").toString();
        uchar pack = static_cast<uchar>(m_settings.value("pack").toInt());

        // Parse activation values (space-separated)
        QSet<uchar> activationValues;
        QStringList activationValuesStr = m_settings.value("activationValue").toString().split(" ", Qt::SkipEmptyParts);
        for (const QString& valueStr : activationValuesStr) {
            activationValues.insert(static_cast<uchar>(valueStr.toInt()));
        }

        // Convert type string to CardType enum (assuming CardType is an enum)
        CardType type;
        if (typeStr == "Landmark") {
            type = CardType::Landmark;
        } else if (typeStr == "Agricultural") {
            type = CardType::Agricultiral;
        } else if (typeStr == "Farm") {
            type = CardType::Farm;
        } else if (typeStr == "Shop") {
            type = CardType::Shop;
        }

        // Create the card using the CardFactory
        std::shared_ptr<Card> card = m_factory.createCard(title, description, imagePath, activationValues, type, pack, price);
        cards.append(card);

        // Exit the section
        m_settings.endGroup();
    }

    return cards;
}
