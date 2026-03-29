#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsProxyWidget>
#include <QPainterPath>
#include <QPointF>

class QVariantAnimation;

class CardItem : public QGraphicsProxyWidget
{
public:
    static constexpr qreal hoverLift() { return 25; }

    /** Z value while at rest in the stack (set from layout order). */
    static constexpr qreal stackZFromIndex(int index) { return static_cast<qreal>(index); }

    /** Always above every resting card so the lifted card is fully visible. */
    static constexpr qreal poppedZValue() { return 1.0e6; }

    explicit CardItem(QWidget *w);

    void setBaseScenePos(const QPointF &scenePos);

    /** Smooth move for layout reflow (cancels any in-flight base animation). */
    void setBaseScenePosAnimated(const QPointF &scenePos, int durationMs = 180);

    void setStackZ(qreal z);

    QPointF baseScenePos() const { return m_baseScenePos; }

    /** Unit direction of pop offset in scene space; e.g. (0,-1) up, (1,0) right, one axis only. */
    void setPopLiftVector(qreal unitX, qreal unitY);

    QPointF popLiftUnit() const { return m_popLiftUnit; }

    /** Scene delta from hover peek (popLiftUnit × current lift). Drag math subtracts this from slot + dragOffset. */
    QPointF hoverLiftSceneOffset() const;

    /** Hover “peek” lift. Use animateHoverLift=false when starting a drag so stacks don’t tween down under the cursor. */
    void setPopped(bool popped, bool animateHoverLift = true);

    /** Extra scene translation while the user drags the card (applied on top of base + pop lift). */
    void setDragOffset(const QPointF &sceneDelta);

    QPointF dragOffset() const { return m_dragOffset; }

    QPainterPath shape() const override;

private:
    void startLiftAnimation(qreal targetLift);

    void applyLiftGeometry();

    QPointF m_baseScenePos;
    QPointF m_dragOffset;
    qreal m_stackZ = 0;
    qreal m_currentLift = 0;
    bool m_popped = false;
    QPointF m_popLiftUnit{0, -1};
    QVariantAnimation *m_liftAnimation = nullptr;
    QVariantAnimation *m_basePosAnimation = nullptr;
};

#endif // CARDITEM_H
