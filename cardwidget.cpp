#include "cardwidget.h"
#include "cards/card.h"

#include <QPainterPath>

CardWidget::CardWidget(QPixmap imagePath,
                       QSet<uchar> triggerNumbers,
                       QString title,
                       QString description,
                       QString price,
                       QString expension,
                       CardType cardType,
                       QWidget *parent)
    : m_imagePath(imagePath)
    , m_triggerNumber(transformQSetToRangeString(triggerNumbers))
    , m_title(title)
    , m_description(description)
    , m_price(price)
    , m_expension(expension)
    , m_cardType(cardType)
    , QWidget(parent)
{
    QSet<CardType> blueTypes = {
        CardType::Agricultiral,
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
    } else if (greenTypes.find(cardType) != greenTypes.end()) {
        m_backgroundColor = greenColor();
    } else if (redTypes.find(cardType) != redTypes.end()) {
        m_backgroundColor = redColor();
    } else if (purpleTypes.find(cardType) != purpleTypes.end() && triggerNumbers.find(0) != triggerNumbers.end()) {
        m_backgroundColor = greyColor();
    } else {
        m_backgroundColor = purpleColor();
    }

    //int w = 200, h = 300;
    int w = 120, h = 228;
    setFixedSize(w, h);

    QLabel* centralImage = new QLabel(this);
    QPixmap pixmap(m_imagePath); // :/cardPublishingHouse.jpeg
    centralImage->setPixmap(pixmap.scaled(w, w, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

    QLabel* descriptionLabel = new QLabel(m_description, this); // description
    descriptionLabel->setContentsMargins(10, 10, 10, 0);
    descriptionLabel->setStyleSheet("color: white; font-size: 13px;");
    descriptionLabel->setAlignment(Qt::AlignCenter);

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
    QHBoxLayout* dataLayout = new QHBoxLayout(this);


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

void CardWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked(m_title); // Emit a signal when clicked
    }
}

void CardWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 15, 15); // Rounded rectangle with 15px radius

    painter.setClipPath(path);
    painter.fillPath(path, m_backgroundColor); // Fill with color
}

QColor CardWidget::blueColor() const {
    return QColor(111, 183, 214);
}

QColor CardWidget::goldColor() const {
    return QColor(255, 250, 129);
}

QColor CardWidget::greenColor() const {
    return QColor(72, 181, 163);
}

QColor CardWidget::greyColor() const {
    return QColor(192, 186, 153);
}

QColor CardWidget::purpleColor() const {
    return QColor(165, 137, 193);
}

QColor CardWidget::redColor() const {
    return QColor(252, 169, 133);
}

QString CardWidget::transformQSetToRangeString(const QSet<uchar>& set) {
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
