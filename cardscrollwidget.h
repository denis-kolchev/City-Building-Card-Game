#ifndef CARDSCROLLWIDGET_H
#define CARDSCROLLWIDGET_H

#include "cardstackwidget.h"

#include <QWidget>

// Layout is outside of this to place it on
// Card

using cardIdType = uchar;
using CardStacks = QMap<cardIdType, CardStackWidget*>;
using CardList = QVector<std::shared_ptr<Card>>;

class CardScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardScrollWidget(QWidget *parent = nullptr);

    void placeCards(const CardList &cards);

    void removeCards(const CardList &cards);

signals:
    void cardClicked(cardIdType id);

private:
    CardStacks m_stacks;

    QHBoxLayout* m_layout;
};

#endif // CARDSCROLLWIDGET_H
