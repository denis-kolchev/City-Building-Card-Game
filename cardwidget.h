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
                        QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

signals:
    void clicked(QString cardTitle);

private:
    QColor blueColor() const;

    QColor goldColor() const;

    QColor greenColor() const;

    QColor greyColor() const;

    QColor purpleColor() const;

    QColor redColor() const;

    QString transformQSetToRangeString(const QSet<uchar>& set);

private:
    QPixmap m_imagePath;
    QString m_triggerNumber;
    QString m_title;
    QString m_description;
    QString m_price;
    QString m_expension;
    QColor m_backgroundColor;
    CardType m_cardType;
};

#endif // CARDWIDGET_H
