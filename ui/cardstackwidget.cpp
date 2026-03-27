#include "cardstackwidget.h"
#include <QtGui/qpainterpath.h>

CardStackWidget::CardStackWidget(QWidget *parent)
    : QWidget(parent)
{
    updateStackGeometry();
}

void CardStackWidget::updateStackGeometry()
{
    // CardWidget uses 150×250; reserve width for outline padding, height for card + vertical stack overlap.
    constexpr int cardW = 150;
    constexpr int cardH = 250;
    constexpr int outlinePad = 10;

    const int n = static_cast<int>(m_cards.size());
    const int stackExtra = n > 1 ? (n - 1) * m_cardOverlap : 0;
    const int w = cardW + outlinePad;
    const int h = cardH + outlinePad + stackExtra;
    setFixedSize(w, h);
}

void CardStackWidget::addCard(CardWidget *card)
{
    m_cards.append(card);
    card->setParent(this); // Set this widget as the parent
    card->show();
    updateStackGeometry();
    updateGeometry();
    update(); // Trigger a repaint
}

CardWidget* CardStackWidget::at(CardId id) const
{
    for (auto card : m_cards) {
        if (card->id() == id) {
            return card;
        }
    }

    return nullptr;
}

bool CardStackWidget::isEmpty()
{
    return m_cards.empty();
}

CardId CardStackWidget::id()
{
    if (m_cards.isEmpty()) {
        return m_cards.at(0)->id();
    } else {
        return CardId::None;
    }
}

void CardStackWidget::removeCard()
{
    if (!m_cards.isEmpty()) {
        CardWidget *card = m_cards.takeLast();
        card->hide();
        card->deleteLater();
        qDebug() << "Card removed. Total cards:" << m_cards.size();
        updateStackGeometry();
        updateGeometry();
        update(); // Trigger a repaint
    }
}

int CardStackWidget::cardCount() const
{
    return m_cards.size();
}

void CardStackWidget::startCardsHighlighting(int playerBalance)
{
    if (m_cards.back()->price() > playerBalance) {
        return;
    }

    m_lastHighlighted = m_cards.back();
    m_lastHighlighted->startOutlineHighlight();
}

void CardStackWidget::stopCardsHighlighting()
{
    if (m_lastHighlighted) {
        m_lastHighlighted->stopOutlineHighlight();
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
        card->setVisible(true);
        xOffset += m_cardOverlap; // Increment the offset for the next card
    }
}

void CardStackWidget::turnOn()
{
    for (qsizetype i = 0; i < m_cards.size(); ++i) {
        m_cards[i]->turnOn();
    }
    update();
}

void CardStackWidget::turnOff()
{
    for (qsizetype i = 0; i < m_cards.size(); ++i) {
        m_cards[i]->turnOff();
    }
    update();
}
