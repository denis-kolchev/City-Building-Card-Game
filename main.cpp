#include "gameapplicationbuilder.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication eventLoop(argc, argv);

    //  Factory/Builder Pattern
    auto gameApplication = GameApplicationBuilder()
                               .withConfigReader()
                               .withGameLogic()
                               .withMainWindow()
                               .withNetworkManager()
                               .withStartMenu()
                               .build();

    gameApplication->run();

    return eventLoop.exec();
}
