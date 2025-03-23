#include "cardwidget.h"
#include "cards/card.h"

#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

CardWidget::CardWidget(QPixmap imagePath,
                       QSet<uchar> triggerNumbers,
                       QString title,
                       QString description,
                       QString price,
                       QString expension,
                       CardType cardType,
                       uchar id,
                       QWidget *parent)
    : m_imagePath(imagePath)
    , m_triggerNumber(transformQSetToRangeString(triggerNumbers))
    , m_title(title)
    , m_description(description)
    , m_price(price)
    , m_expension(expension)
    , m_cardType(cardType)
    , m_id(id)
    , m_outlineAnimation(new QPropertyAnimation(this, "outlineColor"))
    , QWidget(parent)
{
    QMap<CardType, QString> emojiMap = {
        {CardType::Agricultural, "\u2600"},
        {CardType::Business, "\u26EA"},
        {CardType::Dining, "\u2615"},
        {CardType::Farm, "\u26F0"},
        {CardType::Fruit, "\u26FA"},
        {CardType::Landmark, "\u26E9"},
        {CardType::Mining, "\u2699"},
        {CardType::Production, "\u267B"},
        {CardType::Ship, "\u26F4"},
        {CardType::Shop, "\u26F1"}
    };

    // Use the map to set the title
    if (emojiMap.contains(m_cardType)) {
        m_title = emojiMap[m_cardType] + " " + m_title;
    }

    QSet<CardType> blueTypes = {
        CardType::Agricultural,
        CardType::Farm,
        CardType::Mining,
        CardType::Ship
    };

    QSet<CardType> greenTypes = {
        CardType::Fruit,
        CardType::Production,
        CardType::Shop
    };

    QSet<CardType> redTypes = {
        CardType::Dining
    };

    QSet<CardType> purpleTypes = {
        CardType::Landmark
    };

    if (blueTypes.find(cardType) != blueTypes.end()) {
        m_backgroundColor = blueColor();
        m_baseOutlineColor = blueOutlineColor();
    } else if (greenTypes.find(cardType) != greenTypes.end()) {
        m_backgroundColor = greenColor();
        m_baseOutlineColor = greenOutlineColor();
    } else if (redTypes.find(cardType) != redTypes.end()) {
        m_backgroundColor = redColor();
        m_baseOutlineColor = redOutlineColor();
    } else if (purpleTypes.find(cardType) != purpleTypes.end() && triggerNumbers.find(0) != triggerNumbers.end()) {
        m_backgroundColor = greyColor();
        m_baseOutlineColor = greyOutlineColor();
    } else {
        m_backgroundColor = purpleColor();
        m_baseOutlineColor = purpleOutlineColor();
    }

    m_outlineColor = baseOutlineColor();

    m_description = replaceSubstringWithEmoji(m_description, "coffee shop", emojiMap[CardType::Dining]);
    m_description = replaceSubstringWithEmoji(m_description, "store", emojiMap[CardType::Shop]);
    m_description = replaceSubstringWithEmoji(m_description, "landmark", emojiMap[CardType::Landmark]);
    m_description = replaceSubstringWithEmoji(m_description, "farm", emojiMap[CardType::Farm]);
    m_description = replaceSubstringWithEmoji(m_description, "mining", emojiMap[CardType::Mining]);
    m_description = replaceSubstringWithEmoji(m_description, "agricultiral", emojiMap[CardType::Agricultural]);

    m_outlineAnimation->setDuration(1000); // duration of animation
    m_outlineAnimation->setLoopCount(-1); // while(true)
    m_outlineAnimation->setStartValue(outlineColor().lighter(150)); // light color
    m_outlineAnimation->setEndValue(outlineColor().darker(150)); // dark color

    //int w = 200, h = 300;
    int w = 150, h = 250;
    setFixedSize(w, h);

    // Adjust the size of the QPixmap to leave space for the outline
    int pixmapWidth = w - 2 * 3;
    int pixmapHeight = w - 2 * 3; // Assuming square image

    QLabel* centralImage = new QLabel(this);
    QPixmap pixmap(m_imagePath); // :/cardPublishingHouse.jpeg
    centralImage->setPixmap(pixmap.scaled(pixmapWidth, pixmapHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    centralImage->setAlignment(Qt::AlignCenter);
    //centralImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *diceTriggerNumber = new QLabel(m_triggerNumber, this); // 9
    diceTriggerNumber->setAlignment(Qt::AlignCenter);
    diceTriggerNumber->setStyleSheet("color: white; font-size: 12px;");
    diceTriggerNumber->setContentsMargins(4, 8, 4, 2);

    QLabel* cardTitple = new QLabel(m_title, this);
    cardTitple->setContentsMargins(2, 4, 4, 10);
    cardTitple->setAlignment(Qt::AlignCenter);
    cardTitple->setStyleSheet("color: white; font-size: 14px;  font-weight: bold;");
    cardTitple->setTextFormat(Qt::PlainText);

    QLabel* descriptionLabel = new QLabel(m_description, this); // description
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setContentsMargins(10, 10, 10, 0);
    descriptionLabel->setStyleSheet("color: white; font-size: 10px;");
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setTextFormat(Qt::PlainText);

    QLabel* priceLabel = new QLabel(m_price, this); // 5
    priceLabel->setContentsMargins(10, 10, 10, 10);
    priceLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    priceLabel->setStyleSheet("color: white; font-size: 12px;");

    QLabel* expensionImage = new QLabel(expension, this);
    expensionImage->setAlignment(Qt::AlignRight | Qt::AlignTop);
    expensionImage->setStyleSheet("color: white; font-size: 12px;");
    expensionImage->setContentsMargins(10, 10, 10, 10);

    // Layouts
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* dataLayout = new QHBoxLayout();


    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    dataLayout->setContentsMargins(0, 0, 0, 0);
    dataLayout->setSpacing(0);

    mainLayout->addWidget(diceTriggerNumber);
    mainLayout->addWidget(cardTitple);
    mainLayout->addWidget(centralImage);
    mainLayout->addWidget(descriptionLabel);

    dataLayout->addWidget(priceLabel);
    dataLayout->addWidget(expensionImage);

    mainLayout->addLayout(dataLayout);

    setLayout(mainLayout);
}

QColor CardWidget::baseOutlineColor() const
{
    return m_baseOutlineColor;
}

uchar CardWidget::id()
{
    return m_id;
}

QColor CardWidget::outlineColor() const
{
    return m_outlineColor;
}

int CardWidget::price()
{
    return m_price.toInt();
}

void CardWidget::setOutlineColor(const QColor &color)
{
    if (m_outlineColor != color) {
        m_outlineColor = color;
        update(); // Перерисовка виджета
        emit outlineColorChanged();
    }
}

void CardWidget::startOutlineHighlight()
{
    m_outlineAnimation->start();
}

void CardWidget::stopOutlineHighlight()
{
    m_outlineAnimation->stop();
    m_outlineColor = baseOutlineColor();
}

void CardWidget::turnOn()
{
    // So it should be somewhere set in some file
    QSet<CardType> blueTypes = {
        CardType::Agricultural,
        CardType::Farm,
        CardType::Mining,
        CardType::Ship
    };

    QSet<CardType> greenType = {
        CardType::Business,
        CardType::Fruit,
        CardType::Production,
        CardType::Shop
    };

    if (m_triggerNumber == "0") {
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

void CardWidget::turnOff()
{
    m_backgroundColor = greyColor();
    m_outlineColor = greyOutlineColor();
    update();
}

void CardWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        //qDebug() << "[CardWidget] Clicked ID:" << m_id; // Debug
        emit clicked(m_id); // Emit a signal when clicked
    }
}

void CardWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 15, 15); // Rounded rectangle with 15px radius

    painter.setClipPath(path);
    painter.fillPath(path, m_backgroundColor); // Fill with color

    // Draw the outline
    QPen pen(m_outlineColor, 6); // Set the outline color and thickness
    painter.setPen(pen);
    painter.drawPath(path);
}

