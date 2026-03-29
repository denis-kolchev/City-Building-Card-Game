#include "cardview.h"
#include "basecardwidget.h"

#include <QTimer>
#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QPainter>
#include <QPointF>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QGuiApplication>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <algorithm>
#include <utility>
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

QRect boundsForOpaquePixels(const QImage &img, int alphaThreshold = 18)
{
    int minX = img.width();
    int minY = img.height();
    int maxX = -1;
    int maxY = -1;
    for (int y = 0; y < img.height(); ++y) {
        const QRgb *line = reinterpret_cast<const QRgb *>(img.constScanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            if (qAlpha(line[x]) >= alphaThreshold) {
                minX = qMin(minX, x);
                minY = qMin(minY, y);
                maxX = qMax(maxX, x);
                maxY = qMax(maxY, y);
            }
        }
    }
    if (maxX < minX)
        return {};
    return QRect(minX, minY, maxX - minX + 1, maxY - minY + 1);
}

QPixmap phantomPixmapFromWidget(QWidget *w, QPoint *outCropTopLeftInWidget = nullptr)
{
    if (!w)
        return {};

    QImage img = w->grab().toImage().convertToFormat(QImage::Format_ARGB32);

    const int tw = qMax(1, w->width());
    const int th = qMax(1, w->height());
    if (img.width() != tw || img.height() != th)
        img = img.scaled(tw, th, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                  .convertToFormat(QImage::Format_ARGB32);

    QPoint cropTL(0, 0);
    const QRect tight = boundsForOpaquePixels(img);
    if (tight.isValid()) {
        cropTL = tight.topLeft();
        img = img.copy(tight);
    }

    if (outCropTopLeftInWidget)
        *outCropTopLeftInWidget = cropTL;

    for (int y = 0; y < img.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(img.scanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            const QRgb px = line[x];
            const int a = qAlpha(px);
            if (a < 12) {
                line[x] = qRgba(0, 0, 0, 0);
                continue;
            }
            const int r = qRed(px) * 72 / 100;
            const int g = qGreen(px) * 72 / 100;
            const int b = qBlue(px) * 80 / 100;
            const int na = qMin(255, a * 200 / 255);
            line[x] = qRgba(r, g, b, na);
        }
    }

    QPixmap pm = QPixmap::fromImage(std::move(img));
    pm.setDevicePixelRatio(1.0);
    return pm;
}

int mapCoordToNearestSlot(qreal coord, qreal axisOrigin, qreal offsetMain, qreal step, qreal itemMain, int slotCount)
{
    if (slotCount <= 1)
        return 0;
    int best = 0;
    qreal bestDist = 1.0e30;
    for (int k = 0; k < slotCount; ++k) {
        const qreal left = axisOrigin + offsetMain + static_cast<qreal>(k) * step;
        const qreal cx = left + itemMain * 0.5;
        const qreal d = qAbs(coord - cx);
        if (d < bestDist) {
            bestDist = d;
            best = k;
        }
    }
    return best;
}

void reorderSpanLocals(std::vector<CardItem *> &items, int spanStart, int spanLen, int fromLocal, int toLocal)
{
    if (fromLocal == toLocal || spanLen <= 0)
        return;
    std::vector<CardItem *> span;
    span.reserve(static_cast<size_t>(spanLen));
    for (int i = 0; i < spanLen; ++i)
        span.push_back(items[static_cast<size_t>(spanStart + i)]);
    CardItem *moved = span[static_cast<size_t>(fromLocal)];
    span.erase(span.begin() + fromLocal);
    span.insert(span.begin() + toLocal, moved);
    for (int i = 0; i < spanLen; ++i)
        items[static_cast<size_t>(spanStart + i)] = span[static_cast<size_t>(i)];
}

std::pair<int, int> horizontalRowSpanForIndex(int globalIndex, int totalCount, int rowCount)
{
    const std::vector<int> rowSizes = cardsPerSpanDistribution(totalCount, rowCount);
    int cur = 0;
    for (int r = 0; r < rowCount; ++r) {
        const int n = rowSizes[static_cast<size_t>(r)];
        if (globalIndex >= cur && globalIndex < cur + n)
            return {cur, n};
        cur += n;
    }
    return {0, totalCount};
}

std::pair<int, int> verticalColumnSpanForIndex(int globalIndex, int totalCount, int colCount)
{
    const std::vector<int> colSizes = cardsPerSpanDistribution(totalCount, colCount);
    int cur = 0;
    for (int c = 0; c < colCount; ++c) {
        const int n = colSizes[static_cast<size_t>(c)];
        if (globalIndex >= cur && globalIndex < cur + n)
            return {cur, n};
        cur += n;
    }
    return {0, totalCount};
}

int horizontalRowIndexForGlobal(int globalIndex, int N, int rowCount)
{
    const std::vector<int> rowSizes = cardsPerSpanDistribution(N, rowCount);
    int cur = 0;
    for (int r = 0; r < rowCount; ++r) {
        const int n = rowSizes[static_cast<size_t>(r)];
        if (globalIndex >= cur && globalIndex < cur + n)
            return r;
        cur += n;
    }
    return 0;
}

int verticalColIndexForGlobal(int globalIndex, int N, int colCount)
{
    const std::vector<int> colSizes = cardsPerSpanDistribution(N, colCount);
    int cur = 0;
    for (int c = 0; c < colCount; ++c) {
        const int n = colSizes[static_cast<size_t>(c)];
        if (globalIndex >= cur && globalIndex < cur + n)
            return c;
        cur += n;
    }
    return 0;
}

int indexOfItem(const std::vector<CardItem *> &items, CardItem *it)
{
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        if (items[static_cast<size_t>(i)] == it)
            return i;
    }
    return -1;
}

/** Row/column-major flat index in a fixed split (spans sum to item count). */
int flatIndexInSpans(const std::vector<int> &spanSizes, int spanIndex, int slotInSpan)
{
    int flat = 0;
    for (int s = 0; s < spanIndex; ++s)
        flat += spanSizes[static_cast<size_t>(s)];
    return flat + slotInSpan;
}

/**
 * Move dragged card to (previewSpan, slotInSpan) while preserving span counts.
 * Fixes cross-span drag: inserting only into the target span left the source short (OOB/garbage CardItem*).
 */
