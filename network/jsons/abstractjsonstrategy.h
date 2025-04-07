#ifndef ABSTRACTJSONSTRATEGY_H
#define ABSTRACTJSONSTRATEGY_H

#include <QDateTime>
#include <QObject>
#include <QJsonObject>

#include <memory>

class AbstractJsonStrategy;
using AbstractJsonPtr = std::shared_ptr<AbstractJsonStrategy>;

class AbstractJsonStrategy
{
public:
    AbstractJsonStrategy(QString type) : m_type(type) {};
    virtual ~AbstractJsonStrategy() = default;

    virtual QJsonObject json() = 0;

    QString type() { return m_type; }

private:
    QString m_type;
};

#endif // ABSTRACTJSONSTRATEGY_H
