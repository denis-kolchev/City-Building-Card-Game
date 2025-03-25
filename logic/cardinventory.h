#ifndef CARDINVENTORY_H
#define CARDINVENTORY_H

#include "../logic/cards/card.h"

#include <QMap>
#include <QSet>

#include <memory>

class CardInventory
{
public:
    void addCard(std::shared_ptr<Card> card);

    void removeCard(std::shared_ptr<Card> card);

    int countCard(std::shared_ptr<Card> card) const;

    std::shared_ptr<Card> findCardById(int cardId) const;

    const QMap<std::shared_ptr<Card>, int>& getCards() const;

    const QMap<std::shared_ptr<Card>, int>& blueCards() const;

    const QMap<std::shared_ptr<Card>, int>& greenCards() const;

    const QMap<std::shared_ptr<Card>, int>& landmarks() const;

    const QMap<std::shared_ptr<Card>, int>& purpleCards() const;

    const QMap<std::shared_ptr<Card>, int>& redCards() const;

private:
    void categorizeCard(std::shared_ptr<Card> card);

    void uncategorizeCard(std::shared_ptr<Card> card);

private:
    QMap<std::shared_ptr<Card>, int> m_cards;
    QMap<std::shared_ptr<Card>, int> m_landmarks;
    QMap<std::shared_ptr<Card>, int> m_redCards;
    QMap<std::shared_ptr<Card>, int> m_blueCards;
    QMap<std::shared_ptr<Card>, int> m_greenCards;
    QMap<std::shared_ptr<Card>, int> m_purpleCards;

};
#endif // CARDINVENTORY_H
