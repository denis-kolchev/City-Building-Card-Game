#ifndef CARDDATACONFIGREADER_H
#define CARDDATACONFIGREADER_H

#include "cardDataHandler/carddatahandler.h"
#include "cardfactory.h"

#include <QSettings>

class Card; // Forward declaration

class CardDataConfigReader : public QObject
{
    Q_OBJECT

public:
    CardDataConfigReader(QString configFilePath = "");

signals:
    // Signal emitted when config data is ready
    void configDataReady();

    // Emitted with the requested card
    void sendCardData(QVector<std::shared_ptr<Card>> data);

public slots:
    // Slot to handle range requests
    void handleReadFromRange(int begin, int end);

    void requestCardData(int begin, int end, std::shared_ptr<CardDataHandler> handler);

private:
    QVector<std::shared_ptr<Card>> readFromRange(uchar begin, uchar end);

private:
    CardFactory m_factory;
    QSettings m_settings;
    QString m_configFilePath;
};

#endif // CARDDATACONFIGREADER_H
