#include "democardwidget.h"

#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QScreen>
#include <QShowEvent>
#include <QVBoxLayout>
#include <QWindow>

#include <algorithm>

namespace {

qreal effectiveDevicePixelRatio(const QWidget *w)
{
    if (!w)
        return 1.0;
    if (w->windowHandle())
        return w->windowHandle()->devicePixelRatio();
    if (const QScreen *s = QGuiApplication::primaryScreen())
        return s->devicePixelRatio();
    return 1.0;
}

} // namespace

DemoCardWidget::DemoCardWidget(std::shared_ptr<Card> card, QWidget *parent)
    : DemoCardWidget(QPixmap(card->imagePath()),
                     card->activationValues(),
                     card->title(),
                     card->description(),
                     QString::number(card->price()),
                     QString::number(card->pack()),
                     card->type(),
                     card->id(),
                     parent)
{
}

DemoCardWidget::DemoCardWidget(const QPixmap &cardImage,
                               const QSet<int> &triggerNumbers,
                               const QString &title,
                               const QString &description,
                               const QString &price,
                               const QString &expansion,
                               CardType cardType,
                               CardId id,
                               QWidget *parent)
    : BaseCardWidget(parent)
    , m_cardPixmap(cardImage)
    , m_triggerNumber(transformQSetToRangeString(triggerNumbers))
    , m_title(title)
    , m_description(description)
    , m_price(price)
    , m_expansion(expansion)
    , m_cardType(cardType)
    , m_id(id)
    , m_outlineAnimation(std::make_shared<QPropertyAnimation>(this, "outlineColor"))
{
    setCardType();

    switch (m_cardType) {
    case CardType::Agricultural:
    case CardType::Farm:
    case CardType::Mining:
    case CardType::Ship:
        m_backgroundColor = blueColor();
        m_baseOutlineColor = blueOutlineColor();
        break;
    case CardType::Fruit:
    case CardType::Production:
    case CardType::Shop:
    case CardType::Business:
        m_backgroundColor = greenColor();
        m_baseOutlineColor = greenOutlineColor();
        break;
    case CardType::Dining:
        m_backgroundColor = redColor();
        m_baseOutlineColor = redOutlineColor();
        break;
    case CardType::Landmark:
        m_backgroundColor = purpleColor();
        m_baseOutlineColor = purpleOutlineColor();
        break;
    }

    if (triggerNumbers.contains(0)) {
        m_backgroundColor = greyColor();
        m_baseOutlineColor = greyOutlineColor();
    }

    m_outlineColor = baseOutlineColor();

    m_outlineAnimation->setDuration(1000);
    m_outlineAnimation->setLoopCount(-1);
    m_outlineAnimation->setStartValue(outlineColor().lighter(150));
    m_outlineAnimation->setEndValue(outlineColor().darker(150));

    setFixedSize(150, 250);
    setStyleSheet(QString());

    const int w = 150;

    auto *centralImage = new QLabel(this);
    m_centralImageLabel = centralImage;
    centralImage->setAlignment(Qt::AlignCenter);
    updateCentralImagePixmap();

    auto *diceTriggerNumber = new QLabel(m_triggerNumber, this);
    diceTriggerNumber->setAlignment(Qt::AlignCenter);
    diceTriggerNumber->setStyleSheet(QStringLiteral("color: white; font-size: 12px;"));
    diceTriggerNumber->setContentsMargins(4, 8, 4, 2);

    auto *cardTitle = new QLabel(m_title, this);
    cardTitle->setContentsMargins(2, 4, 4, 10);
    cardTitle->setAlignment(Qt::AlignCenter);
    cardTitle->setStyleSheet(QStringLiteral("color: white; font-size: 14px; font-weight: bold;"));
    cardTitle->setTextFormat(Qt::PlainText);

    auto *descriptionLabel = new QLabel(m_description, this);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setContentsMargins(10, 10, 10, 0);
    descriptionLabel->setStyleSheet(QStringLiteral("color: white; font-size: 10px;"));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setTextFormat(Qt::PlainText);

    auto *priceLabel = new QLabel(m_price, this);
    priceLabel->setContentsMargins(10, 10, 10, 10);
    priceLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    priceLabel->setStyleSheet(QStringLiteral("color: white; font-size: 12px;"));

    auto *expansionLabel = new QLabel(m_expansion, this);
    expansionLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    expansionLabel->setStyleSheet(QStringLiteral("color: white; font-size: 12px;"));
    expansionLabel->setContentsMargins(10, 10, 10, 10);

    auto *mainLayout = new QVBoxLayout(this);
    auto *dataLayout = new QHBoxLayout();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    dataLayout->setContentsMargins(0, 0, 0, 0);
    dataLayout->setSpacing(0);

    mainLayout->addWidget(diceTriggerNumber);
    mainLayout->addWidget(cardTitle);
    mainLayout->addWidget(centralImage);
    mainLayout->addWidget(descriptionLabel);

    dataLayout->addWidget(priceLabel);
    dataLayout->addWidget(expansionLabel);

    mainLayout->addLayout(dataLayout);

    setLayout(mainLayout);
}

