#ifndef CARDWIDGET_H
#define CARDWIDGET_H

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
                        QString triggerNumber,
                        QString title,
                        QString description,
                        QString price,
                        QString expension,
                        QColor backgroundColor,
                        QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

signals:
    void clicked();

private:
    QColor blueColor() const;

    QColor goldColor() const;

    QColor greenColor() const;

    QColor greyColor() const;

    QColor redColor() const;

private:
    QPixmap m_imagePath;
    QString m_triggerNumber;
    QString m_title;
    QString m_description;
    QString m_price;
    QString m_expension;
    QColor m_backgroundColor;
};

#endif // CARDWIDGET_H
