#include "bankcardshandler.h"

#include <QDebug>

BankCardsHandler::BankCardsHandler(std::shared_ptr<Bank>& bank)
    : m_bank(bank)
{
}

void BankCardsHandler::handleCardData(QVector<std::shared_ptr<Card>> data)
{
    for (const auto& card : data) {
        m_bank->addCard(card);
    }

    qDebug() << "Initial bank cards received and processed.";
}
