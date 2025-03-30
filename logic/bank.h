#ifndef BANK_H
#define BANK_H

#include "cardinventory.h"
#include "icardcontainer.h"

#include <QObject>

class Bank : public QObject, public ICardContainer
{
    Q_OBJECT
public:
    explicit Bank(QObject *parent = nullptr);

    ~Bank() override;

    void addCard(std::shared_ptr<Card> card) override;

    std::shared_ptr<Card> findCardById(CardId cardId);

    void removeCard(std::shared_ptr<Card> card) override;

signals:
    void bankGetsCard(std::shared_ptr<Card> card);

    void bankLoosesCard(std::shared_ptr<Card> card);

private:
    std::shared_ptr<CardInventory> m_cardInventory;
};

#endif // BANK_H