DemoCardWidget::DemoCardWidget(const QString &title, const QString &imageResourcePath, QWidget *parent)
    : DemoCardWidget(QPixmap(imageResourcePath),
                       QSet<int>{1, 2, 3},
                       title,
                       QStringLiteral("Demo: gain 1 coin on your turn."),
                       QStringLiteral("3"),
                       QStringLiteral("1"),
                       CardType::Shop,
                       CardId::None,
                       parent)
{
}

DemoCardWidget::DemoCardWidget(const QString &title, QWidget *parent)
    : DemoCardWidget(title, QStringLiteral(":/images/cardWheatField.jpeg"), parent)
{
}

QColor DemoCardWidget::baseOutlineColor() const
{
    return m_baseOutlineColor;
}

void DemoCardWidget::landmarkUnlocked()
{
}

CardId DemoCardWidget::id() const
{
    return m_id;
}

QColor DemoCardWidget::outlineColor() const
{
    return m_outlineColor;
}

int DemoCardWidget::price() const
{
    return m_price.toInt();
}

void DemoCardWidget::setOutlineColor(const QColor &color)
{
    if (m_outlineColor != color) {
        m_outlineColor = color;
        update();
        emit outlineColorChanged();
    }
}

void DemoCardWidget::startOutlineHighlight()
{
    m_outlineAnimation->start();
}

void DemoCardWidget::stopOutlineHighlight()
{
    if (m_outlineAnimation)
        m_outlineAnimation->stop();
    m_outlineColor = baseOutlineColor();
}

void DemoCardWidget::turnOn()
{
    const QSet<CardType> blueTypes = {
        CardType::Agricultural,
        CardType::Farm,
        CardType::Mining,
        CardType::Ship
    };

    const QSet<CardType> greenType = {
        CardType::Business,
        CardType::Fruit,
        CardType::Production,
        CardType::Shop
    };

    if (m_triggerNumber == QStringLiteral("0")) {
        m_backgroundColor = goldColor();
        m_outlineColor = goldOutlineColor();
    } else if (CardType::Landmark == m_cardType) {
        m_backgroundColor = purpleColor();
        m_outlineColor = purpleOutlineColor();
    } else if (greenType.contains(m_cardType)) {
        m_backgroundColor = greenColor();
        m_outlineColor = greenOutlineColor();
    } else if (blueTypes.contains(m_cardType)) {
        m_backgroundColor = blueColor();
        m_outlineColor = blueOutlineColor();
    }

    update();
}

void DemoCardWidget::turnOff()
{
    m_backgroundColor = greyColor();
    m_outlineColor = greyOutlineColor();
    update();
}

void DemoCardWidget::showEvent(QShowEvent *event)
{
    BaseCardWidget::showEvent(event);
    updateCentralImagePixmap();
}

void DemoCardWidget::updateCentralImagePixmap()
{
    if (!m_centralImageLabel || m_cardPixmap.isNull())
        return;

    constexpr int cardW = 150;
    const int pixmapWidth = cardW - 2 * 3;
    const int pixmapHeight = cardW - 2 * 3;

    const qreal dpr = qMax(1.0, effectiveDevicePixelRatio(this));
    const int pw = qMax(1, qRound(pixmapWidth * dpr));
    const int ph = qMax(1, qRound(pixmapHeight * dpr));

    QPixmap scaled = m_cardPixmap.scaled(pw, ph, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scaled.setDevicePixelRatio(dpr);
    m_centralImageLabel->setPixmap(scaled);
}

void DemoCardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(m_id);
    BaseCardWidget::mousePressEvent(event);
}

void DemoCardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // Concentric rounded rects: a stroked path centers the pen on one curve, so the inner
    // edge of the border did not share the same radius as a true inset rounded rect.
    // Outer − inner ring keeps inner and outer corners parallel (matching radii offset).
    const QRectF bounds(rect());
    constexpr qreal kOuterR = 15.0;
    /** Half of former 6px stroke — inner edge of border band (keep this arc geometry). */
    constexpr qreal kBorderHalf = 3.0;

    QPainterPath outerPath;
    outerPath.addRoundedRect(bounds, kOuterR, kOuterR);

    const QRectF innerBounds = bounds.adjusted(kBorderHalf, kBorderHalf, -kBorderHalf, -kBorderHalf);
    const qreal innerR = qMax(0.0, kOuterR - kBorderHalf);
    QPainterPath innerPath;
    innerPath.addRoundedRect(innerBounds, innerR, innerR);

    painter.fillPath(innerPath, m_backgroundColor);

    const QPainterPath ringPath = outerPath.subtracted(innerPath);
    if (!ringPath.isEmpty())
        painter.fillPath(ringPath, m_outlineColor);
}

QColor DemoCardWidget::blueColor() const
{
    return QColor(111, 183, 214);
}

QColor DemoCardWidget::blueOutlineColor() const
{
    return QColor(91, 163, 194);
}

QColor DemoCardWidget::goldColor() const
{
    return QColor(225, 207, 51);
}

QColor DemoCardWidget::goldOutlineColor() const
{
    return QColor(205, 187, 31);
}

QColor DemoCardWidget::greenColor() const
{
    return QColor(72, 181, 163);
}

QColor DemoCardWidget::greenOutlineColor() const
{
    return QColor(52, 161, 143);
}

QColor DemoCardWidget::greyColor() const
{
    return QColor(192, 186, 153);
}

QColor DemoCardWidget::greyOutlineColor() const
{
    return QColor(172, 166, 133);
}

QColor DemoCardWidget::purpleColor() const
{
    return QColor(165, 137, 193);
}

QColor DemoCardWidget::purpleOutlineColor() const
{
    return QColor(135, 117, 173);
}

QColor DemoCardWidget::redColor() const
{
    return QColor(252, 169, 133);
}

QColor DemoCardWidget::redOutlineColor() const
{
    return QColor(232, 149, 113);
}

QString DemoCardWidget::replaceSubstringWithEmoji(const QString &input, const QString &substring, const QString &emoji)
{
    QString result = input;
    result.replace(substring, emoji);
    return result;
}

void DemoCardWidget::setCardType()
{
    const QMap<CardType, QString> emojiMap = {
        {CardType::Agricultural, QStringLiteral("\u2600")},
        {CardType::Business, QStringLiteral("\u26EA")},
        {CardType::Dining, QStringLiteral("\u2615")},
        {CardType::Farm, QStringLiteral("\u26F0")},
        {CardType::Fruit, QStringLiteral("\u26FA")},
        {CardType::Landmark, QStringLiteral("\u26E9")},
        {CardType::Mining, QStringLiteral("\u2699")},
        {CardType::Production, QStringLiteral("\u267B")},
        {CardType::Ship, QStringLiteral("\u26F4")},
        {CardType::Shop, QStringLiteral("\u26F1")}
    };

    if (emojiMap.contains(m_cardType))
        m_title = emojiMap[m_cardType] + QLatin1Char(' ') + m_title;

    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("coffee shop"), emojiMap[CardType::Dining]);
    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("store"), emojiMap[CardType::Shop]);
    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("landmark"), emojiMap[CardType::Landmark]);
    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("farm"), emojiMap[CardType::Farm]);
    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("mining"), emojiMap[CardType::Mining]);
    m_description = replaceSubstringWithEmoji(m_description, QStringLiteral("agricultiral"), emojiMap[CardType::Agricultural]);
}

QString DemoCardWidget::transformQSetToRangeString(const QSet<int> &set)
{
    if (set.isEmpty())
        return QString();

    auto sortedList = set.values();
    std::sort(sortedList.begin(), sortedList.end());

    QString result;
    int start = sortedList.first();
    int prev = start;

    for (int i = 1; i < sortedList.size(); ++i) {
        const int current = sortedList[i];
        if (int(current) != int(prev) + 1) {
            if (start == prev)
                result += QString::number(int(start)) + QStringLiteral(", ");
            else
                result += QString::number(int(start)) + QLatin1Char('-') + QString::number(int(prev))
                    + QStringLiteral(", ");
            start = current;
        }
        prev = current;
    }

    if (start == prev)
        result += QString::number(int(start));
    else
        result += QString::number(int(start)) + QLatin1Char('-') + QString::number(int(prev));

    return result;
}
