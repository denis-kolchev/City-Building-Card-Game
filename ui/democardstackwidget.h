#ifndef DEMOCARDSTACKWIDGET_H
#define DEMOCARDSTACKWIDGET_H

#include "../logic/cards/card.h"

#include <QWidget>

#include <memory>

class DemoCardWidget;

/**
 * How identical face cards step and overlap in a single pile (not CardView’s queue axis).
 * Z-order: last index stays visually on top after layout (same as a physical deck).
 */
enum class StackDirection {
    /** Back at top; faces step downward (+Y). */
    VerticalDown,
    /** Back at bottom; faces step upward (−Y). */
    VerticalUp,
    /** Back at left; faces step rightward (+X). */
    HorizontalRight,
    /** Back at right; faces step leftward (−X). */
    HorizontalLeft,
};

/**
 * CardView / graphics-view demo: stacks several identical DemoCardWidgets with stepped
 * overlap (same idea as CardStackWidget in the real game). One widget → one CardItem,
 * so hover pop lifts the whole pile, not each face card in the row.
 */
class DemoCardStackWidget : public QWidget
{
public:
    explicit DemoCardStackWidget(std::shared_ptr<Card> card, QWidget *parent = nullptr);

    explicit DemoCardStackWidget(const QString &title,
                                 const QString &imageResourcePath,
                                 QWidget *parent = nullptr);

    /** Number of identical face widgets in this pile; clamped to >= 1 in setters. */
    int cardCount() const { return m_cardCount; }

    void setCardCount(int count);

    int stackDepth() const { return cardCount(); }

    void setStackDepth(int depth) { setCardCount(depth); }

    /** Step between stacked faces along the pile axis (pixels); vertical and horizontal piles. */
    int stackOverlap() const { return m_stackOverlap; }

    void setStackOverlap(int pixels);

    int verticalOverlap() const { return stackOverlap(); }

    void setVerticalOverlap(int pixels) { setStackOverlap(pixels); }

    StackDirection stackDirection() const { return m_stackDirection; }

    void setStackDirection(StackDirection d);

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
    int m_cardCount = 1;
    int m_stackOverlap = 10;
    StackDirection m_stackDirection = StackDirection::VerticalDown;

    QList<DemoCardWidget *> m_cards;
};

#endif // DEMOCARDSTACKWIDGET_H
