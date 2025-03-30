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

    CardWidget* at(CardId id) const;

    CardId id();

    bool isEmpty();

    void removeCard();

    int cardCount() const;

    void turnOn();

    void turnOff();

public slots:
    void startCardsHighlighting(int playerBalance);

    void stopCardsHighlighting();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void clicked(QString cardTitle);

private:
    QList<CardWidget*> m_cards;
    int m_cardOverlap = 10; // Horizontal overlap between cards
    CardWidget* m_lastHighlighted;
};

#endif // CARDSTACKWIDGET_H
