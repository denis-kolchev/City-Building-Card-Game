#ifndef CARDSCROLLWIDGET_H
#define CARDSCROLLWIDGET_H

#include "cardstackwidget.h"

#include <QWidget>

// Layout is outside of this to place it on
// Card

using CardStacks = QMap<uchar, CardStackWidget*>;
using CardList = QVector<std::shared_ptr<Card>>;

class CardScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardScrollWidget(QWidget *parent = nullptr);

    void placeCards(const CardList &cards);

    void removeCards(const CardList &cards);

    void turnOn(uchar id);

    void turnOff(uchar id);

signals:
    void activateCardsHighlighting(int playerBalance);

    void cardSignalClicked(uchar id);

    void deactivateCardsHighlighting();

public slots:
    void handleCardClicked(uchar id);

private:
    void sortCardsById();

private:
    CardStacks m_stacks;

    QHBoxLayout* m_layout;
};

#endif // CARDSCROLLWIDGET_H