std::vector<CardItem *> permuteDragToSpanSlot(
    const std::vector<CardItem *> &items,
    int dragIdx,
    int previewSpan,
    int previewLocal,
    const std::vector<int> &spanSizes)
{
    const int spanCount = static_cast<int>(spanSizes.size());
    if (dragIdx < 0 || dragIdx >= static_cast<int>(items.size()) || previewSpan < 0
        || previewSpan >= spanCount)
        return items;
    const int nInSpan = spanSizes[static_cast<size_t>(previewSpan)];
    if (nInSpan <= 0)
        return items;
    const int slot = qBound(0, previewLocal, nInSpan - 1);
    const int to = flatIndexInSpans(spanSizes, previewSpan, slot);
    if (dragIdx == to)
        return items;
    std::vector<CardItem *> perm = items;
    CardItem *d = perm[static_cast<size_t>(dragIdx)];
    perm.erase(perm.begin() + dragIdx);
    perm.insert(perm.begin() + to, d);
    return perm;
}

std::vector<std::vector<CardItem *>> reshapeBySpans(
    const std::vector<CardItem *> &flat,
    const std::vector<int> &spanSizes,
    int spanCount)
{
    std::vector<std::vector<CardItem *>> out(static_cast<size_t>(spanCount));
    int f = 0;
    for (int s = 0; s < spanCount; ++s) {
        const int n = spanSizes[static_cast<size_t>(s)];
        for (int j = 0; j < n; ++j)
            out[static_cast<size_t>(s)].push_back(flat[static_cast<size_t>(f++)]);
    }
    return out;
}

int rowFromSceneY(qreal sceneY,
    int rowCount,
    qreal layoutBandTop,
    qreal topPad,
    qreal rowContentHeight,
    qreal betweenRows)
{
    if (rowCount <= 1)
        return 0;
    int best = 0;
    qreal bestDist = 1.0e30;
    for (int r = 0; r < rowCount; ++r) {
        const qreal rowTop = layoutBandTop + topPad + r * (rowContentHeight + betweenRows);
        const qreal cy = rowTop + rowContentHeight * 0.5;
        const qreal d = qAbs(sceneY - cy);
        if (d < bestDist) {
            bestDist = d;
            best = r;
        }
    }
    return best;
}

