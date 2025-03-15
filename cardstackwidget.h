#ifndef CARDSTACKWIDGET_H
#define CARDSTACKWIDGET_H

#include "cardwidget.h"

#include <QWidget>

class CardStackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardStackWidget(QWidget *parent = nullptr);

    void addCard(CardWidget *card);
    void removeCard();
    int cardCount() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<CardWidget*> m_cards;
    int m_cardOverlap = 10; // Horizontal overlap between cards
};

#endif // CARDSTACKWIDGET_H
