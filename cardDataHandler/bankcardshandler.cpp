#include "bankcardshandler.h"

#include <QDebug>

BankCardsHandler::BankCardsHandler(std::shared_ptr<CardInventory>& bank)
    : m_bank(bank)
{
}

void BankCardsHandler::handleCardData(QVector<std::shared_ptr<Card>> data)
{
    for (const auto& card : data) {
        m_bank->addCard(card);
    }

    qDebug() << "Initial player cards received and processed.";
}