int colFromSceneX(qreal sceneX,
    int colCount,
    qreal columnBandLeft,
    qreal leftPad,
    qreal colContentWidth,
    qreal betweenCols)
{
    if (colCount <= 1)
        return 0;
    int best = 0;
    qreal bestDist = 1.0e30;
    for (int c = 0; c < colCount; ++c) {
        const qreal colLeft = columnBandLeft + leftPad + c * (colContentWidth + betweenCols);
        const qreal cx = colLeft + colContentWidth * 0.5;
        const qreal d = qAbs(sceneX - cx);
        if (d < bestDist) {
            bestDist = d;
            best = c;
        }
    }
    return best;
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

/** Scene-space height for vertical flow (logical height × scale). */
qreal scaledWidgetHeight(QWidget *w, qreal scale, qreal fallback)
{
    if (!w)
        return fallback;
    int h = w->height();
    if (h <= 0) {
        const QSize sh = w->sizeHint();
        h = qMax(sh.height(), 1);
    }
    return static_cast<qreal>(h) * scale;
}

/**
 * Vertical columns: stacks often have different heights (depth). Spacing uses per-item extents
 * so a short stack does not force the same step as a tall one (which compressed the column and
 * clipped deep piles). Horizontal rows already tie cross-axis space to max height via baseSize.
 */
void layoutVerticalColumnItems(int nInCol,
    int &cardIndex,
    qreal scale,
    const QSizeF &baseLogicalSize,
    const QSizeF &itemSize,
    qreal availableMain,
    qreal colY0,
    qreal xSlots,
    std::vector<CardItem *> &items,
    std::vector<QRectF> &slotSceneRects,
    std::vector<bool> &cardPopHoverEnabled,
    bool interColCrowd,
    const QPointF &popAlongColumn,
    const QPointF &popWhenColsCrowd,
    int dragGlobalIndex,
    int prevPreviewSlot,
    qreal dragPointerMainCoord,
    int *outColumnDragPreviewSlot,
    bool dragFollowReady,
    QPointF *outDragSlotTopLeftScene,
    const QPointF *dragMouseScene,
    const QPointF *dragGrabSceneOffset,
    QPointF *ioSmoothedFollowOffset,
    int *ioLastSmoothSlotP)
{
    if (nInCol <= 0)
        return;

    const int startIdx = cardIndex;
    const qreal fallbackMain = baseLogicalSize.height() * scale;

    const bool columnHasDrag = (dragGlobalIndex >= startIdx && dragGlobalIndex < startIdx + nInCol);

    auto placeOne = [&](int globalIdx,
                         const QPointF &pos,
                         const QSizeF &slotSize,
                         const QPointF &popU,
                         bool allowPop,
                         bool isDragged,
                         bool siblingAnim) {
        CardItem *item = items[static_cast<size_t>(globalIdx)];
        item->setPopLiftVector(popU.x(), popU.y());
        item->setScale(scale);
        slotSceneRects[static_cast<size_t>(globalIdx)] = QRectF(pos, slotSize);
        item->setDragOffset(QPointF(0, 0));
        const qreal mainZ = CardItem::stackZFromIndex(globalIdx);
        if (isDragged) {
            item->setStackZ(CardItem::poppedZValue());
            item->setZValue(CardItem::poppedZValue());
            item->setBaseScenePos(pos);
        } else if (siblingAnim) {
            item->setStackZ(mainZ);
            item->setBaseScenePosAnimated(pos);
        } else {
            item->setStackZ(mainZ);
            item->setBaseScenePos(pos);
        }
        cardPopHoverEnabled[static_cast<size_t>(globalIdx)] = allowPop;
    };

    if (!columnHasDrag) {
        std::vector<qreal> mainExtents;
        mainExtents.reserve(static_cast<size_t>(nInCol));
        qreal sumExtents = 0;
        qreal maxExtent = 0;
        for (int j = 0; j < nInCol; ++j) {
            QWidget *w = items[static_cast<size_t>(startIdx + j)]->widget();
            const qreal ext = scaledWidgetHeight(w, scale, fallbackMain);
            mainExtents.push_back(ext);
            sumExtents += ext;
            maxExtent = qMax(maxExtent, ext);
        }

        constexpr qreal eps = 1e-3;
        const bool colNeedsOverlap = (nInCol > 1) && (sumExtents > availableMain + eps);

        std::vector<qreal> mainOffsets(static_cast<size_t>(nInCol));
        if (!colNeedsOverlap) {
            const qreal gap = (availableMain - sumExtents) / static_cast<qreal>(nInCol + 1);
            qreal y = gap;
            for (int j = 0; j < nInCol; ++j) {
                mainOffsets[static_cast<size_t>(j)] = y;
                y += mainExtents[static_cast<size_t>(j)] + gap;
            }
        } else {
            qreal step = 0;
            qreal offsetMain = 0;
            computeMainAxisLayout(nInCol, availableMain, maxExtent, step, offsetMain);
            for (int j = 0; j < nInCol; ++j)
                mainOffsets[static_cast<size_t>(j)] = offsetMain + j * step;
        }

        const bool colStacks = colNeedsOverlap;
        const QPointF popU = colStacks
            ? popAlongColumn
            : (interColCrowd ? popWhenColsCrowd : popAlongColumn);

        const bool allowPop = colStacks || interColCrowd;

        for (int j = 0; j < nInCol; ++j) {
            const int i = startIdx + j;
            const qreal slotH = mainExtents[static_cast<size_t>(j)];
            const QPointF pos(xSlots, colY0 + mainOffsets[static_cast<size_t>(j)]);
            placeOne(i, pos, QSizeF(itemSize.width(), slotH), popU, allowPop, false, false);
        }

        cardIndex += nInCol;
        return;
    }

    const int K = nInCol;

    std::vector<qreal> origExtents(static_cast<size_t>(K));
    qreal origSum = 0;
    qreal origMax = 0;
    for (int k = 0; k < K; ++k) {
        QWidget *w = items[static_cast<size_t>(startIdx + k)]->widget();
        const qreal ext = scaledWidgetHeight(w, scale, fallbackMain);
        origExtents[static_cast<size_t>(k)] = ext;
        origSum += ext;
        origMax = qMax(origMax, ext);
    }

    constexpr qreal eps = 1e-3;
    const bool origOverlap = (K > 1) && (origSum > availableMain + eps);
    std::vector<qreal> origOffsets(static_cast<size_t>(K));
    if (!origOverlap) {
        const qreal gap = (availableMain - origSum) / static_cast<qreal>(K + 1);
        qreal y = gap;
        for (int k = 0; k < K; ++k) {
            origOffsets[static_cast<size_t>(k)] = y;
            y += origExtents[static_cast<size_t>(k)] + gap;
        }
    } else {
        qreal ostep = 0;
        qreal ooff = 0;
        computeMainAxisLayout(K, availableMain, origMax, ostep, ooff);
        for (int k = 0; k < K; ++k)
            origOffsets[static_cast<size_t>(k)] = ooff + k * ostep;
    }

    int p = 0;
    qreal bestCy = 1.0e30;
    for (int k = 0; k < K; ++k) {
        const qreal cy = colY0 + origOffsets[static_cast<size_t>(k)] + origExtents[static_cast<size_t>(k)] * 0.5;
        const qreal d = qAbs(dragPointerMainCoord - cy);
        if (d < bestCy) {
            bestCy = d;
            p = k;
        }
    }

    std::vector<int> others;
    others.reserve(static_cast<size_t>(K - 1));
    for (int k = 0; k < K; ++k) {
        const int g = startIdx + k;
        if (g != dragGlobalIndex)
            others.push_back(g);
    }
    std::vector<int> slotGlobal(static_cast<size_t>(K));
    for (int slot = 0; slot < K; ++slot) {
        if (slot == p)
            slotGlobal[static_cast<size_t>(slot)] = dragGlobalIndex;
        else if (slot < p)
            slotGlobal[static_cast<size_t>(slot)] = others[static_cast<size_t>(slot)];
        else
            slotGlobal[static_cast<size_t>(slot)] = others[static_cast<size_t>(slot - 1)];
    }

    std::vector<qreal> mainExtents(static_cast<size_t>(K));
    qreal sumExtents = 0;
    qreal maxExtent = 0;
    for (int slot = 0; slot < K; ++slot) {
        QWidget *w = items[static_cast<size_t>(slotGlobal[static_cast<size_t>(slot)])]->widget();
        const qreal ext = scaledWidgetHeight(w, scale, fallbackMain);
        mainExtents[static_cast<size_t>(slot)] = ext;
        sumExtents += ext;
        maxExtent = qMax(maxExtent, ext);
    }

    const bool colNeedsOverlap = (K > 1) && (sumExtents > availableMain + eps);
    std::vector<qreal> mainOffsets(static_cast<size_t>(K));
    if (!colNeedsOverlap) {
        const qreal gap = (availableMain - sumExtents) / static_cast<qreal>(K + 1);
        qreal y = gap;
        for (int slot = 0; slot < K; ++slot) {
            mainOffsets[static_cast<size_t>(slot)] = y;
            y += mainExtents[static_cast<size_t>(slot)] + gap;
        }
    } else {
        qreal step = 0;
        qreal offsetMain = 0;
        computeMainAxisLayout(K, availableMain, maxExtent, step, offsetMain);
        for (int slot = 0; slot < K; ++slot)
            mainOffsets[static_cast<size_t>(slot)] = offsetMain + slot * step;
    }

    const bool colStacks = colNeedsOverlap;
    const QPointF popU = colStacks
        ? popAlongColumn
        : (interColCrowd ? popWhenColsCrowd : popAlongColumn);

    const bool allowPop = colStacks || interColCrowd;

    const bool siblingAnim = (prevPreviewSlot >= 0 && p != prevPreviewSlot);

    if (outColumnDragPreviewSlot)
        *outColumnDragPreviewSlot = p;

    for (int slot = 0; slot < K; ++slot) {
        const int g = slotGlobal[static_cast<size_t>(slot)];
        const qreal slotH = mainExtents[static_cast<size_t>(slot)];
        const QPointF pos(xSlots, colY0 + mainOffsets[static_cast<size_t>(slot)]);
        const bool isDragged = (g == dragGlobalIndex);
        if (!isDragged) {
            placeOne(g, pos, QSizeF(itemSize.width(), slotH), popU, allowPop, false, siblingAnim);
            continue;
        }

        CardItem *item = items[static_cast<size_t>(g)];
        item->setPopLiftVector(popU.x(), popU.y());
        item->setScale(scale);
        slotSceneRects[static_cast<size_t>(g)] = QRectF(pos, QSizeF(itemSize.width(), slotH));
        item->setStackZ(CardItem::poppedZValue());
        item->setZValue(CardItem::poppedZValue());
        item->setBaseScenePos(pos);

        if (outDragSlotTopLeftScene)
            *outDragSlotTopLeftScene = pos;
        if (dragFollowReady && dragMouseScene && dragGrabSceneOffset && ioSmoothedFollowOffset && ioLastSmoothSlotP) {
            if (p != *ioLastSmoothSlotP) {
                *ioLastSmoothSlotP = p;
                *ioSmoothedFollowOffset =
                    *dragMouseScene - *dragGrabSceneOffset - pos - item->hoverLiftSceneOffset();
            }
            item->setDragOffset(*ioSmoothedFollowOffset);
        } else {
            item->setDragOffset(QPointF(0, 0));
        }
        cardPopHoverEnabled[static_cast<size_t>(g)] = allowPop;
    }

    cardIndex += nInCol;
}

/**
 * Place one vertical column from an explicit card order (used for multi-column cross-column drag).
 * siblingReflowAnim: animate non-dragged items when the cross-column preview changed this frame.
 */
void layoutVerticalColumnOrdered(
    const std::vector<CardItem *> &order,
    bool siblingReflowAnim,
    int previewOrthoColumn,
    int previewSlotP,
    qreal scale,
    const QSizeF &baseLogicalSize,
    const QSizeF &itemSize,
    qreal availableMain,
    qreal colY0,
    qreal xSlots,
    std::vector<CardItem *> &items,
    std::vector<QRectF> &slotSceneRects,
    std::vector<bool> &cardPopHoverEnabled,
    bool interColCrowd,
    const QPointF &popAlongColumn,
    const QPointF &popWhenColsCrowd,
    int dragGlobalIndex,
    bool dragFollowReady,
    QPointF *outDragSlotTopLeftScene,
    const QPointF *dragMouseScene,
    const QPointF *dragGrabSceneOffset,
    QPointF *ioSmoothedFollowOffset,
    int *ioLastSmoothSlotP,
    int *ioLastSmoothOrtho)
{
    const int nInCol = static_cast<int>(order.size());
    if (nInCol <= 0)
        return;

    const qreal fallbackMain = baseLogicalSize.height() * scale;
    std::vector<qreal> mainExtents;
    mainExtents.reserve(static_cast<size_t>(nInCol));
    qreal sumExtents = 0;
    qreal maxExtent = 0;
    for (int j = 0; j < nInCol; ++j) {
        QWidget *w = order[static_cast<size_t>(j)]->widget();
        const qreal ext = scaledWidgetHeight(w, scale, fallbackMain);
        mainExtents.push_back(ext);
        sumExtents += ext;
        maxExtent = qMax(maxExtent, ext);
    }

    constexpr qreal eps = 1e-3;
    const bool colNeedsOverlap = (nInCol > 1) && (sumExtents > availableMain + eps);

    std::vector<qreal> mainOffsets(static_cast<size_t>(nInCol));
    if (!colNeedsOverlap) {
        const qreal gap = (availableMain - sumExtents) / static_cast<qreal>(nInCol + 1);
        qreal y = gap;
        for (int j = 0; j < nInCol; ++j) {
            mainOffsets[static_cast<size_t>(j)] = y;
            y += mainExtents[static_cast<size_t>(j)] + gap;
        }
    } else {
        qreal step = 0;
        qreal offsetMain = 0;
        computeMainAxisLayout(nInCol, availableMain, maxExtent, step, offsetMain);
        for (int j = 0; j < nInCol; ++j)
            mainOffsets[static_cast<size_t>(j)] = offsetMain + j * step;
    }

    const bool colStacks = colNeedsOverlap;
    const QPointF popU = colStacks
        ? popAlongColumn
        : (interColCrowd ? popWhenColsCrowd : popAlongColumn);

    const bool allowPop = colStacks || interColCrowd;

    for (int j = 0; j < nInCol; ++j) {
        CardItem *item = order[static_cast<size_t>(j)];
        const int i = indexOfItem(items, item);
        if (i < 0)
            continue;
        const qreal slotH = mainExtents[static_cast<size_t>(j)];
        const QPointF pos(xSlots, colY0 + mainOffsets[static_cast<size_t>(j)]);
        item->setPopLiftVector(popU.x(), popU.y());
        item->setScale(scale);
        slotSceneRects[static_cast<size_t>(i)] = QRectF(pos, QSizeF(itemSize.width(), slotH));
        const bool isDragged = (dragGlobalIndex >= 0 && i == dragGlobalIndex);

        if (!isDragged) {
            item->setDragOffset(QPointF(0, 0));
            if (siblingReflowAnim) {
                item->setStackZ(CardItem::stackZFromIndex(i));
                item->setBaseScenePosAnimated(pos);
            } else {
                item->setStackZ(CardItem::stackZFromIndex(i));
                item->setBaseScenePos(pos);
            }
        } else {
            item->setStackZ(CardItem::poppedZValue());
            item->setZValue(CardItem::poppedZValue());
            item->setBaseScenePos(pos);
            if (outDragSlotTopLeftScene)
                *outDragSlotTopLeftScene = pos;
            if (dragFollowReady && dragMouseScene && dragGrabSceneOffset && ioSmoothedFollowOffset
                && ioLastSmoothSlotP && ioLastSmoothOrtho) {
                if (previewOrthoColumn != *ioLastSmoothOrtho || previewSlotP != *ioLastSmoothSlotP) {
                    *ioLastSmoothOrtho = previewOrthoColumn;
                    *ioLastSmoothSlotP = previewSlotP;
                    *ioSmoothedFollowOffset =
                        *dragMouseScene - *dragGrabSceneOffset - pos - item->hoverLiftSceneOffset();
                }
                item->setDragOffset(*ioSmoothedFollowOffset);
            } else {
                item->setDragOffset(QPointF(0, 0));
            }
        }
        cardPopHoverEnabled[static_cast<size_t>(i)] = allowPop;
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

    viewport()->installEventFilter(this);

    m_dragSmoothTimer = new QTimer(this);
    m_dragSmoothTimer->setInterval(16);
    connect(m_dragSmoothTimer, &QTimer::timeout, this, [this]() { tickDragFollowSmoothing(); });
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

void CardView::relayoutNow()
{
    m_layoutScheduled = false;
    QRectF r = mapToScene(viewport()->rect()).boundingRect();
    m_scene->setSceneRect(r);
    layoutItems();
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
    if (m_draggingCardIndex < 0)
        updateHoverState(m_lastSceneHoverPos);
    QGraphicsView::mouseMoveEvent(event);
}

bool CardView::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == viewport()) {
        switch (event->type()) {
        case QEvent::MouseButtonPress: {
            auto *me = static_cast<QMouseEvent *>(event);
            if (me->button() == Qt::LeftButton) {
                const QPointF scenePos = mapToScene(me->position().toPoint());
                const int hit = cardIndexAtScenePoint(scenePos);
                if (hit >= 0) {
                    beginCardDrag(hit, scenePos);
                    return true;
                }
            }
            break;
        }
        case QEvent::MouseMove:
            if (m_draggingCardIndex >= 0) {
                const QPointF scenePos = mapToScene(static_cast<QMouseEvent *>(event)->position().toPoint());
                m_lastSceneHoverPos = scenePos;
                m_hasLastSceneHoverPos = true;
                updateCardDrag(scenePos);
                return true;
            }
            break;
        case QEvent::MouseButtonRelease:
            if (m_draggingCardIndex >= 0) {
                auto *me = static_cast<QMouseEvent *>(event);
                if (me->button() == Qt::LeftButton) {
                    endCardDrag();
                    return true;
                }
            }
            break;
        default:
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}

int CardView::cardIndexAtScenePoint(const QPointF &scenePoint) const
{
    if (!m_scene || m_items.empty())
        return -1;

    const QList<QGraphicsItem *> under = m_scene->items(scenePoint);
    for (QGraphicsItem *gi : under) {
        auto *ci = dynamic_cast<CardItem *>(gi);
        if (!ci)
            continue;
        for (size_t k = 0; k < m_items.size(); ++k) {
            if (m_items[k] == ci)
                return static_cast<int>(k);
        }
    }
    return -1;
}

void CardView::beginCardDrag(int index, const QPointF &scenePos)
{
    m_draggingCardIndex = index;
    m_dragStartScene = scenePos;
    m_dragMouseScene = scenePos;

    const int N = static_cast<int>(m_items.size());
    if (m_orientation == Orientation::Horizontal) {
        const std::pair<int, int> span = horizontalRowSpanForIndex(index, N, std::max(1, m_horizontalRowCount));
        m_dragSpanStart = span.first;
        m_dragSpanLength = span.second;
    } else {
        const std::pair<int, int> span = verticalColumnSpanForIndex(index, N, std::max(1, m_verticalColumnCount));
        m_dragSpanStart = span.first;
        m_dragSpanLength = span.second;
    }
    m_dragFromLocal = index - m_dragSpanStart;
    m_dragPreviewLocal = m_dragFromLocal;
    m_lastDragLayoutPreviewLocal = -1;
    m_dragLastLayoutPreviewOrtho = -1;
    if (m_orientation == Orientation::Horizontal)
        m_dragPreviewOrtho = horizontalRowIndexForGlobal(index, N, std::max(1, m_horizontalRowCount));
    else
        m_dragPreviewOrtho = verticalColIndexForGlobal(index, N, std::max(1, m_verticalColumnCount));
    m_dragFollowReady = false;

    // Clear hover on other stacks only. Keep hover lift on the dragged stack; drag offset is then
    // computed as mouse − grab − slot − hoverLift so the pile stays visually where it was (e.g. y+1).
    const int prevHover = m_hoveredIndex;
    m_hoveredIndex = -1;
    if (prevHover >= 0 && prevHover < N && prevHover != index)
        m_items[static_cast<size_t>(prevHover)]->setPopped(false, false);

    CardItem *it = m_items[static_cast<size_t>(index)];
    it->setStackZ(CardItem::poppedZValue());
    it->setZValue(CardItem::poppedZValue());

    QGuiApplication::setOverrideCursor(Qt::ClosedHandCursor);
    viewport()->grabMouse();

    layoutItems();

    m_dragGrabSceneOffset = scenePos - it->scenePos();
    m_dragFollowReady = true;
    m_dragSmoothedFollowOffset =
        m_dragMouseScene - m_dragGrabSceneOffset - m_dragSlotTopLeftScene - it->hoverLiftSceneOffset();
    m_dragLastSmoothSlotP = m_dragPreviewLocal;
    m_dragLastSmoothOrtho = m_dragPreviewOrtho;
    it->setDragOffset(m_dragSmoothedFollowOffset);

    createDragPhantom(m_dragPhantomLayoutScale);
    m_dragSmoothTimer->start();
}

void CardView::updateCardDrag(const QPointF &scenePos)
{
    if (m_draggingCardIndex < 0)
        return;

    m_dragMouseScene = scenePos;
    layoutItems();
}

void CardView::endCardDrag()
{
    if (m_draggingCardIndex < 0)
        return;

    m_dragSmoothTimer->stop();
    removeDragPhantom();
    m_dragFollowReady = false;

    CardItem *dragged = m_items[static_cast<size_t>(m_draggingCardIndex)];
    dragged->setDragOffset(QPointF(0, 0));

    const int dragIdx = m_draggingCardIndex;
    const int N = static_cast<int>(m_items.size());

    if (m_orientation == Orientation::Horizontal && m_horizontalRowCount > 1) {
        const int rowCount = std::max(1, m_horizontalRowCount);
        const std::vector<int> rowSizes = cardsPerSpanDistribution(N, rowCount);
        const int pr = m_dragPreviewOrtho;
        const int pl = m_dragPreviewLocal;
        const int nTarget = rowSizes[static_cast<size_t>(qBound(0, pr, rowCount - 1))];
        const int slot = qBound(0, pl, qMax(0, nTarget - 1));
        m_items = permuteDragToSpanSlot(m_items, dragIdx, qBound(0, pr, rowCount - 1), slot, rowSizes);
    } else if (m_orientation == Orientation::Vertical && m_verticalColumnCount > 1) {
        const int colCount = std::max(1, m_verticalColumnCount);
        const std::vector<int> colSizes = cardsPerSpanDistribution(N, colCount);
        const int pc = m_dragPreviewOrtho;
        const int pl = m_dragPreviewLocal;
        const int nTarget = colSizes[static_cast<size_t>(qBound(0, pc, colCount - 1))];
        const int slot = qBound(0, pl, qMax(0, nTarget - 1));
        m_items = permuteDragToSpanSlot(m_items, dragIdx, qBound(0, pc, colCount - 1), slot, colSizes);
    } else {
        reorderSpanLocals(m_items, m_dragSpanStart, m_dragSpanLength, m_dragFromLocal, m_dragPreviewLocal);
    }

    m_draggingCardIndex = -1;
    m_lastDragLayoutPreviewLocal = -1;
    m_dragLastLayoutPreviewOrtho = -1;

    QGuiApplication::restoreOverrideCursor();
    viewport()->releaseMouse();

    layoutItems();

    const bool dragStillUnderCursor = m_hoveredIndex >= 0
        && m_hoveredIndex < static_cast<int>(m_items.size())
        && m_items[static_cast<size_t>(m_hoveredIndex)] == dragged;
    if (!dragStillUnderCursor)
        dragged->setPopped(false, true);
}

void CardView::tickDragFollowSmoothing()
{
    if (m_draggingCardIndex < 0 || !m_dragFollowReady)
        return;

    CardItem *it = m_items[static_cast<size_t>(m_draggingCardIndex)];
    const QPointF target =
        m_dragMouseScene - m_dragGrabSceneOffset - m_dragSlotTopLeftScene - it->hoverLiftSceneOffset();
    constexpr qreal k = 0.29;
    m_dragSmoothedFollowOffset += (target - m_dragSmoothedFollowOffset) * k;
    it->setDragOffset(m_dragSmoothedFollowOffset);
}

void CardView::createDragPhantom(qreal layoutScale)
{
    if (m_dragPhantom || m_draggingCardIndex < 0)
        return;

    QWidget *w = m_items[static_cast<size_t>(m_draggingCardIndex)]->widget();
    if (!w)
        return;

    QPixmap pm = phantomPixmapFromWidget(w, &m_dragPhantomAlignOffset);
    m_dragPhantom = new QGraphicsPixmapItem(pm);
    m_dragPhantom->setZValue(CardItem::poppedZValue() - 50000.0);
    m_dragPhantom->setAcceptedMouseButtons(Qt::NoButton);
    m_scene->addItem(m_dragPhantom);
    syncDragPhantom(layoutScale);
}

void CardView::removeDragPhantom()
{
    if (!m_dragPhantom)
        return;
    m_scene->removeItem(m_dragPhantom);
    delete m_dragPhantom;
    m_dragPhantom = nullptr;
}

void CardView::syncDragPhantom(qreal layoutScale)
{
    if (!m_dragPhantom)
        return;
    const QPointF align = QPointF(m_dragPhantomAlignOffset) * layoutScale;
    m_dragPhantom->setPos(m_dragSlotTopLeftScene + align);
    m_dragPhantom->setScale(layoutScale);
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

void CardView::setHoveredIndex(int index, bool animateHoverLift)
{
    if (index == m_hoveredIndex)
        return;

    if (m_hoveredIndex >= 0 && m_hoveredIndex < static_cast<int>(m_items.size()))
        m_items[static_cast<size_t>(m_hoveredIndex)]->setPopped(false, animateHoverLift);

    m_hoveredIndex = index;

    if (m_hoveredIndex >= 0 && m_hoveredIndex < static_cast<int>(m_items.size()))
        m_items[static_cast<size_t>(m_hoveredIndex)]->setPopped(true, animateHoverLift);
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

    // Match embedded QWidget size (e.g. 150×250 for CardWidget / DemoCardWidget). A fixed 120×160
    // here scaled the proxy wrong and looked vertically “indented” vs the layout band.
    QSizeF baseSize(120, 160);
    for (const CardItem *item : m_items) {
        QWidget *w = item->widget();
        if (!w)
            continue;
        QSizeF sz(w->width(), w->height());
        if (sz.width() <= 0 || sz.height() <= 0)
            sz = QSizeF(w->sizeHint());
        if (sz.width() > 0 && sz.height() > 0) {
            baseSize.setWidth(qMax(baseSize.width(), sz.width()));
            baseSize.setHeight(qMax(baseSize.height(), sz.height()));
        }
    }

    const qreal maxScale = 2.0;
    const qreal minScale = 0.5;

    m_slotSceneRects.resize(static_cast<size_t>(N));
    m_cardPopHoverEnabled.assign(static_cast<size_t>(N), false);

    const int prevHovered = m_hoveredIndex;
    setHoveredIndex(-1, m_draggingCardIndex < 0);

    const int prevLayoutPreview = m_lastDragLayoutPreviewLocal;

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
        m_dragPhantomLayoutScale = scale;
        const QSizeF itemSize = baseSize * scale;
        const qreal itemMain = itemSize.width();
        const bool interRowCrowd = rowCount >= 2 && rowContentHeight + 1e-3 < itemSize.height();
        const qreal lateralPeek = interRowCrowd ? peekPad : 0;
        const qreal availableMain = inner.width() - 2 * lateralPeek;
        const qreal rowX0 = inner.left() + lateralPeek;

        const std::vector<int> rowSizes = cardsPerSpanDistribution(N, rowCount);

        if (m_draggingCardIndex < 0 || rowCount > 1) {
            if (m_draggingCardIndex < 0) {
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
                        item->setDragOffset(QPointF(0, 0));
                        item->setBaseScenePos(pos);
                        item->setStackZ(CardItem::stackZFromIndex(i));
                        m_cardPopHoverEnabled[static_cast<size_t>(i)] = allowPop;
                    }
                }
            } else {
                int previewRow = rowFromSceneY(
                    m_dragMouseScene.y(),
                    rowCount,
                    layoutBandH.top(),
                    topPad,
                    rowContentHeight,
                    betweenRows);
                if (rowSizes[static_cast<size_t>(previewRow)] <= 0) {
                    for (int r = 0; r < rowCount; ++r) {
                        if (rowSizes[static_cast<size_t>(r)] > 0) {
                            previewRow = r;
                            break;
                        }
                    }
                }
                m_dragPreviewOrtho = previewRow;

                const int nTarget = rowSizes[static_cast<size_t>(previewRow)];
                qreal stepP = 0;
                qreal offP = 0;
                computeMainAxisLayout(nTarget, availableMain, itemMain, stepP, offP);
                m_dragPreviewLocal = mapCoordToNearestSlot(
                    m_dragMouseScene.x(), rowX0, offP, stepP, itemMain, nTarget);

                CardItem *const dragItem = m_items[static_cast<size_t>(m_draggingCardIndex)];
                const int slotBound = qBound(0, m_dragPreviewLocal, qMax(0, nTarget - 1));
                const std::vector<CardItem *> perm = permuteDragToSpanSlot(
                    m_items,
                    m_draggingCardIndex,
                    previewRow,
                    slotBound,
                    rowSizes);
                std::vector<std::vector<CardItem *>> slotRows = reshapeBySpans(perm, rowSizes, rowCount);

                const int prevOrtho = m_dragLastLayoutPreviewOrtho;
                const bool rowDragReflowAnim = m_dragFollowReady
                    && (prevLayoutPreview >= 0 || prevOrtho >= 0)
                    && (prevLayoutPreview != m_dragPreviewLocal || prevOrtho != previewRow);

                for (int row = 0; row < rowCount; ++row) {
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

                    for (int slot = 0; slot < nInRow; ++slot) {
                        CardItem *item = slotRows[static_cast<size_t>(row)][static_cast<size_t>(slot)];
                        const int gIdx = indexOfItem(m_items, item);
                        if (!item || gIdx < 0)
                            continue;
                        const QPointF pos(rowX0 + offsetMain + slot * step, ySlots);
                        item->setPopLiftVector(popU.x(), popU.y());
                        item->setScale(scale);
                        m_slotSceneRects[static_cast<size_t>(gIdx)] = QRectF(pos, itemSize);
                        const bool isDragged = (item == dragItem);
                        if (isDragged) {
                            m_dragSlotTopLeftScene = pos;
                            item->setStackZ(CardItem::poppedZValue());
                            item->setZValue(CardItem::poppedZValue());
                            item->setBaseScenePos(pos);
                            if (m_dragFollowReady) {
                                if (previewRow != m_dragLastSmoothOrtho
                                    || m_dragPreviewLocal != m_dragLastSmoothSlotP) {
                                    m_dragLastSmoothOrtho = previewRow;
                                    m_dragLastSmoothSlotP = m_dragPreviewLocal;
                                    m_dragSmoothedFollowOffset = m_dragMouseScene - m_dragGrabSceneOffset - pos
                                        - item->hoverLiftSceneOffset();
                                }
                                item->setDragOffset(m_dragSmoothedFollowOffset);
                            } else {
                                item->setDragOffset(QPointF(0, 0));
                            }
                        } else {
                            item->setDragOffset(QPointF(0, 0));
                            if (rowDragReflowAnim) {
                                item->setStackZ(CardItem::stackZFromIndex(gIdx));
                                item->setBaseScenePosAnimated(pos);
                            } else {
                                item->setStackZ(CardItem::stackZFromIndex(gIdx));
                                item->setBaseScenePos(pos);
                            }
                        }
                        m_cardPopHoverEnabled[static_cast<size_t>(gIdx)] = allowPop;
                    }
                }

                m_dragLastLayoutPreviewOrtho = previewRow;
                m_lastDragLayoutPreviewLocal = m_dragPreviewLocal;
            }
        } else {
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

                const bool rowHasDrag = (m_draggingCardIndex >= cardIndex
                    && m_draggingCardIndex < cardIndex + nInRow);

                if (!rowHasDrag) {
                    for (int j = 0; j < nInRow; ++j) {
                        const int i = cardIndex++;
                        CardItem *item = m_items[static_cast<size_t>(i)];
                        item->setPopLiftVector(popU.x(), popU.y());
                        item->setScale(scale);
                        const QPointF pos(rowX0 + offsetMain + j * step, ySlots);
                        m_slotSceneRects[static_cast<size_t>(i)] = QRectF(pos, itemSize);
                        item->setDragOffset(QPointF(0, 0));
                        item->setBaseScenePos(pos);
                        item->setStackZ(CardItem::stackZFromIndex(i));
                        m_cardPopHoverEnabled[static_cast<size_t>(i)] = allowPop;
                    }
                } else {
                    const int K = nInRow;
                    const int spanStart = cardIndex;
                    const int p = mapCoordToNearestSlot(m_dragMouseScene.x(), rowX0, offsetMain, step, itemMain, K);
                    m_dragPreviewLocal = p;
                    m_dragPreviewOrtho = 0;
                    const bool rowDragReflowAnim = (prevLayoutPreview >= 0 && p != prevLayoutPreview);

                    std::vector<int> others;
                    others.reserve(static_cast<size_t>(K - 1));
                    for (int k = 0; k < K; ++k) {
                        const int g = spanStart + k;
                        if (g != m_draggingCardIndex)
                            others.push_back(g);
                    }
                    std::vector<int> slotGlobal(static_cast<size_t>(K));
                    for (int slot = 0; slot < K; ++slot) {
                        if (slot == p)
                            slotGlobal[static_cast<size_t>(slot)] = m_draggingCardIndex;
                        else if (slot < p)
                            slotGlobal[static_cast<size_t>(slot)] = others[static_cast<size_t>(slot)];
                        else
                            slotGlobal[static_cast<size_t>(slot)] = others[static_cast<size_t>(slot - 1)];
                    }

                    for (int slot = 0; slot < K; ++slot) {
                        const int g = slotGlobal[static_cast<size_t>(slot)];
                        CardItem *item = m_items[static_cast<size_t>(g)];
                        const QPointF pos(rowX0 + offsetMain + slot * step, ySlots);
                        item->setPopLiftVector(popU.x(), popU.y());
                        item->setScale(scale);
                        m_slotSceneRects[static_cast<size_t>(g)] = QRectF(pos, itemSize);
                        const bool isDragged = (g == m_draggingCardIndex);
                        if (isDragged) {
                            m_dragSlotTopLeftScene = pos;
                            item->setStackZ(CardItem::poppedZValue());
                            item->setZValue(CardItem::poppedZValue());
                            item->setBaseScenePos(pos);
                            if (m_dragFollowReady) {
                                if (p != m_dragLastSmoothSlotP || m_dragLastSmoothOrtho != 0) {
                                    m_dragLastSmoothSlotP = p;
                                    m_dragLastSmoothOrtho = 0;
                                    m_dragSmoothedFollowOffset = m_dragMouseScene - m_dragGrabSceneOffset - pos
                                        - item->hoverLiftSceneOffset();
                                }
                                item->setDragOffset(m_dragSmoothedFollowOffset);
                            } else {
                                item->setDragOffset(QPointF(0, 0));
                            }
                        } else {
                            item->setDragOffset(QPointF(0, 0));
                            if (rowDragReflowAnim) {
                                item->setStackZ(CardItem::stackZFromIndex(g));
                                item->setBaseScenePosAnimated(pos);
                            } else {
                                item->setStackZ(CardItem::stackZFromIndex(g));
                                item->setBaseScenePos(pos);
                            }
                        }
                        m_cardPopHoverEnabled[static_cast<size_t>(g)] = allowPop;
                    }

                    cardIndex += K;
                }
            }

            if (m_draggingCardIndex >= 0) {
                m_dragLastLayoutPreviewOrtho = 0;
                m_lastDragLayoutPreviewLocal = m_dragPreviewLocal;
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
        m_dragPhantomLayoutScale = scale;
        const QSizeF itemSize = baseSize * scale;
        const bool interColCrowd = colCount >= 2 && colContentWidth + 1e-3 < itemSize.width();
        const qreal columnPeek = interColCrowd ? peekPad : 0;
        const qreal availableMain = columnBandV.height() - 2 * columnPeek;
        const qreal colY0 = columnBandV.top() + columnPeek;

        const std::vector<int> colSizes = cardsPerSpanDistribution(N, colCount);

        if (m_draggingCardIndex < 0 || colCount <= 1) {
            for (int col = 0, cardIndex = 0; col < colCount; ++col) {
                const int nInCol = colSizes[static_cast<size_t>(col)];
                if (nInCol <= 0)
                    continue;

                qreal xSlots = 0;
                if (colCount >= 2) {
                    const qreal colLeft = columnBandV.left() + leftPad + col * (colContentWidth + betweenCols);
                    xSlots = colLeft + (colContentWidth - itemSize.width()) * 0.5;
                } else {
                    xSlots = columnBandV.left() + (bandW - itemSize.width()) * 0.5;
                }

                layoutVerticalColumnItems(
                    nInCol,
                    cardIndex,
                    scale,
                    baseSize,
                    itemSize,
                    availableMain,
                    colY0,
                    xSlots,
                    m_items,
                    m_slotSceneRects,
                    m_cardPopHoverEnabled,
                    interColCrowd,
                    popUnitFromVerticalFlow(),
                    popUnitFromHorizontalFlow(),
                    m_draggingCardIndex,
                    prevLayoutPreview,
                    m_dragMouseScene.y(),
                    m_draggingCardIndex >= 0 ? &m_dragPreviewLocal : nullptr,
                    m_dragFollowReady,
                    m_draggingCardIndex >= 0 ? &m_dragSlotTopLeftScene : nullptr,
                    m_draggingCardIndex >= 0 ? &m_dragMouseScene : nullptr,
                    m_draggingCardIndex >= 0 ? &m_dragGrabSceneOffset : nullptr,
                    m_draggingCardIndex >= 0 ? &m_dragSmoothedFollowOffset : nullptr,
                    m_draggingCardIndex >= 0 ? &m_dragLastSmoothSlotP : nullptr);
            }

            if (m_draggingCardIndex >= 0) {
                m_dragPreviewOrtho = 0;
                m_dragLastLayoutPreviewOrtho = 0;
                m_lastDragLayoutPreviewLocal = m_dragPreviewLocal;
            }
        } else {
            const int prevOrthoV = m_dragLastLayoutPreviewOrtho;
            CardItem *const dragItemV = m_items[static_cast<size_t>(m_draggingCardIndex)];

            std::vector<std::vector<CardItem *>> slotCols(static_cast<size_t>(colCount));
            int colWalk = 0;
            for (int c = 0; c < colCount; ++c) {
                for (int j = 0; j < colSizes[static_cast<size_t>(c)]; ++j, ++colWalk) {
                    if (colWalk != m_draggingCardIndex)
                        slotCols[static_cast<size_t>(c)].push_back(m_items[static_cast<size_t>(colWalk)]);
                }
            }

            const int previewCol = colFromSceneX(
                m_dragMouseScene.x(),
                colCount,
                columnBandV.left(),
                leftPad,
                colContentWidth,
                betweenCols);
            m_dragPreviewOrtho = previewCol;

            const qreal fallbackMainV = baseSize.height() * scale;
            qreal maxExtCol = scaledWidgetHeight(dragItemV->widget(), scale, fallbackMainV);
            for (CardItem *cit : slotCols[static_cast<size_t>(previewCol)]) {
                maxExtCol = qMax(maxExtCol, scaledWidgetHeight(cit->widget(), scale, fallbackMainV));
            }
            const int Kcol = static_cast<int>(slotCols[static_cast<size_t>(previewCol)].size()) + 1;
            qreal stepY = 0;
            qreal offY = 0;
            computeMainAxisLayout(Kcol, availableMain, maxExtCol, stepY, offY);
            m_dragPreviewLocal = mapCoordToNearestSlot(
                m_dragMouseScene.y(), colY0, offY, stepY, maxExtCol, Kcol);

            std::vector<CardItem *> orderPreviewCol = slotCols[static_cast<size_t>(previewCol)];
            const int insV = qBound(0, m_dragPreviewLocal, static_cast<int>(orderPreviewCol.size()));
            orderPreviewCol.insert(orderPreviewCol.begin() + insV, dragItemV);

            const bool colDragReflowAnim = m_dragFollowReady
                && (prevLayoutPreview >= 0 || prevOrthoV >= 0)
                && (prevLayoutPreview != m_dragPreviewLocal || prevOrthoV != previewCol);

            for (int col = 0; col < colCount; ++col) {
                const int nInCol = colSizes[static_cast<size_t>(col)];
                if (nInCol <= 0)
                    continue;

                qreal xSlots = 0;
                if (colCount >= 2) {
                    const qreal colLeft = columnBandV.left() + leftPad + col * (colContentWidth + betweenCols);
                    xSlots = colLeft + (colContentWidth - itemSize.width()) * 0.5;
                } else {
                    xSlots = columnBandV.left() + (bandW - itemSize.width()) * 0.5;
                }

                std::vector<CardItem *> orderCol;
                if (col == previewCol)
                    orderCol = orderPreviewCol;
                else
                    orderCol = slotCols[static_cast<size_t>(col)];

                layoutVerticalColumnOrdered(
                    orderCol,
                    colDragReflowAnim,
                    m_dragPreviewOrtho,
                    m_dragPreviewLocal,
                    scale,
                    baseSize,
                    itemSize,
                    availableMain,
                    colY0,
                    xSlots,
                    m_items,
                    m_slotSceneRects,
                    m_cardPopHoverEnabled,
                    interColCrowd,
                    popUnitFromVerticalFlow(),
                    popUnitFromHorizontalFlow(),
                    m_draggingCardIndex,
                    m_dragFollowReady,
                    &m_dragSlotTopLeftScene,
                    &m_dragMouseScene,
                    &m_dragGrabSceneOffset,
                    &m_dragSmoothedFollowOffset,
                    &m_dragLastSmoothSlotP,
                    &m_dragLastSmoothOrtho);
            }

            m_dragLastLayoutPreviewOrtho = previewCol;
            m_lastDragLayoutPreviewLocal = m_dragPreviewLocal;
        }
    }

    if (m_draggingCardIndex >= 0)
        syncDragPhantom(m_dragPhantomLayoutScale);

    if (m_draggingCardIndex < 0) {
        if (m_hasLastSceneHoverPos)
            updateHoverState(m_lastSceneHoverPos);
        else if (prevHovered >= 0 && prevHovered < N && m_cardPopHoverEnabled[static_cast<size_t>(prevHovered)])
            setHoveredIndex(prevHovered);
    }
}
