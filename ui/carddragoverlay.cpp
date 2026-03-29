#include "carddragoverlay.h"

#include <QPainter>
#include <QPaintEvent>

CardDragOverlayWidget *CardDragOverlayWidget::instance()
{
    static CardDragOverlayWidget *s = new CardDragOverlayWidget;
    return s;
}

CardDragOverlayWidget::CardDragOverlayWidget(QWidget *parent)
    : QWidget(nullptr,
                Qt::Tool | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus
                    | Qt::WindowTransparentForInput)
{
    Q_UNUSED(parent);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
}

void CardDragOverlayWidget::setDragPixmap(const QPixmap &pm)
{
    m_pixmap = pm;
}

void CardDragOverlayWidget::setOverlayScreenFrame(const QPoint &globalTopLeft, const QSize &screenSize)
{
    const int w = qMax(1, screenSize.width());
    const int h = qMax(1, screenSize.height());
    move(globalTopLeft);
    resize(w, h);
    setFixedSize(w, h);
    raise();
    update();
}

void CardDragOverlayWidget::clearAndHide()
{
    m_pixmap = QPixmap();
    hide();
}

void CardDragOverlayWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (m_pixmap.isNull())
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    const QRect target(0, 0, width(), height());
    p.drawPixmap(target, m_pixmap);
}
