#include "flowlayout.h"

#include <QWidget>

FlowLayout::FlowLayout(QWidget* parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    QLayoutItem* item;
    while ((item = takeAt(0)))
        delete item;
}

void FlowLayout::addWidget(QWidget* widget) {
    addChildWidget(widget); // Ensures correct parenting
    addItem(new QWidgetItem(widget));
}

void FlowLayout::addStretch(int stretch) {
    Q_UNUSED(stretch);
    addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
}

void FlowLayout::insertWidget(int index, QWidget* widget) {
    if (index < 0 || index > itemList.size())
        index = itemList.size();
    addChildWidget(widget); // Ensures correct parenting
    itemList.insert(index, new QWidgetItem(widget));
}

void FlowLayout::addItem(QLayoutItem* item)
{
    itemList.append(item);
}

int FlowLayout::horizontalSpacing() const
{
    return m_hSpace >= 0 ? m_hSpace : smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int FlowLayout::verticalSpacing() const
{
    return m_vSpace >= 0 ? m_vSpace : smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem* FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem* FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    return nullptr;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return Qt::Horizontal;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0, 0, width, 0), true);
}

void FlowLayout::setGeometry(const QRect& rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (const QLayoutItem* item : qAsConst(itemList))
        size = size.expandedTo(item->minimumSize());

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

int FlowLayout::doLayout(const QRect& rect, bool testOnly) const {
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    QList<QLayoutItem*> currentLineItems;
    int currentLineWidth = 0;

    for (QLayoutItem* item : qAsConst(itemList)) {
        const QWidget* wid = item->widget();
        if (wid && !wid->isVisible())
            continue;

        int spaceX = horizontalSpacing();
        int nextX = x + item->sizeHint().width() + spaceX;

        // Check if item fits in current line or needs to wrap
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            // Distribute stretchable space in current line
            int remainingWidth = effectiveRect.right() - x + spaceX;
            if (remainingWidth > 0) {
                int stretchCount = 0;
                for (QLayoutItem* lineItem : currentLineItems) {
                    if (dynamic_cast<QSpacerItem*>(lineItem))
                        stretchCount++;
                }
                if (stretchCount > 0) {
                    int stretchSpace = remainingWidth / stretchCount;
                    int adjustedX = effectiveRect.x();
                    for (QLayoutItem* lineItem : currentLineItems) {
                        if (dynamic_cast<QSpacerItem*>(lineItem)) {
                            if (!testOnly)
                                lineItem->setGeometry(QRect(QPoint(adjustedX, y),
                                                            QSize(stretchSpace, lineHeight)));
                            adjustedX += stretchSpace + spaceX;
                        } else {
                            adjustedX += lineItem->sizeHint().width() + spaceX;
                        }
                    }
                }
            }

            // Reset for new line
            x = effectiveRect.x();
            y += lineHeight + verticalSpacing();
            lineHeight = 0;
            currentLineItems.clear();
            currentLineWidth = 0;
        }

        // Add item to current line
        currentLineItems.append(item);
        currentLineWidth += item->sizeHint().width() + spaceX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
        x += item->sizeHint().width() + spaceX;
    }

    // Position items in the last line
    if (!testOnly) {
        int adjustedX = effectiveRect.x();
        for (QLayoutItem* lineItem : currentLineItems) {
            lineItem->setGeometry(QRect(QPoint(adjustedX, y), lineItem->sizeHint()));
            adjustedX += lineItem->sizeHint().width() + horizontalSpacing();
        }
    }

    return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject* parent = this->parent();
    if (!parent)
        return -1;
    if (parent->isWidgetType()) {
        QWidget* pw = static_cast<QWidget*>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    }
    return static_cast<QLayout*>(parent)->spacing();
}
