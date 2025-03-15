#include "cardstackwidget.h"

CardStackWidget::CardStackWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground); // Allow transparency for shadows
    // These calculations should be fixed in the future and made binamic
    int w = 120, h = 228;
    w += 10; // outline
    h += 10; // otline
    h += 60; // offset * 6
    setFixedSize(w, h);
}

void CardStackWidget::addCard(CardWidget *card)
{
    m_cards.append(card);
    card->setParent(this); // Set this widget as the parent
    update(); // Trigger a repaint
}

void CardStackWidget::removeCard()
{
    if (!m_cards.isEmpty()) {
        CardWidget *card = m_cards.takeLast();
        card->deleteLater();
        update(); // Trigger a repaint
    }
}

int CardStackWidget::cardCount() const
{
    return m_cards.size();
}

void CardStackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int xOffset = 0; // Start drawing from the left

    for (CardWidget *card : m_cards) {
        // Draw the card with an offset
        card->move(0, xOffset);
        card->raise(); // Bring the card to the front
        xOffset += m_cardOverlap; // Increment the offset for the next card
    }
}