QColor CardWidget::blueColor() const
{
    // QColor(239, 83, 80);
    // QColor(100, 181, 246);
    // QColor(129, 199, 132);
    // QColor(186, 104, 200);
    // QColor(149, 165, 166);
    // QColor(255, 235, 59);

    // QColor(255, 138, 128);
    // QColor(173, 216, 230);
    // QColor(178, 235, 175);
    // QColor(206, 147, 216);
    // QColor(200, 200, 200);
    // QColor(255, 249, 196);

    return QColor(111, 183, 214); // pastel
    //return QColor(25, 118, 210);
}

QColor CardWidget::blueOutlineColor() const
{
    return QColor(91, 163, 194); // pastele
    //return QColor(5, 98, 190);
}

QColor CardWidget::goldColor() const
{
    return QColor(225, 207, 51); // pastele
    //return QColor(251, 192, 45);
}

QColor CardWidget::goldOutlineColor() const
{
    return QColor(205, 187, 31); // pastele
    //return QColor(231, 172, 25);
}

QColor CardWidget::greenColor() const
{
    return QColor(72, 181, 163); // pastele
    //return QColor(56, 142, 60);
}

QColor CardWidget::greenOutlineColor() const
{
    return QColor(52, 161, 143); // pastele
    //return QColor(36, 132, 40);
}

QColor CardWidget::greyColor() const
{
    return QColor(192, 186, 153); // pastele
    //return QColor(97, 97, 97);
}

QColor CardWidget::greyOutlineColor() const
{
    return QColor(172, 166, 133); // pastele
    //return QColor(77, 77, 77);
}

QColor CardWidget::purpleColor() const
{
    return QColor(165, 137, 193); // pastele
    //return QColor(123, 31, 162);
}

QColor CardWidget::purpleOutlineColor() const
{
    return QColor(135, 117, 173); // pastele
    //return QColor(103, 11, 142);
}

QColor CardWidget::redColor() const
{
    return QColor(252, 169, 133); // pastele
    //return QColor(211, 47, 47);
}

QColor CardWidget::redOutlineColor() const
{
    return QColor(232, 149, 113); // pastele
    //return QColor(191, 27, 27);
}

QString CardWidget::replaceSubstringWithEmoji(const QString &input, const QString &substring, const QString &emoji)
{
    QString result = input;
    result.replace(substring, emoji);
    return result;
}

QString CardWidget::transformQSetToRangeString(const QSet<uchar>& set)
{
    if (set.isEmpty()) {
        return QString();
    }

    // Convert QSet to QList and sort it
    QList<uchar> sortedList = set.values();
    std::sort(sortedList.begin(), sortedList.end());

    QString result;
    int start = sortedList.first();
    int prev = start;

    for (int i = 1; i < sortedList.size(); ++i) {
        int current = sortedList[i];
        if (current != prev + 1) {
            if (start == prev) {
                result += QString::number(start) + ", ";
            } else {
                result += QString::number(start) + "-" + QString::number(prev) + ", ";
            }
            start = current;
        }
        prev = current;
    }

    // Handle the last range or single number
    if (start == prev) {
        result += QString::number(start);
    } else {
        result += QString::number(start) + "-" + QString::number(prev);
    }

    return result;
}
