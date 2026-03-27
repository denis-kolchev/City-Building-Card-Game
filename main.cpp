// #include "ui/cardview.h"
// #include "ui/democardstackwidget.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     CardView view;
//     view.resize(900, 400);
//     view.setOrthogonalLineCount(1);

//     const QString demoImages[] = {
//         QStringLiteral(":/images/cardWheatField.jpeg"),
//         QStringLiteral(":/images/cardBakery.jpeg"),
//         QStringLiteral(":/images/cardCafe.jpeg"),
//         QStringLiteral(":/images/cardForest.jpeg"),
//         QStringLiteral(":/images/cardShop.jpeg"),
//         QStringLiteral(":/images/cardStadium.jpeg"),
//     };

//     const int stackDepths[] = { 3, 2, 4, 1, 2, 3 };

//     for (int i = 0; i < 6; ++i) {
//         view.addWidget(new DemoCardStackWidget(
//             QStringLiteral("Card %1").arg(i),
//             demoImages[i],
//             stackDepths[i]));
//     }

//     view.setOrientation(Orientation::Horizontal);
//     view.setPopLiftDirection(PopLiftDirection::Up, PopLiftDirection::Right);

//     view.show();

//     return app.exec();
// }

#include "gameapplicationbuilder.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[]) {
    QApplication eventLoop(argc, argv);

    // Default: local 2-player game, no start menu, no network required.
    // Pass --start-menu to use the Offline / Create Server / Connect tabs (multiplayer over network).
    // Optional: --players N (2–5) when not using --start-menu.
    bool useStartMenu = false;
    int offlinePlayers = 2;
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (arg == QLatin1String("--start-menu")) {
            useStartMenu = true;
        } else if (arg == QLatin1String("--players") && i + 1 < argc) {
            offlinePlayers = QString::fromLocal8Bit(argv[++i]).toInt();
        }
    }

    GameApplicationBuilder builder;
    builder.withConfigReader()
        .withGameLogic()
        .withMainWindow()
        .withNetworkManager()
        .withOfflinePlayerCount(offlinePlayers);

    if (useStartMenu) {
        builder.withStartMenu();
    }

    auto gameApplication = builder.build();

    gameApplication->run();

    return eventLoop.exec();
}
