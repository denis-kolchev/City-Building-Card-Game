#include "cardview.h"
#include "basecardwidget.h"

#include <QTimer>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QPainter>
#include <QPointF>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
#include <algorithm>
#include <vector>

namespace {

/** Evenly split cardCount across spanCount buckets (rows or columns). */
std::vector<int> cardsPerSpanDistribution(int cardCount, int spanCount)
{
    const int S = std::max(1, spanCount);
    std::vector<int> counts(static_cast<size_t>(S), 0);
    if (cardCount <= 0)
        return counts;
    const int base = cardCount / S;
    const int rem = cardCount % S;
    for (int s = 0; s < S; ++s)
        counts[static_cast<size_t>(s)] = base + (s < rem ? 1 : 0);
    return counts;
}

void computeMainAxisLayout(int n, qreal availableMain, qreal itemMain, qreal &outStep, qreal &outOffsetMain)
{
    if (n <= 0) {
        outStep = 0;
        outOffsetMain = 0;
        return;
    }
    if (n == 1) {
        outStep = 0;
        outOffsetMain = (availableMain - itemMain) * 0.5;
        return;
    }
    const qreal totalCardsMain = itemMain * n;
    if (totalCardsMain <= availableMain) {
        const qreal remaining = availableMain - totalCardsMain;
        const qreal gap = remaining / (n + 1);
        outOffsetMain = gap;
        outStep = itemMain + gap;
    } else {
        outStep = (availableMain - itemMain) / (n - 1);
        if (outStep < 0)
            outStep = 0;
        const qreal totalUsed = itemMain + outStep * (n - 1);
        outOffsetMain = (availableMain - totalUsed) * 0.5;
    }
}

} // namespace

CardView::CardView(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setMouseTracking(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CardView::setOrientation(Orientation o)
{
    m_orientation = o;
    scheduleLayout();
}

void CardView::setOrthogonalLineCount(int count)
{
    const int c = std::max(1, count);
    // Keep row and column counts in sync so call order vs setOrientation does not matter
    // (e.g. setOrthogonalLineCount(2) then setOrientation(Vertical) still yields two columns).
    if (c == m_horizontalRowCount && c == m_verticalColumnCount)
        return;
    m_horizontalRowCount = c;
    m_verticalColumnCount = c;
    scheduleLayout();
}

int CardView::orthogonalLineCount() const
{
    return m_orientation == Orientation::Horizontal ? m_horizontalRowCount : m_verticalColumnCount;
}

void CardView::setHorizontalRowCount(int rows)
{
    const int r = std::max(1, rows);
    if (r == m_horizontalRowCount)
        return;
    m_horizontalRowCount = r;
    scheduleLayout();
}

void CardView::setVerticalColumnCount(int columns)
{
    const int c = std::max(1, columns);
    if (c == m_verticalColumnCount)
        return;
    m_verticalColumnCount = c;
    scheduleLayout();
}

void CardView::setPopLiftDirection(PopLiftDirection direction)
{
    switch (direction) {
    case PopLiftDirection::Up:
    case PopLiftDirection::Down:
        setHorizontalPopDirection(direction);
        break;
    case PopLiftDirection::Left:
    case PopLiftDirection::Right:
        setVerticalPopDirection(direction);
        break;
    }
}

void CardView::setPopLiftDirection(PopLiftDirection horizontalFlow, PopLiftDirection verticalFlow)
{
    bool changed = false;
    if ((horizontalFlow == PopLiftDirection::Up || horizontalFlow == PopLiftDirection::Down)
        && horizontalFlow != m_horizontalFlowPop) {
        m_horizontalFlowPop = horizontalFlow;
        changed = true;
    }
    if ((verticalFlow == PopLiftDirection::Left || verticalFlow == PopLiftDirection::Right)
        && verticalFlow != m_verticalFlowPop) {
        m_verticalFlowPop = verticalFlow;
        changed = true;
    }
    if (changed)
        scheduleLayout();
}

void CardView::setHorizontalPopDirection(PopLiftDirection direction)
{
    if (direction != PopLiftDirection::Up && direction != PopLiftDirection::Down)
        return;
    if (direction == m_horizontalFlowPop)
        return;
    m_horizontalFlowPop = direction;
    scheduleLayout();
}

void CardView::setVerticalPopDirection(PopLiftDirection direction)
{
    if (direction != PopLiftDirection::Left && direction != PopLiftDirection::Right)
        return;
    if (direction == m_verticalFlowPop)
        return;
    m_verticalFlowPop = direction;
    scheduleLayout();
}

QPointF CardView::popUnitFromHorizontalFlow() const
{
    return m_horizontalFlowPop == PopLiftDirection::Up ? QPointF(0, -1) : QPointF(0, 1);
}

QPointF CardView::popUnitFromVerticalFlow() const
{
    return m_verticalFlowPop == PopLiftDirection::Left ? QPointF(-1, 0) : QPointF(1, 0);
}

void CardView::addWidget(QWidget *w)
{
    auto *item = new CardItem(w);
    m_scene->addItem(item);
    m_items.push_back(item);
    scheduleLayout();
}

void CardView::addCard(BaseCardWidget *card)
{
    addWidget(card);
}

void CardView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    // Match scene to the visible viewport so a huge fixed scene rect cannot create scroll range.
    m_scene->setSceneRect(mapToScene(viewport()->rect()).boundingRect());
    scheduleLayout();
}

void CardView::mouseMoveEvent(QMouseEvent *event)
{
    m_lastSceneHoverPos = mapToScene(event->position().toPoint());
    m_hasLastSceneHoverPos = true;
    updateHoverState(m_lastSceneHoverPos);
    QGraphicsView::mouseMoveEvent(event);
}

bool CardView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::Leave) {
        m_hasLastSceneHoverPos = false;
        setHoveredIndex(-1);
    }
    return QGraphicsView::viewportEvent(event);
}

