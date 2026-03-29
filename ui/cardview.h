#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "carditem.h"

#include <QGraphicsView>
#include <QPoint>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <vector>

enum class Orientation {
    Horizontal,
    Vertical
};

/**
 * Pop lift in scene space.
 * Horizontal CardView: Up/Down when cards stack along X in a row; Left/Right is used when
 * multiple rows crowd vertically (no horizontal overlap in the row).
 * Vertical CardView: Left/Right when cards stack along Y in a column; Up/Down when columns crowd horizontally.
 */
enum class PopLiftDirection {
    Up,
    Down,
    Left,
    Right
};

class QGraphicsScene;
class QGraphicsPixmapItem;
class QMouseEvent;
class QEvent;
class QTimer;
class BaseCardWidget;

class CardView : public QGraphicsView
{
public:
    explicit CardView(QWidget *parent = nullptr);

    void setOrientation(Orientation o);

    /**
     * Sets both row count (horizontal flow) and column count (vertical flow) to the same value
     * so it works no matter whether you call this before or after setOrientation (>= 1).
     */
    void setOrthogonalLineCount(int count);

    int orthogonalLineCount() const;

    /** One argument: Up/Down updates horizontal-flow pop; Left/Right updates vertical-flow pop. */
    void setPopLiftDirection(PopLiftDirection direction);

    /** Two arguments: first is pop when flow is horizontal (Up or Down), second when vertical (Left or Right). */
    void setPopLiftDirection(PopLiftDirection horizontalFlow, PopLiftDirection verticalFlow);

    PopLiftDirection horizontalFlowPopDirection() const { return m_horizontalFlowPop; }

    PopLiftDirection verticalFlowPopDirection() const { return m_verticalFlowPop; }

    /** Any QWidget (custom card UIs, or plain controls). */
    void addWidget(QWidget *w);

    /** Convenience for BaseCardWidget-derived cards; same as addWidget. */
    void addCard(BaseCardWidget *card);

    Orientation flowOrientation() const { return m_orientation; }

    /** Runs layout immediately (deferred timer may lag behind embedded widget resize). */
    void relayoutNow();

protected:
    /** Horizontal flow: how many rows (equal height). */
    void setHorizontalRowCount(int rows);

    /** Vertical flow: how many columns (equal width). */
    void setVerticalColumnCount(int columns);

    /** Must be Up or Down. */
    void setHorizontalPopDirection(PopLiftDirection direction);

    /** Must be Left or Right. */
    void setVerticalPopDirection(PopLiftDirection direction);

    void resizeEvent(QResizeEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    bool viewportEvent(QEvent *event) override;

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void scheduleLayout();

    void layoutItems();

    void updateHoverState(const QPointF &scenePoint);

    void setHoveredIndex(int index, bool animateHoverLift = true);

    /** Topmost card under point, or -1. Uses slot rects and pop-lift bands (same as hover). */
    int cardIndexAtScenePoint(const QPointF &scenePoint) const;

    void beginCardDrag(int index, const QPointF &scenePos);

    void updateCardDrag(const QPointF &scenePos);

    void endCardDrag();

    void tickDragFollowSmoothing();

    void createDragPhantom(qreal layoutScale);

    void removeDragPhantom();

    void syncDragPhantom(qreal layoutScale);

    /** Scene top-left of the preview drop slot (grid), updated each layout while dragging. */
    QPointF m_dragSlotTopLeftScene;

    /** Cursor minus dragged item top-left at press (scene space). */
    QPointF m_dragGrabSceneOffset;

    /** Smoothed offset from preview slot toward cursor. */
    QPointF m_dragSmoothedFollowOffset;

    int m_dragLastSmoothSlotP = -1000000;

    qreal m_dragPhantomLayoutScale = 1.0;

    /** Top-left of cropped phantom pixmap in widget pixels; positions ghost under scaled stack. */
    QPoint m_dragPhantomAlignOffset;

    QGraphicsPixmapItem *m_dragPhantom = nullptr;

    QTimer *m_dragSmoothTimer = nullptr;

    /** False until m_dragGrabSceneOffset is set after the first layout pass of a drag. */
    bool m_dragFollowReady = false;

    /** Grid drag: span of items in the active row (horizontal flow) or column (vertical flow). */
    int m_dragSpanStart = 0;

    int m_dragSpanLength = 0;

    /** Local index within span at press; drop target is m_dragPreviewLocal. */
    int m_dragFromLocal = 0;

    int m_dragPreviewLocal = 0;

    /** Last preview slot applied in layout (for sibling reflow animation). */
    int m_lastDragLayoutPreviewLocal = -1;

    /** Preview row (horizontal flow) or column (vertical flow) for cross-span drag. */
    int m_dragPreviewOrtho = 0;

    int m_dragLastLayoutPreviewOrtho = -1;

    int m_dragLastSmoothOrtho = -1000000;

    QPointF m_dragMouseScene;

    int m_draggingCardIndex = -1;

    QPointF m_dragStartScene;

    QPointF popUnitFromHorizontalFlow() const;

    QPointF popUnitFromVerticalFlow() const;

    QGraphicsScene *m_scene = nullptr;
    std::vector<CardItem *> m_items;
    std::vector<QRectF> m_slotSceneRects;
    Orientation m_orientation = Orientation::Horizontal;
    bool m_layoutScheduled = false;

    QPointF m_lastSceneHoverPos;
    bool m_hasLastSceneHoverPos = false;
    int m_hoveredIndex = -1;

    /** Per card: pop-on-hover only if that card's row/column is stacked (spread rows don't peek). */
    std::vector<bool> m_cardPopHoverEnabled;

    int m_horizontalRowCount = 1;
    int m_verticalColumnCount = 1;

    PopLiftDirection m_horizontalFlowPop = PopLiftDirection::Up;
    PopLiftDirection m_verticalFlowPop = PopLiftDirection::Left;
};

#endif // CARDVIEW_H
