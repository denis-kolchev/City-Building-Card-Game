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

    void setStackZ(qreal z);

    QPointF baseScenePos() const { return m_baseScenePos; }

    /** Unit direction of pop offset in scene space; e.g. (0,-1) up, (1,0) right, one axis only. */
    void setPopLiftVector(qreal unitX, qreal unitY);

    QPointF popLiftUnit() const { return m_popLiftUnit; }

    void setPopped(bool popped);

    QPainterPath shape() const override;

private:
    void startLiftAnimation(qreal targetLift);

    void applyLiftGeometry();

    QPointF m_baseScenePos;
    qreal m_stackZ = 0;
    qreal m_currentLift = 0;
    bool m_popped = false;
    QPointF m_popLiftUnit{0, -1};
    QVariantAnimation *m_liftAnimation = nullptr;
};

#endif // CARDITEM_H