void CardView::scheduleLayout()
{
    if (m_layoutScheduled)
        return;

    m_layoutScheduled = true;
    QTimer::singleShot(0, this, [this]() {
        m_layoutScheduled = false;
        layoutItems();
    });
}

void CardView::setHoveredIndex(int index)
{
    if (index == m_hoveredIndex)
        return;

    if (m_hoveredIndex >= 0 && m_hoveredIndex < static_cast<int>(m_items.size()))
        m_items[static_cast<size_t>(m_hoveredIndex)]->setPopped(false);

    m_hoveredIndex = index;

    if (m_hoveredIndex >= 0 && m_hoveredIndex < static_cast<int>(m_items.size()))
        m_items[static_cast<size_t>(m_hoveredIndex)]->setPopped(true);
}

void CardView::updateHoverState(const QPointF &scenePoint)
{
    const int N = static_cast<int>(m_items.size());
    if (N == 0 || static_cast<int>(m_slotSceneRects.size()) != N
        || static_cast<int>(m_cardPopHoverEnabled.size()) != N)
        return;

    int hit = -1;

    for (int i = N - 1; i >= 0; --i) {
        if (m_slotSceneRects[static_cast<size_t>(i)].contains(scenePoint)) {
            hit = i;
            break;
        }
    }

    if (hit >= 0 && !m_cardPopHoverEnabled[static_cast<size_t>(hit)])
        hit = -1;

    if (hit < 0 && m_hoveredIndex >= 0 && m_hoveredIndex < N) {
        if (m_cardPopHoverEnabled[static_cast<size_t>(m_hoveredIndex)]) {
            const QPointF u = m_items[static_cast<size_t>(m_hoveredIndex)]->popLiftUnit();
            const QPointF d(u.x() * CardItem::hoverLift(), u.y() * CardItem::hoverLift());
            const QRectF elevated = m_slotSceneRects[static_cast<size_t>(m_hoveredIndex)].translated(d);
            if (elevated.contains(scenePoint))
                hit = m_hoveredIndex;
        }
    }

    setHoveredIndex(hit);
}

