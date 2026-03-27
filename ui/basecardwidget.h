#ifndef BASECARDWIDGET_H
#define BASECARDWIDGET_H

#include <QColor>
#include <QSize>
#include <QWidget>

class QPaintEvent;

/**
 * QWidget base for content embedded in CardView via CardItem.
 * Rounded chrome is painted with antialiased paths (no QWidget::setMask — masks are 1-bit
 * and produce stair-stepped edges when scaled in QGraphicsView).
 */
class BaseCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseCardWidget(QWidget *parent = nullptr);

    static QSize defaultCardSize();

    /** Corner radius in device pixels (default matches game card widgets, ~15). */
    void setCornerRadius(qreal radius);
    qreal cornerRadius() const { return m_cornerRadius; }

    /** Card interior fill; use QColor(0, 0, 0, 0) for a fully transparent face. */
    void setCardFillColor(const QColor &color);
    QColor cardFillColor() const { return m_fillColor; }

    void setCardBorderColor(const QColor &color);
    QColor cardBorderColor() const { return m_borderColor; }

    void setCardBorderWidth(int widthPx);
    int cardBorderWidth() const { return m_borderWidth; }

protected:
    void paintEvent(QPaintEvent *event) override;

    /** Clears stylesheet so custom painting is visible. */
    void applyCardChromeStyleSheet();

private:
    void refreshTranslucentAttribute();

    qreal m_cornerRadius = 15.0;
    QColor m_fillColor{Qt::white};
    QColor m_borderColor{Qt::black};
    int m_borderWidth = 2;
};

#endif // BASECARDWIDGET_H
