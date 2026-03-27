#ifndef DEMOCARDSTACKWIDGET_H
#define DEMOCARDSTACKWIDGET_H

#include "../logic/cards/card.h"

#include <QWidget>

#include <memory>

class DemoCardWidget;

/**
 * CardView / graphics-view demo: stacks several identical DemoCardWidgets with vertical
 * overlap (same idea as CardStackWidget in the real game). One widget → one CardItem,
 * so hover pop lifts the whole pile, not each face card in the row.
 */
class DemoCardStackWidget : public QWidget
{
public:
    explicit DemoCardStackWidget(std::shared_ptr<Card> card, int stackDepth = 1, QWidget *parent = nullptr);

    explicit DemoCardStackWidget(const QString &title,
                                 const QString &imageResourcePath,
                                 int stackDepth = 1,
                                 QWidget *parent = nullptr);

    int stackDepth() const { return m_stackDepth; }

    /** Recreates face cards; clamped to >= 1. */
    void setStackDepth(int depth);

    /** Vertical step between stacked faces (pixels), same role as CardStackWidget overlap. */
    int verticalOverlap() const { return m_verticalOverlap; }

    void setVerticalOverlap(int pixels);

    DemoCardWidget *topCard() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void clearCards();

    void appendFaceCards(int count);

    void updateStackGeometry();

    std::shared_ptr<Card> m_card;
    QString m_title;
    QString m_imageResourcePath;
    bool m_useGameCard = false;
    int m_stackDepth = 1;
    int m_verticalOverlap = 10;

    QList<DemoCardWidget *> m_cards;
};

#endif // DEMOCARDSTACKWIDGET_H
