#ifndef CARDDATACONFIGREADER_H
#define CARDDATACONFIGREADER_H

#include "logic/carddatahandler.h"
#include "cardfactory.h"

#include <QSettings>

class Card; // Forward declaration

class CardDataConfigReader : public QObject
{
    Q_OBJECT

public:
    CardDataConfigReader(QString configFilePath = "");

    bool isConfigDataReady();

    /// Emits configDataReadyToRead when the INI was found; call once after connections are wired
    /// so GameLogic can fill the bank before players are created.
    void notifyConfigReady();

signals:
    // Signal emitted when config data is ready
    void configDataReadyToRead();

    // Emitted with the requested card
    void sendCardData(QVector<std::shared_ptr<Card>> data);

public slots:
    // Slot to handle range requests
    void handleReadFromRange(CardId begin, CardId end);

    void handleRequestCardData(CardId begin, CardId end, std::shared_ptr<CardDataHandler> handler);

private:
    QVector<std::shared_ptr<Card>> readFromRange(CardId begin, CardId end);

private:
    CardFactory m_factory;
    QSettings m_settings;
    QString m_configFilePath;
    bool m_isConfigDataReady;
};

#endif // CARDDATACONFIGREADER_H
