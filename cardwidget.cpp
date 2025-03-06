#include "cardwidget.h"

#include <QPainterPath>

CardWidget::CardWidget(QPixmap imagePath,
                       QString triggerNumber,
                       QString title,
                       QString description,
                       QString price,
                       QString expension,
                       QColor backgroundColor,
                       QWidget *parent)
    : m_imagePath(imagePath)
    , m_triggerNumber(triggerNumber)
    , m_title(title)
    , m_description(description)
    , m_price(price)
    , m_expension(expension)
    , m_backgroundColor(backgroundColor)
    , QWidget(parent)
{

    int w = 200, h = 300;
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
        emit clicked(); // Emit a signal when clicked
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
