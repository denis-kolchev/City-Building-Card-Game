#ifndef CARDDATACONFIGREADER_H
#define CARDDATACONFIGREADER_H

#include "cardfactory.h"

#include <QSettings>

class Card; // Forward declaration

class CardDataConfigReader
{
public:
    CardDataConfigReader(const QString& configFilePath);

    QVector<std::shared_ptr<Card>> readFromRange(uchar begin, uchar end);

private:
    CardFactory m_factory;
    QSettings m_settings;
};

#endif // CARDDATACONFIGREADER_H
