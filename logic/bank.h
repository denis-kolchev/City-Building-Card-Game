#ifndef BANK_H
#define BANK_H

#include "cardinventory.h"

#include <QObject>

class Bank : public QObject
{
    Q_OBJECT
public:
    explicit Bank(QObject *parent = nullptr);

    ~Bank();

    void addCard(std::shared_ptr<Card> card);

    std::shared_ptr<Card> findCardById(int cardId);

    void removeCard(std::shared_ptr<Card> card);

signals:
    void bankGetsCard(std::shared_ptr<Card> card);

    void bankLoosesCard(std::shared_ptr<Card> card);

private:
    std::shared_ptr<CardInventory> m_cardInventory;
};

#endif // BANK_H
