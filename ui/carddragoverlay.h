#ifndef CARDDRAGOVERLAY_H
#define CARDDRAGOVERLAY_H

#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QWidget>

/**
 * Top-level drag preview: full-color pixmap positioned under the cursor (hotspot from grab);
 * the tinted drop preview lives in-scene on CardView only.
 */
class CardDragOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    static CardDragOverlayWidget *instance();

    void setDragPixmap(const QPixmap &pm);

    /** Positions and sizes the window to the given screen rectangle (typically from QWidget::mapToGlobal). */
    void setOverlayScreenFrame(const QPoint &globalTopLeft, const QSize &screenSize);

    void clearAndHide();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    explicit CardDragOverlayWidget(QWidget *parent = nullptr);

    QPixmap m_pixmap;
};

#endif // CARDDRAGOVERLAY_H
