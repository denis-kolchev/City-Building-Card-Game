#include "cardstackwidget.h"
#include <QtGui/qpainterpath.h>

CardStackWidget::CardStackWidget(QWidget *parent)
    : QWidget(parent)
{
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
    card->show();
    qDebug() << "Card added. Total cards:" << m_cards.size();
    updateGeometry();
    update(); // Trigger a repaint
}

CardWidget* CardStackWidget::at(QString title) const
{
    for (auto card : m_cards) {
        if (card->title() == title) {
            return card;
        }
    }

    return nullptr;
}

bool CardStackWidget::isEmpty()
{
    return m_cards.empty();
}

void CardStackWidget::removeCard()
{
    if (!m_cards.isEmpty()) {
        CardWidget *card = m_cards.takeLast();
        card->hide();
        card->deleteLater();
        qDebug() << "Card removed. Total cards:" << m_cards.size();
        updateGeometry();
        update(); // Trigger a repaint
    }
}

int CardStackWidget::cardCount() const
{
    return m_cards.size();
}

void CardStackWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !m_cards.empty()) {
        qDebug() << "mousepressEvent from CardStackWidget, send a tilte of card";
        emit clicked(m_cards.at(0)->title()); // Emit a signal when clicked
    }
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
        card->updateGeometry();
        xOffset += m_cardOverlap; // Increment the offset for the next card
    }
}
