#include "gamesceneboardwidget.h"
#include "democardstackwidget.h"

#include <QGridLayout>
#include <QGraphicsProxyWidget>
#include <QResizeEvent>
#include <QShowEvent>
#include <QTimer>

namespace {

const QString demoImagePaths[] = {
    QStringLiteral(":/images/cardWheatField.jpeg"),
    QStringLiteral(":/images/cardBakery.jpeg"),
    QStringLiteral(":/images/cardCafe.jpeg"),
    QStringLiteral(":/images/cardForest.jpeg"),
    QStringLiteral(":/images/cardShop.jpeg"),
    QStringLiteral(":/images/cardStadium.jpeg"),
};

const int demoStackDepths[] = { 3, 2, 4, 1, 2, 3 };

} // namespace

GameSceneBoardWidget::GameSceneBoardWidget(int playerCount, QWidget *parent)
    : QWidget(parent)
    , m_playerCount(qBound(2, playerCount, 5))
{
    m_shopView = new CardView(this);
    m_playerViews.resize(m_playerCount);
    for (int i = 0; i < m_playerCount; ++i)
        m_playerViews[i] = new CardView(this);

    auto *grid = new QGridLayout(this);
    grid->setContentsMargins(8, 8, 8, 8);
    grid->setSpacing(8);

    const int P = m_playerCount;
    for (int c = 0; c < P; ++c)
        grid->addWidget(m_playerViews[c], 0, c);
    grid->addWidget(m_shopView, 1, 0, 1, P);

    grid->setRowStretch(0, 2);
    grid->setRowStretch(1, 1);

    for (int c = 0; c < P; ++c)
        grid->setColumnStretch(c, 1);

    fillDemoStacks();
    syncRegionsFromGeometry();
}

CardView *GameSceneBoardWidget::playerView(int index) const
{
    if (index < 0 || index >= m_playerViews.size())
        return nullptr;
    return m_playerViews[index];
}

void GameSceneBoardWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    syncRegionsFromGeometry();
    QTimer::singleShot(0, this, [this]() { syncRegionsFromGeometry(); });
}

void GameSceneBoardWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    syncRegionsFromGeometry();
}

void GameSceneBoardWidget::fillDemoStacks()
{
    constexpr int stacksPerRegion = 4;

    int seq = 0;
    for (int s = 0; s < stacksPerRegion; ++s) {
        const int k = seq++ % 6;
        auto *shopStack = new DemoCardStackWidget(
            QStringLiteral("Shop %1").arg(s + 1),
            demoImagePaths[k]);
        shopStack->setCardCount(demoStackDepths[k]);
        m_shopView->addWidget(shopStack);
    }

    for (int p = 0; p < m_playerCount; ++p) {
        for (int s = 0; s < stacksPerRegion; ++s) {
            const int k = seq++ % 6;
            auto *playerStack = new DemoCardStackWidget(
                QStringLiteral("P%1 · stack %2").arg(p + 1).arg(s + 1),
                demoImagePaths[k]);
            playerStack->setCardCount(demoStackDepths[k]);
            m_playerViews[p]->addWidget(playerStack);
        }
    }
}

void GameSceneBoardWidget::syncRegionsFromGeometry()
{
    updateRegionCardViewOrientations();
}

void GameSceneBoardWidget::updateRegionCardViewOrientations()
{
    auto orientAndStacks = [](CardView *v) {
        if (!v)
            return;
        QSize sz = v->size();
        if (sz.width() <= 0 || sz.height() <= 0) {
            if (QWidget *pw = v->parentWidget())
                sz = pw->size();
        }
        if (sz.width() <= 0 || sz.height() <= 0)
            return;

        const bool tallStrip = sz.height() > sz.width();
        const Orientation o = tallStrip ? Orientation::Vertical : Orientation::Horizontal;
        v->setOrientation(o);
        v->setOrthogonalLineCount(1);
        v->setPopLiftDirection(PopLiftDirection::Up, PopLiftDirection::Right);
        applyDemoStackDirectionsForCardView(v, o);
    };

    orientAndStacks(m_shopView);
    for (CardView *pv : m_playerViews)
        orientAndStacks(pv);
}

void GameSceneBoardWidget::applyDemoStackDirectionsForCardView(CardView *v, Orientation o)
{
    if (!v || !v->scene())
        return;

    const StackDirection pile = (o == Orientation::Vertical) ? StackDirection::HorizontalRight
                                                               : StackDirection::VerticalDown;

    const QList<QGraphicsItem *> items = v->scene()->items();
    for (QGraphicsItem *gi : items) {
        auto *proxy = dynamic_cast<QGraphicsProxyWidget *>(gi);
        if (!proxy)
            continue;
        if (auto *stack = dynamic_cast<DemoCardStackWidget *>(proxy->widget()))
            stack->setStackDirection(pile);
    }

    v->relayoutNow();
}
