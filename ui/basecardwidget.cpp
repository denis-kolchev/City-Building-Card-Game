#include "basecardwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

BaseCardWidget::BaseCardWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("cbcg_BaseCardWidget"));
    setAutoFillBackground(false);
    setFixedSize(defaultCardSize());
    applyCardChromeStyleSheet();
    refreshTranslucentAttribute();
}

QSize BaseCardWidget::defaultCardSize()
{
    return QSize(120, 160);
}

void BaseCardWidget::setCornerRadius(qreal radius)
{
    const qreal r = qMax(0.0, radius);
    if (qFuzzyCompare(m_cornerRadius, r))
        return;
    m_cornerRadius = r;
    refreshTranslucentAttribute();
    update();
}

void BaseCardWidget::setCardFillColor(const QColor &color)
{
    if (m_fillColor == color)
        return;
    m_fillColor = color;
    refreshTranslucentAttribute();
    update();
}

void BaseCardWidget::setCardBorderColor(const QColor &color)
{
    if (m_borderColor == color)
        return;
    m_borderColor = color;
    update();
}

void BaseCardWidget::setCardBorderWidth(int widthPx)
{
    const int w = qMax(0, widthPx);
    if (m_borderWidth == w)
        return;
    m_borderWidth = w;
    update();
}

void BaseCardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QRectF bounds(rect());
    QPainterPath outerPath;
    outerPath.addRoundedRect(bounds, m_cornerRadius, m_cornerRadius);

    if (m_borderWidth <= 0 || m_borderColor.alpha() <= 0) {
        if (m_fillColor.alpha() > 0)
            painter.fillPath(outerPath, m_fillColor);
        return;
    }

    // Parallel border: inner rounded rect = outer inset by half stroke (same as centered pen).
    const qreal inset = static_cast<qreal>(m_borderWidth) * 0.5;
    const QRectF innerBounds = bounds.adjusted(inset, inset, -inset, -inset);
    const qreal innerR = qMax(0.0, m_cornerRadius - inset);
    QPainterPath innerPath;
    innerPath.addRoundedRect(innerBounds, innerR, innerR);

    if (m_fillColor.alpha() > 0)
        painter.fillPath(innerPath, m_fillColor);

    const QPainterPath ringPath = outerPath.subtracted(innerPath);
    if (!ringPath.isEmpty())
        painter.fillPath(ringPath, m_borderColor);
}

void BaseCardWidget::applyCardChromeStyleSheet()
{
    setStyleSheet(QString());
}

void BaseCardWidget::refreshTranslucentAttribute()
{
    // Unpainted areas outside the rounded path must be transparent so anti-aliased edge
    // pixels blend with the scene (setMask would force a binary silhouette and look jagged).
    const bool needAlpha = m_cornerRadius > 0.0 || m_fillColor.alpha() < 255;
    setAttribute(Qt::WA_TranslucentBackground, needAlpha);
}
