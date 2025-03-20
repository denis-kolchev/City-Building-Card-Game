#include "cardscrollwidget.h"

CardScrollWidget::CardScrollWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    setLayout(m_layout);
}

void CardScrollWidget::placeCards(const CardList &cards)
{
    for (qsizetype i = 0; i < cards.size(); ++i) {
        CardWidget *cardWidget = new CardWidget(cards[i]->imagePath(),
                                                cards[i]->activationValues(),
                                                cards[i]->title(),
                                                cards[i]->description(),
                                                QString::number(cards[i]->price()),
                                                QString::number(cards[i]->pack()),
                                                cards[i]->type(),
                                                cards[i]->id());

        uchar id = cards[i]->id();
        connect(cardWidget, &CardWidget::clicked, this, &CardScrollWidget::handleCardClicked);

        // create a stack for this card type if wasn't made before
        if (!m_stacks.contains(id)) {
            m_stacks[id] = new CardStackWidget();
            m_layout->addWidget(m_stacks[id]);
        }

        // add a cardWidget to the appropriate stack
        m_stacks[id]->addCard(cardWidget);
    }
    update();
}

void CardScrollWidget::removeCards(const CardList &cards)
{
    for (qsizetype i = 0; i < cards.size(); ++i) {
        uchar id = cards[i]->id();

        // check if a stack exists
        if (m_stacks.contains(id)) {
            auto *stack = m_stacks[id];

            if (!stack->isEmpty()) {
                stack->removeCard(); // Remove a card from the stack
            }

            // If the stack becomes empty, remove it from the layout and delete it
            if (stack->isEmpty()) {
                //layout.removeWidget(stackWidget);
                stack->deleteLater();
                m_stacks.remove(id);
            }
        }
    }
    update();
}

void CardScrollWidget::turnOn(uchar id)
{
    m_stacks[id]->turnOn();
}

void CardScrollWidget::turnOff(uchar id)
{
    m_stacks[id]->turnOff();
}

void CardScrollWidget::handleCardClicked(uchar id)
{
    qDebug() << "[CardScrollWidget] Forwarding ID:" << id; // Debug
    emit this->cardSignalClicked(id);
}
