#ifndef BANKCARDSHANDLER_H
#define BANKCARDSHANDLER_H

#include "carddatahandler.h"
#include "../logic/bank.h"

class BankCardsHandler : public CardDataHandler {
public:
    explicit BankCardsHandler(std::shared_ptr<Bank>& bank);

    void handleCardData(QVector<std::shared_ptr<Card>> data) override;

private:
    std::shared_ptr<Bank>& m_bank;
};

#endif // BANKCARDSHANDLER_H
