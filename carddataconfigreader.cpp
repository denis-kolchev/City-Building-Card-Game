#include "carddataconfigreader.h"

#include <QCoreApplication>
#include <QFile>
#include <QRegularExpression>
#include <QTimer>

CardDataConfigReader::CardDataConfigReader(QString configFilePath)
    : m_settings(configFilePath, QSettings::IniFormat)
    , m_configFilePath(configFilePath)
    , m_isConfigDataReady(false)
{
    // Still needs to change this code somehow
    m_configFilePath = QCoreApplication::applicationDirPath() + "/CardsDataConfig.ini";
    if (QFile::exists(m_configFilePath)) {
        qDebug() << "Config file has found: " << m_configFilePath;
        m_isConfigDataReady = true;
        // Call timer, cause slot might not be created yet
    } else {
        m_isConfigDataReady = false;
        qDebug() << "File not found!";
    }

    if (m_settings.status() != QSettings::NoError) {
        qDebug() << "Error loading file!";
    }
}

bool CardDataConfigReader::isConfigDataReady()
{
    return m_isConfigDataReady;
}

void CardDataConfigReader::handleReadFromRange(int begin, int end)
{
    emit sendCardData(readFromRange(begin, end));
}

void CardDataConfigReader::requestCardData(int begin,
                                           int end,
                                           std::shared_ptr<CardDataHandler> handler)
{
    QVector<std::shared_ptr<Card>> cards = readFromRange(begin, end);
    handler->handleCardData(cards); // Use the handler to process the data (Strategy Pattern)
}

QVector<std::shared_ptr<Card>> CardDataConfigReader::readFromRange(uchar begin, uchar end)
{
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
                        type = CardType::Agricultural;
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
                type = CardType::Agricultural;
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