void CardView::layoutItems()
{
    if (m_items.empty())
        return;

    QRectF r = mapToScene(viewport()->rect()).boundingRect();

    // Insets scale down with the view so narrow widths are not eaten by a fixed “frame”.
    constexpr qreal marginMin = 2.0;
    constexpr qreal marginMax = 20.0;
    const qreal insetW = std::clamp(r.width() * 0.025, marginMin, marginMax);
    const qreal insetH = std::clamp(r.height() * 0.025, marginMin, marginMax);
    const qreal peekPad = CardItem::hoverLift();

    QRectF inner(
        r.left() + insetW,
        r.top() + insetH,
        r.width() - 2 * insetW,
        r.height() - 2 * insetH);
    if (inner.width() <= 0 || inner.height() <= 0)
        return;

    // Horizontal rows: reserve peek top/bottom for pop −Y. Vertical column: reserve peek left/right for pop −X;
    // full inner height so top/bottom match inset only (no extra vertical peek strip).
    QRectF layoutBandH;
    QRectF columnBandV;
    if (m_orientation == Orientation::Horizontal) {
        layoutBandH = QRectF(
            inner.left(),
            inner.top() + peekPad,
            inner.width(),
            std::max<qreal>(0, inner.height() - 2 * peekPad));
    } else {
        columnBandV = QRectF(
            inner.left() + peekPad,
            inner.top(),
            std::max<qreal>(0, inner.width() - 2 * peekPad),
            inner.height());
    }

    const int N = static_cast<int>(m_items.size());

    QSizeF baseSize(120, 160);

    const qreal maxScale = 2.0;
    const qreal minScale = 0.5;

    m_slotSceneRects.resize(static_cast<size_t>(N));
    m_cardPopHoverEnabled.assign(static_cast<size_t>(N), false);

    const int prevHovered = m_hoveredIndex;
    setHoveredIndex(-1);

    if (m_orientation == Orientation::Horizontal) {
        const int rowCount = std::max(1, m_horizontalRowCount);
        const qreal bandH = layoutBandH.height();

        // Multi-row: insetH/2 above first row, insetH/2 below last row, insetH between rows
        // (half margin under a row + half margin above the next).
        qreal rowContentHeight = bandH;
        qreal topPad = 0;
        qreal betweenRows = 0;
        if (rowCount >= 2) {
            const qreal m = insetH;
            topPad = m * 0.5;
            const qreal bottomPad = m * 0.5;
            betweenRows = m;
            const qreal totalGaps = topPad + bottomPad + (rowCount - 1) * betweenRows;
            rowContentHeight = std::max<qreal>(0, bandH - totalGaps) / rowCount;
        }

        const qreal availableCross = rowContentHeight;
        const qreal scaleCross = availableCross / baseSize.height();
        const qreal scale = std::clamp(scaleCross, minScale, maxScale);
        const QSizeF itemSize = baseSize * scale;
        const qreal itemMain = itemSize.width();
        const bool interRowCrowd = rowCount >= 2 && rowContentHeight + 1e-3 < itemSize.height();
        const qreal lateralPeek = interRowCrowd ? peekPad : 0;
        const qreal availableMain = inner.width() - 2 * lateralPeek;
        const qreal rowX0 = inner.left() + lateralPeek;

        const std::vector<int> rowSizes = cardsPerSpanDistribution(N, rowCount);

        for (int row = 0, cardIndex = 0; row < rowCount; ++row) {
            const int nInRow = rowSizes[static_cast<size_t>(row)];
            if (nInRow <= 0)
                continue;

            qreal step = 0;
            qreal offsetMain = 0;
            computeMainAxisLayout(nInRow, availableMain, itemMain, step, offsetMain);

            const bool rowStacks = (nInRow > 1) && (itemMain * static_cast<qreal>(nInRow) > availableMain);

            const QPointF popU = rowStacks
                ? popUnitFromHorizontalFlow()
                : (interRowCrowd ? popUnitFromVerticalFlow() : popUnitFromHorizontalFlow());

            qreal ySlots = 0;
            if (rowCount >= 2) {
                const qreal rowTop = layoutBandH.top() + topPad + row * (rowContentHeight + betweenRows);
                ySlots = rowTop + (rowContentHeight - itemSize.height()) * 0.5;
            } else {
                ySlots = layoutBandH.top() + (bandH - itemSize.height()) * 0.5;
            }

            const bool allowPop = rowStacks || interRowCrowd;

            for (int j = 0; j < nInRow; ++j) {
                const int i = cardIndex++;
                CardItem *item = m_items[static_cast<size_t>(i)];
                item->setPopLiftVector(popU.x(), popU.y());
                item->setScale(scale);
                const QPointF pos(rowX0 + offsetMain + j * step, ySlots);
                m_slotSceneRects[static_cast<size_t>(i)] = QRectF(pos, itemSize);
                item->setBaseScenePos(pos);
                item->setStackZ(CardItem::stackZFromIndex(i));
                m_cardPopHoverEnabled[static_cast<size_t>(i)] = allowPop;
            }
        }
    } else {
        const int colCount = std::max(1, m_verticalColumnCount);
        const qreal bandW = columnBandV.width();

        // Multi-column: mirror of horizontal rows (insetW/2, insetW between, insetW/2).
        qreal colContentWidth = bandW;
        qreal leftPad = 0;
        qreal betweenCols = 0;
        if (colCount >= 2) {
            const qreal m = insetW;
            leftPad = m * 0.5;
            const qreal rightPad = m * 0.5;
            betweenCols = m;
            const qreal totalGaps = leftPad + rightPad + (colCount - 1) * betweenCols;
            colContentWidth = std::max<qreal>(0, bandW - totalGaps) / colCount;
        }

        const qreal availableCross = colContentWidth;
        const qreal scaleCross = availableCross / baseSize.width();
        const qreal scale = std::clamp(scaleCross, minScale, maxScale);
        const QSizeF itemSize = baseSize * scale;
        const qreal itemMain = itemSize.height();
        const bool interColCrowd = colCount >= 2 && colContentWidth + 1e-3 < itemSize.width();
        const qreal columnPeek = interColCrowd ? peekPad : 0;
        const qreal availableMain = columnBandV.height() - 2 * columnPeek;
        const qreal colY0 = columnBandV.top() + columnPeek;

        const std::vector<int> colSizes = cardsPerSpanDistribution(N, colCount);

        for (int col = 0, cardIndex = 0; col < colCount; ++col) {
            const int nInCol = colSizes[static_cast<size_t>(col)];
            if (nInCol <= 0)
                continue;

            qreal step = 0;
            qreal offsetMain = 0;
            computeMainAxisLayout(nInCol, availableMain, itemMain, step, offsetMain);

            const bool colStacks = (nInCol > 1) && (itemMain * static_cast<qreal>(nInCol) > availableMain);

            const QPointF popU = colStacks
                ? popUnitFromVerticalFlow()
                : (interColCrowd ? popUnitFromHorizontalFlow() : popUnitFromVerticalFlow());

            qreal xSlots = 0;
            if (colCount >= 2) {
                const qreal colLeft = columnBandV.left() + leftPad + col * (colContentWidth + betweenCols);
                xSlots = colLeft + (colContentWidth - itemSize.width()) * 0.5;
            } else {
                xSlots = columnBandV.left() + (bandW - itemSize.width()) * 0.5;
            }

            const bool allowPop = colStacks || interColCrowd;

            for (int j = 0; j < nInCol; ++j) {
                const int i = cardIndex++;
                CardItem *item = m_items[static_cast<size_t>(i)];
                item->setPopLiftVector(popU.x(), popU.y());
                item->setScale(scale);
                const QPointF pos(xSlots, colY0 + offsetMain + j * step);
                m_slotSceneRects[static_cast<size_t>(i)] = QRectF(pos, itemSize);
                item->setBaseScenePos(pos);
                item->setStackZ(CardItem::stackZFromIndex(i));
                m_cardPopHoverEnabled[static_cast<size_t>(i)] = allowPop;
            }
        }
    }

    if (m_hasLastSceneHoverPos)
        updateHoverState(m_lastSceneHoverPos);
    else if (prevHovered >= 0 && prevHovered < N && m_cardPopHoverEnabled[static_cast<size_t>(prevHovered)])
        setHoveredIndex(prevHovered);
}

