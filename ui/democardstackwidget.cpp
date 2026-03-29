#include "democardstackwidget.h"

#include "democardwidget.h"

#include <QPaintEvent>

namespace {

void applyStackContainerSurface(QWidget *w)
{
    if (!w)
        return;
    // No extra fixed "outlinePad" rectangle: cards are 150×250 at (0, y). Padding beyond
    // that only exposed bare QWidget background inside QGraphicsProxyWidget (often black).
    w->setAutoFillBackground(false);
    w->setAttribute(Qt::WA_TranslucentBackground, true);
}

} // namespace

DemoCardStackWidget::DemoCardStackWidget(std::shared_ptr<Card> card, QWidget *parent)
    : QWidget(parent)
    , m_card(std::move(card))
    , m_useGameCard(true)
{
    applyStackContainerSurface(this);
    appendFaceCards(m_cardCount);
    updateStackGeometry();
}

DemoCardStackWidget::DemoCardStackWidget(const QString &title,
                                         const QString &imageResourcePath,
                                         QWidget *parent)
    : QWidget(parent)
    , m_title(title)
    , m_imageResourcePath(imageResourcePath)
    , m_useGameCard(false)
{
    applyStackContainerSurface(this);
    appendFaceCards(m_cardCount);
    updateStackGeometry();
}

void DemoCardStackWidget::setCardCount(int count)
{
    const int n = qMax(1, count);
    if (n == m_cardCount && static_cast<int>(m_cards.size()) == n)
        return;

    m_cardCount = n;
    clearCards();
    appendFaceCards(m_cardCount);
    updateStackGeometry();
    updateGeometry();
    update();
}

void DemoCardStackWidget::setStackOverlap(int pixels)
{
    const int p = qMax(0, pixels);
    if (p == m_stackOverlap)
        return;
    m_stackOverlap = p;
    updateStackGeometry();
    updateGeometry();
    update();
}

void DemoCardStackWidget::setStackDirection(StackDirection d)
{
    if (d == m_stackDirection)
        return;
    m_stackDirection = d;
    updateStackGeometry();
    updateGeometry();
    update();
}

DemoCardWidget *DemoCardStackWidget::topCard() const
{
    return m_cards.isEmpty() ? nullptr : m_cards.constLast();
}

void DemoCardStackWidget::clearCards()
{
    for (DemoCardWidget *c : m_cards) {
        c->hide();
        c->deleteLater();
    }
    m_cards.clear();
}

void DemoCardStackWidget::appendFaceCards(int count)
{
    for (int i = 0; i < count; ++i) {
        DemoCardWidget *face = nullptr;
        if (m_useGameCard && m_card)
            face = new DemoCardWidget(m_card, this);
        else
            face = new DemoCardWidget(m_title, m_imageResourcePath, this);
        m_cards.append(face);
        face->show();
    }
}

void DemoCardStackWidget::updateStackGeometry()
{
    constexpr int cardW = 150;
    constexpr int cardH = 250;

    const int n = static_cast<int>(m_cards.size());
    if (n <= 0) {
        setFixedSize(cardW, cardH);
        return;
    }
    const int stackExtra = (n > 1) ? (n - 1) * m_stackOverlap : 0;
    const bool vertical = (m_stackDirection == StackDirection::VerticalDown
                           || m_stackDirection == StackDirection::VerticalUp);
    if (vertical) {
        setFixedSize(cardW, cardH + stackExtra);
    } else {
        setFixedSize(cardW + stackExtra, cardH);
    }
}

void DemoCardStackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    switch (m_stackDirection) {
    case StackDirection::VerticalDown: {
        int y = 0;
        for (DemoCardWidget *card : m_cards) {
            card->move(0, y);
            card->raise();
            card->updateGeometry();
            card->setVisible(true);
            y += m_stackOverlap;
        }
        break;
    }
    case StackDirection::VerticalUp: {
        const int n = static_cast<int>(m_cards.size());
        const int stackExtra = (n > 1) ? (n - 1) * m_stackOverlap : 0;
        int y = stackExtra;
        for (DemoCardWidget *card : m_cards) {
            card->move(0, y);
            card->raise();
            card->updateGeometry();
            card->setVisible(true);
            y -= m_stackOverlap;
        }
        break;
    }
    case StackDirection::HorizontalRight: {
        int x = 0;
        for (DemoCardWidget *card : m_cards) {
            card->move(x, 0);
            card->raise();
            card->updateGeometry();
            card->setVisible(true);
            x += m_stackOverlap;
        }
        break;
    }
    case StackDirection::HorizontalLeft: {
        const int n = static_cast<int>(m_cards.size());
        const int stackExtra = (n > 1) ? (n - 1) * m_stackOverlap : 0;
        int x = stackExtra;
        for (DemoCardWidget *card : m_cards) {
            card->move(x, 0);
            card->raise();
            card->updateGeometry();
            card->setVisible(true);
            x -= m_stackOverlap;
        }
        break;
    }
    }
}
