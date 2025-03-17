#include "carddataconfigreader.h"

#include <QFile>
#include <QRegularExpression>

CardDataConfigReader::CardDataConfigReader(const QString& configFilePath)
    : m_settings(configFilePath, QSettings::IniFormat), m_configFilePath(configFilePath)
{
    if (m_settings.status() != QSettings::NoError) {
        qDebug() << "Error loading file!";
    }
}

#ifdef false
QVector<std::shared_ptr<Card>> CardDataConfigReader::readFromRange(uchar begin, uchar end) {
    QVector<std::shared_ptr<Card>> cards;

    QStringList groups = m_settings.childGroups();
    uchar current = begin;
    for (const QString& group : groups) {
        if (!group.startsWith("Card_")) continue;

        uchar cardNumber = group.mid(5).toUShort();
        if (cardNumber < begin || cardNumber > end) continue;

        m_settings.beginGroup(group);
        QString title = m_settings.value("title", "Unknown").toString();
        QString description = m_settings.value("description", "No description").toString();
        QString imagePath = m_settings.value("image", "").toString();
        uchar price = static_cast<uchar>(m_settings.value("price", 0).toUInt());
        QStringList activationStrList = m_settings.value("activationValue", "").toString().split(' ', Qt::SkipEmptyParts);

        QSet<uchar> activationValues;
        for (const QString& value : activationStrList) {
            activationValues.insert(value.toUShort());
        }

        QString typeStr = m_settings.value("type", "Agricultural").toString();
        CardType type = CardType::Agricultiral;
        if (typeStr == "Business") type = CardType::Business;
        else if (typeStr == "Dining") type = CardType::Dining;
        else if (typeStr == "Farm") type = CardType::Farm;
        else if (typeStr == "Fruit") type = CardType::Fruit;
        else if (typeStr == "Landmark") type = CardType::Landmark;
        else if (typeStr == "Mining") type = CardType::Mining;
        else if (typeStr == "Production") type = CardType::Production;
        else if (typeStr == "Ship") type = CardType::Ship;
        else if (typeStr == "Shop") type = CardType::Shop;

        uchar pack = static_cast<uchar>(m_settings.value("pack", 0).toUInt());

        std::shared_ptr<Card> card = m_factory.createCard(title, description, imagePath, activationValues, type, pack, price, current);
        cards.append(card);

        m_settings.endGroup();
        current++;
    }

    return cards;
}
#endif

QVector<std::shared_ptr<Card>> CardDataConfigReader::readFromRange(uchar begin, uchar end) {
    QVector<std::shared_ptr<Card>> cards;

    QFile file(m_configFilePath);

    if (!file.exists()) {
        qDebug() << "Error: INI file not found at" << m_configFilePath;
        return cards;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot open INI file.";
        return cards;
    }

    QTextStream in(&file);
    //in.setCodec("UTF-8");

    QRegularExpression sectionRegex(R"(\[Card_(\d+)\])"); // Matches [Card_XX]
    QRegularExpression keyValueRegex(R"((\w+)\s*=\s*(.*))"); // Matches key=value

    QString currentSection;
    QMap<QString, QString> currentCardData;

    uchar i = begin;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith(';') || line.startsWith('#')) continue;

        QRegularExpressionMatch sectionMatch = sectionRegex.match(line);
        if (sectionMatch.hasMatch()) {
            if (!currentSection.isEmpty()) {
                // Convert collected data into a Card object
                uchar cardNumber = currentSection.toUShort();
                if (cardNumber >= begin && cardNumber <= end) {
                    QString title = currentCardData.value("title", "Unknown");
                    QString description = currentCardData.value("description", "No description");
                    QString imagePath = currentCardData.value("image", "");
                    QSet<uchar> activationValues;

                    for (const QString& value : currentCardData.value("activationValue", "").split(' ', Qt::SkipEmptyParts)) {
                        activationValues.insert(value.toUShort());
                    }

                    QString typeStr = currentCardData.value("type", "Agricultural");
                    CardType type;
                    if (typeStr == "Agricultiral") {
                        type = CardType::Agricultiral;
                    } else if (typeStr == "Business") {
                        type = CardType::Business;
                    } else if (typeStr == "Dining") {
                        type = CardType::Dining;
                    } else if (typeStr == "Farm") {
                        type = CardType::Farm;
                    } else if (typeStr == "Fruit") {
                        type = CardType::Fruit;
                    } else if (typeStr == "Landmark") {
                        type = CardType::Landmark;
                    } else if (typeStr == "Mining") {
                        type = CardType::Mining;
                    } else if (typeStr == "Production") {
                        type = CardType::Production;
                    } else if (typeStr == "Ship") {
                        type = CardType::Ship;
                    } else if (typeStr == "Shop") {
                        type = CardType::Shop;
                    }

                    uchar pack = currentCardData.value("pack", "0").toUShort();
                    uchar price = currentCardData.value("price", "0").toUShort();

                    std::shared_ptr<Card> card = m_factory.createCard(title, description, imagePath, activationValues, type, pack, price, i);
                    cards.append(card);
                    i++; // Increment i after processing each card
                }
            }

            // Start a new section
            currentSection = sectionMatch.captured(1);
            currentCardData.clear();
            continue;
        }

        QRegularExpressionMatch keyValueMatch = keyValueRegex.match(line);
        if (keyValueMatch.hasMatch() && !currentSection.isEmpty()) {
            QString key = keyValueMatch.captured(1);
            QString value = keyValueMatch.captured(2);
            currentCardData[key] = value;
        }
    }

    // Process the last card in the file
    if (!currentSection.isEmpty()) {
        uchar cardNumber = currentSection.toUShort();
        if (cardNumber >= begin && cardNumber <= end) {
            QString title = currentCardData.value("title", "Unknown");
            QString description = currentCardData.value("description", "No description");
            QString imagePath = currentCardData.value("image", "");
            QSet<uchar> activationValues;

            for (const QString& value : currentCardData.value("activationValue", "").split(' ', Qt::SkipEmptyParts)) {
                activationValues.insert(value.toUShort());
            }

            QString typeStr = currentCardData.value("type", "Agricultural");
            CardType type;
            if (typeStr == "Agricultural") {
                type = CardType::Agricultiral;
            } else if (typeStr == "Business") {
                type = CardType::Business;
            } else if (typeStr == "Dining") {
                type = CardType::Dining;
            } else if (typeStr == "Farm") {
                type = CardType::Farm;
            } else if (typeStr == "Fruit") {
                type = CardType::Fruit;
            } else if (typeStr == "Landmark") {
                type = CardType::Landmark;
            } else if (typeStr == "Mining") {
                type = CardType::Mining;
            } else if (typeStr == "Production") {
                type = CardType::Production;
            } else if (typeStr == "Ship") {
                type = CardType::Ship;
            } else if (typeStr == "Shop") {
                type = CardType::Shop;
            }

            uchar pack = currentCardData.value("pack", "0").toUShort();
            uchar price = currentCardData.value("price", "0").toUShort();

            std::shared_ptr<Card> card = m_factory.createCard(title, description, imagePath, activationValues, type, pack, price, i);
            cards.append(card);
            i++; // Increment i after processing the last card
        }
    }

    file.close();
    return cards;
}
