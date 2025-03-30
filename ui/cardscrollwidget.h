#ifndef CARDSCROLLWIDGET_H
#define CARDSCROLLWIDGET_H

#include "cardstackwidget.h"

#include <QWidget>

// Layout is outside of this to place it on
// Card

using CardStacks = QMap<CardId, CardStackWidget*>;
using CardList = QVector<std::shared_ptr<Card>>;

class CardScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardScrollWidget(QWidget *parent = nullptr);

    CardStacks getStacks();

    void placeCards(const CardList &cards);

    void removeCards(const CardList &cards);

    void turnOn(CardId id);

    void turnOff(CardId id);

signals:
    void activateCardsHighlighting(int playerBalance);

    void cardSignalClicked(CardId id);

    void deactivateCardsHighlighting();

public slots:
    void addCard(std::shared_ptr<Card> card);

    void removeCard(std::shared_ptr<Card> card);

private:
    void sortCardsById();

private:
    CardStacks m_stacks;

    QHBoxLayout* m_layout;
};

#endif // CARDSCROLLWIDGET_H
