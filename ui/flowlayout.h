#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget* parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);

    explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);

    ~FlowLayout();

    void addItem(QLayoutItem* item) override;

    void addWidget(QWidget* widget);

    void addStretch(int stretch = 0);

    void insertWidget(int index, QWidget* widget);

    int horizontalSpacing() const;

    int verticalSpacing() const;

    Qt::Orientations expandingDirections() const override;

    bool hasHeightForWidth() const override;

    int heightForWidth(int) const override;

    int count() const override;

    QLayoutItem* itemAt(int index) const override;

    QSize minimumSize() const override;

    void setGeometry(const QRect& rect) override;

    QSize sizeHint() const override;

    QLayoutItem* takeAt(int index) override;

private:
    int doLayout(const QRect& rect, bool testOnly) const;

    int smartSpacing(QStyle::PixelMetric pm) const;

private:
    QList<QLayoutItem*> itemList;
    int m_hSpace;
    int m_vSpace;
};

#endif // FLOWLAYOUT_H
