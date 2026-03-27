#ifndef DEMOCARDWIDGET_H
#define DEMOCARDWIDGET_H

#include "basecardwidget.h"
#include "../logic/cards/card.h"

#include <QColor>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSet>
#include <memory>
#include <QString>

class QLabel;
class QMouseEvent;
class QPaintEvent;
class QShowEvent;

class DemoCardWidget : public BaseCardWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor NOTIFY outlineColorChanged)

public:
    /** Same data path as CardScrollWidget::placeCards / new CardWidget(...). */
    explicit DemoCardWidget(std::shared_ptr<Card> card, QWidget *parent = nullptr);

    explicit DemoCardWidget(const QPixmap &cardImage,
                            const QSet<int> &triggerNumbers,
                            const QString &title,
                            const QString &description,
                            const QString &price,
                            const QString &expansion,
                            CardType cardType,
                            CardId id,
                            QWidget *parent = nullptr);

    /** CardView demo: title + path in cardImages.qrc. */
    explicit DemoCardWidget(const QString &title, const QString &imageResourcePath, QWidget *parent = nullptr);

    explicit DemoCardWidget(const QString &title, QWidget *parent = nullptr);

    QColor baseOutlineColor() const;

    void landmarkUnlocked();

    CardId id() const;

    QColor outlineColor() const;

    int price() const;

    void setOutlineColor(const QColor &color);

    void startOutlineHighlight();

    void stopOutlineHighlight();

    void turnOn();

    void turnOff();

signals:
    void clicked(CardId cardId);

    void outlineColorChanged();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void showEvent(QShowEvent *event) override;

private:
    void updateCentralImagePixmap();

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

    void setCardType();

    static QString transformQSetToRangeString(const QSet<int> &set);

    QPixmap m_cardPixmap;
    QString m_triggerNumber;
    QString m_title;
    QString m_description;
    QString m_price;
    QString m_expansion;
    QColor m_backgroundColor;
    QColor m_baseOutlineColor;
    QColor m_outlineColor;
    CardType m_cardType;
    CardId m_id;

    std::shared_ptr<QPropertyAnimation> m_outlineAnimation;

    QLabel *m_centralImageLabel = nullptr;
};

#endif // DEMOCARDWIDGET_H
