#include "carditem.h"

#include <QWidget>
#include <QVariantAnimation>
#include <QEasingCurve>

namespace {
constexpr int liftDurationMs = 220;
}

CardItem::CardItem(QWidget *w)
{
    setWidget(w);
    setAcceptHoverEvents(false);
    // DeviceCoordinateCache scales a pre-rasterized pixmap with item->setScale(); curved edges
    // stair-step badly. NoCache repaints the embedded widget each frame — smoother when scaled.
    setCacheMode(QGraphicsItem::NoCache);
}

void CardItem::setPopLiftVector(qreal unitX, qreal unitY)
{
    const QPointF u(unitX, unitY);
    if (u == m_popLiftUnit)
        return;
    m_popLiftUnit = u;
    prepareGeometryChange();
    applyLiftGeometry();
}

void CardItem::applyLiftGeometry()
{
    QGraphicsProxyWidget::setPos(m_baseScenePos
        + QPointF(m_popLiftUnit.x() * m_currentLift, m_popLiftUnit.y() * m_currentLift));
}

void CardItem::setBaseScenePos(const QPointF &scenePos)
{
    m_baseScenePos = scenePos;
    applyLiftGeometry();
}

void CardItem::setStackZ(qreal z)
{
    m_stackZ = z;
    if (m_currentLift <= 1e-6 && !m_liftAnimation)
        setZValue(m_stackZ);
}

void CardItem::setPopped(bool popped)
{
    if (m_popped == popped) {
        if (!m_liftAnimation) {
            const qreal target = popped ? hoverLift() : 0;
            if (qFuzzyCompare(m_currentLift, target))
                return;
        } else {
            return;
        }
    }
    m_popped = popped;
    const qreal target = m_popped ? hoverLift() : 0;

    if (m_popped)
        setZValue(poppedZValue());

    startLiftAnimation(target);
}

void CardItem::startLiftAnimation(qreal targetLift)
{
    if (m_liftAnimation) {
        disconnect(m_liftAnimation, nullptr, this, nullptr);
        m_liftAnimation->stop();
        m_liftAnimation->deleteLater();
        m_liftAnimation = nullptr;
    }

    if (qFuzzyCompare(m_currentLift, targetLift)) {
        applyLiftGeometry();
        if (targetLift <= 1e-6)
            setZValue(m_stackZ);
        return;
    }

    if (targetLift <= 1e-6)
        setZValue(m_stackZ);
    else if (targetLift > m_currentLift)
        setZValue(poppedZValue());

    auto *anim = new QVariantAnimation(this);
    m_liftAnimation = anim;
    anim->setDuration(liftDurationMs);
    anim->setStartValue(m_currentLift);
    anim->setEndValue(targetLift);
    if (targetLift > m_currentLift)
        anim->setEasingCurve(QEasingCurve::OutCubic);
    else
        anim->setEasingCurve(QEasingCurve::InCubic);

    connect(anim, &QVariantAnimation::valueChanged, this, [this](const QVariant &v) {
        prepareGeometryChange();
        m_currentLift = v.toReal();
        applyLiftGeometry();
    });
    connect(anim, &QVariantAnimation::finished, this, [this, anim, targetLift]() {
        if (m_liftAnimation == anim)
            m_liftAnimation = nullptr;
        m_currentLift = targetLift;
        applyLiftGeometry();
        if (targetLift <= 1e-6)
            setZValue(m_stackZ);
        prepareGeometryChange();
        anim->deleteLater();
    });

    anim->start();
}

QPainterPath CardItem::shape() const
{
    QPainterPath path;
    const QRectF br = boundingRect();
    if (m_currentLift <= 1e-6) {
        path.addRect(br);
        return path;
    }
    const qreal ux = m_popLiftUnit.x();
    const qreal uy = m_popLiftUnit.y();
    if (qFuzzyIsNull(ux)) {
        const qreal sh = br.height() - m_currentLift;
        if (sh <= 0)
            return path;
        if (uy < 0)
            path.addRect(0, m_currentLift, br.width(), sh);
        else
            path.addRect(0, 0, br.width(), sh);
    } else {
        const qreal sw = br.width() - m_currentLift;
        if (sw <= 0)
            return path;
        if (ux < 0)
            path.addRect(m_currentLift, 0, sw, br.height());
        else
            path.addRect(0, 0, sw, br.height());
    }
    return path;
}
