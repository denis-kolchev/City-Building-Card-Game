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

DemoCardStackWidget::DemoCardStackWidget(std::shared_ptr<Card> card, int stackDepth, QWidget *parent)
    : QWidget(parent)
    , m_card(std::move(card))
    , m_useGameCard(true)
    , m_stackDepth(qMax(1, stackDepth))
{
    applyStackContainerSurface(this);
    appendFaceCards(m_stackDepth);
    updateStackGeometry();
}

DemoCardStackWidget::DemoCardStackWidget(const QString &title,
                                         const QString &imageResourcePath,
                                         int stackDepth,
                                         QWidget *parent)
    : QWidget(parent)
    , m_title(title)
    , m_imageResourcePath(imageResourcePath)
    , m_useGameCard(false)
    , m_stackDepth(qMax(1, stackDepth))
{
    applyStackContainerSurface(this);
    appendFaceCards(m_stackDepth);
    updateStackGeometry();
}

void DemoCardStackWidget::setStackDepth(int depth)
{
    const int d = qMax(1, depth);
    if (d == m_stackDepth && static_cast<int>(m_cards.size()) == d)
        return;

    m_stackDepth = d;
    clearCards();
    appendFaceCards(m_stackDepth);
    updateStackGeometry();
    updateGeometry();
    update();
}

void DemoCardStackWidget::setVerticalOverlap(int pixels)
{
    const int p = qMax(0, pixels);
    if (p == m_verticalOverlap)
        return;
    m_verticalOverlap = p;
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
    const int stackExtra = (n > 1) ? (n - 1) * m_verticalOverlap : 0;
    // Tight bounds: front card bottom is (n-1)*overlap + cardH (same as CardStackWidget
    // footprint without unused padding that drew as solid strips in the scene).
    const int w = cardW;
    const int h = cardH + stackExtra;
    setFixedSize(w, h);
}

void DemoCardStackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int yOffset = 0;
    for (DemoCardWidget *card : m_cards) {
        card->move(0, yOffset);
        card->raise();
        card->updateGeometry();
        card->setVisible(true);
        yOffset += m_verticalOverlap;
    }
}
