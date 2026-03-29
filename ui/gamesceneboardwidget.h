#ifndef GAMESCENEBOARDWIDGET_H
#define GAMESCENEBOARDWIDGET_H

#include "cardview.h"

#include <QVector>
#include <QWidget>

/**
 * Board UI prototype: grid of CardView regions (players + shop) with demo stacks.
 * Chooses CardView flow and DemoCardStackWidget pile direction from each cell’s aspect ratio.
 */
class GameSceneBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameSceneBoardWidget(int playerCount, QWidget *parent = nullptr);

    int playerCount() const { return m_playerCount; }

    CardView *shopView() const { return m_shopView; }

    /** Zero-based index in [0, playerCount). */
    CardView *playerView(int index) const;

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupGrid();
    void fillDemoStacks();
    void syncRegionsFromGeometry();

    void updateRegionCardViewOrientations();
    static void applyDemoStackDirectionsForCardView(CardView *v, Orientation o);

    int m_playerCount = 2;
    CardView *m_shopView = nullptr;
    QVector<CardView *> m_playerViews;
};

#endif // GAMESCENEBOARDWIDGET_H
