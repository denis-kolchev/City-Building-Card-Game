#include "gameapplicationbuilder.h"
#include "ui/cardview.h"
#include "ui/democardstackwidget.h"
#include "ui/gamesceneboardwidget.h"

#include <QApplication>
#include <QString>

namespace {

enum class LaunchTarget {
    CardViewDemo,
    BoardPrototype,
    FullGame,
};

/**
 * Which executable “project” runs when you start the app without --launch.
 * Override at runtime: --launch demo | board | game
 */
static constexpr LaunchTarget kLaunchTarget = LaunchTarget::FullGame;

LaunchTarget launchTargetFromString(const QString &s)
{
    const QString lower = s.toLower();
    if (lower == QLatin1String("demo") || lower == QLatin1String("cardview"))
        return LaunchTarget::CardViewDemo;
    if (lower == QLatin1String("board") || lower == QLatin1String("prototype"))
        return LaunchTarget::BoardPrototype;
    if (lower == QLatin1String("game") || lower == QLatin1String("full"))
        return LaunchTarget::FullGame;
    return kLaunchTarget;
}

/** Consumes known demo flags from argv; returns target (CLI overrides constexpr default). */
LaunchTarget parseLaunchTarget(int argc, char **argv, int &outOfflinePlayers, bool &outUseStartMenu)
{
    LaunchTarget target = kLaunchTarget;
    outOfflinePlayers = 2;
    outUseStartMenu = false;

    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (arg == QLatin1String("--launch") && i + 1 < argc) {
            target = launchTargetFromString(QString::fromLocal8Bit(argv[++i]));
        } else if (arg == QLatin1String("--start-menu")) {
            outUseStartMenu = true;
        } else if (arg == QLatin1String("--players") && i + 1 < argc) {
            outOfflinePlayers = QString::fromLocal8Bit(argv[++i]).toInt();
        }
    }
    return target;
}

int runCardViewDemo(QApplication &app)
{
    CardView view;
    view.resize(900, 400);
    view.setOrthogonalLineCount(2);

    const QString demoImages[] = {
        QStringLiteral(":/images/cardWheatField.jpeg"),
        QStringLiteral(":/images/cardBakery.jpeg"),
        QStringLiteral(":/images/cardCafe.jpeg"),
        QStringLiteral(":/images/cardForest.jpeg"),
        QStringLiteral(":/images/cardShop.jpeg"),
        QStringLiteral(":/images/cardStadium.jpeg"),
    };

    const int stackDepths[] = { 3, 2, 4, 1, 2, 3 };

    const StackDirection pileDirs[] = {
        StackDirection::VerticalDown,
        StackDirection::VerticalUp,
        StackDirection::HorizontalRight,
        StackDirection::VerticalDown,
        StackDirection::HorizontalLeft,
        StackDirection::HorizontalRight,
    };

    for (int i = 0; i < 6; ++i) {
        auto *pile = new DemoCardStackWidget(
            QStringLiteral("Card %1").arg(i),
            demoImages[i]);
        pile->setCardCount(stackDepths[i]);
        pile->setStackDirection(pileDirs[i]);
        view.addWidget(pile);
    }

    view.setOrientation(Orientation::Horizontal);
    view.setPopLiftDirection(PopLiftDirection::Up, PopLiftDirection::Right);

    view.setWindowTitle(QStringLiteral("CardView demo"));
    view.show();
    return app.exec();
}

int runBoardPrototype(QApplication &app, int argc, char **argv)
{
    int players = 3;
    for (int i = 1; i < argc; ++i) {
        if (QString::fromLocal8Bit(argv[i]) == QLatin1String("--players") && i + 1 < argc) {
            players = QString::fromLocal8Bit(argv[++i]).toInt();
            break;
        }
    }
    players = qBound(2, players, 5);

    GameSceneBoardWidget board(players);
    board.resize(1024, 768);
    board.setWindowTitle(QStringLiteral("Board prototype (%1 players)").arg(players));
    board.show();
    return app.exec();
}

int runFullGame(QApplication &app, int offlinePlayers, bool useStartMenu)
{
    GameApplicationBuilder builder;
    builder.withConfigReader()
        .withGameLogic()
        .withMainWindow()
        .withNetworkManager()
        .withOfflinePlayerCount(offlinePlayers);

    if (useStartMenu)
        builder.withStartMenu();

    auto gameApplication = builder.build();
    gameApplication->run();
    return app.exec();
}

} // namespace

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int offlinePlayers = 4;
    bool useStartMenu = false;
    const LaunchTarget target = LaunchTarget::FullGame;

    switch (target) {
    case LaunchTarget::CardViewDemo:
        return runCardViewDemo(app);
    case LaunchTarget::BoardPrototype:
        return runBoardPrototype(app, argc, argv);
    case LaunchTarget::FullGame:
    default:
        return runFullGame(app, offlinePlayers, useStartMenu);
    }
}
