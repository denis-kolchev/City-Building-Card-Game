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

    CardWidget* at(uchar id) const;

    bool isEmpty();

    void removeCard();

    int cardCount() const;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void clicked(QString cardTitle);

private:
    QList<CardWidget*> m_cards;
    int m_cardOverlap = 10; // Horizontal overlap between cards
};

#endif // CARDSTACKWIDGET_H
