#include "wheatfield.h"

WheatField::WheatField(const QString& title,
                       const QString& description,
                       const QString& imagePath,
                       const QSet<int>& activationValues,
                       CardType type,
                       int pack,
                       int price,
                       CardId id)
    : Card(title,
           description,
           imagePath,
           activationValues,
           type,
           pack,
           price,
           id)
{
}

void WheatField::activate(QVector<std::shared_ptr<Player>>& players,
                          Player& owner,
                          Player& activePlayer,
                          int dice1,
                          int dice2)
{
    if (hasActivationValue(dice1 + dice2)) {
        owner.addCoins(1);
        qDebug() << "--- " << m_title << " - " << owner.name() << " gain income: " << 1;
    }
}
