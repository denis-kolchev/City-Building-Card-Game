#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "carditem.h"

#include <QGraphicsView>
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
class QMouseEvent;
class QEvent;
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

private:
    void scheduleLayout();

    void layoutItems();

    void updateHoverState(const QPointF &scenePoint);

    void setHoveredIndex(int index);

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
