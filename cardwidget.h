#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include "cards/card.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QPixmap imagePath,
                        QSet<uchar> triggerNumbers,
                        QString title,
                        QString description,
                        QString price,
                        QString expension,
                        CardType cardType,
                        uchar id,
                        QWidget *parent = nullptr);

    void landmarkUnlocked();

    uchar id();

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

signals:
    void clicked(uchar cardId);

private:
    QColor blueColor() const;

    QColor blueOutlineColor() const;

    QColor goldColor() const;

    QColor goldOutlineColor() const;

    QColor greenColor() const;

    QColor greenOutlineColor() const;

    QColor greyColor() const;

    QColor greyOutlineColor() const;

    QColor purpleColor() const;

    QColor purpleOutlineColor() const;

    QColor redColor() const;

    QColor redOutlineColor() const;

    QString replaceSubstringWithEmoji(const QString &input, const QString &substring, const QString &emoji);

    QString transformQSetToRangeString(const QSet<uchar>& set);

private:
    QPixmap m_imagePath;
    QString m_triggerNumber;
    QString m_title;
    QString m_description;
    QString m_price;
    QString m_expension;
    QColor m_backgroundColor;
    QColor m_outlineColor;
    CardType m_cardType;
    uchar m_id;
};

#endif // CARDWIDGET_H
