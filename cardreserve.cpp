#include "cardreserve.h"
#include "carddataconfigreader.h"

#include <QDir>
#include <QCoreApplication>

CardReserve::CardReserve(QObject* parent)
    : QObject(parent)
{
    // TO DO this code isn't universal for other platforms
    // find a way to config file
    QString executablePath = QCoreApplication::applicationDirPath();
    QDir sourceDir(executablePath);
    sourceDir.cd("../../../"); // Move on 3 levels up
    QString configPath = sourceDir.absolutePath() + "/CardsDataConfig.ini";
    if (QFile::exists(configPath)) {
        qDebug() << "Config file has found: " << configPath;
    } else {
        qDebug() << "File not found!";
    }

    // read card data from config
    CardDataConfigReader cardReader(configPath);
    auto cards = cardReader.readFromRange(4, 18);
    for (int i = 0; i < cards.size(); ++i) {
        if (cards[i]->type() == CardType::Landmark) {
            m_cards.insert(cards[i], 5);
        } else {
            m_cards.insert(cards[i], 6);
        }
    }
}

CardReserve::~CardReserve()
{
}

void CardReserve::addCard(std::shared_ptr<Card> card)
{
    auto it = m_cards.find(card);
    if (it != m_cards.end()) {
        m_cards.insert(card, m_cards.find(card).value() + 1);
    } else {
        m_cards.insert(card, 1);
    }
}

uchar CardReserve::coundCards(std::shared_ptr<Card> card)
{
    return m_cards.find(card).value();
}

std::shared_ptr<Card> CardReserve::findCardByTitle(QString cardTitle)
{
    std::shared_ptr<Card> card = nullptr;
    for (auto it = m_cards.begin(), ite = m_cards.end(); it != ite; ++it) {
        if (it.key()->title() == cardTitle) {
            card = it.key();
        }
    }
    return card;
}

void CardReserve::removeCard(std::shared_ptr<Card> card)
{
    auto it = m_cards.find(card);
    if (it.value() > 1) {
        m_cards.insert(card, m_cards.find(card).value() + 1);
    } else {
        m_cards.remove(card);
    }
}

void activateCard(const QString& cardName, Player& owner, Player& activePlayer, int diceRoll)
{

}

void CardReserve::handleTryToBuyCard(QString title, uchar playerBalance)
{
    std::shared_ptr<Card> cardClicked = findCardByTitle(title);
    if (!cardClicked) {
        qDebug() << "Eror, card isn't found!";
        std::abort();
    }

    uchar cardPrice = cardClicked->price();
    if (cardPrice <= playerBalance) {
        removeCard(cardClicked);
        emit sellCardToPlayer(cardClicked);
    }
}
