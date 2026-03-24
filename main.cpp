#include "gameapplicationbuilder.h"

#include "ui/gameconfig.h"
#include "ui/gamemainwindow.h"
#include <QApplication>

QJsonDocument example()
{
    QJsonArray playersArray;
    playersArray.append("Mark");
    playersArray.append("Lena");

    QJsonObject jsonObject;
    jsonObject["players"] = playersArray;
    jsonObject["playersCount"] = 2;

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}


int main(int argc, char *argv[]) {
    QApplication eventLoop(argc, argv);

    //  Factory/Builder Pattern
    // auto gameApplication = GameApplicationBuilder()
    //                            .withConfigReader()
    //                            .withGameLogic()
    //                            .withMainWindow()
    //                            .withNetworkManager()
    //                            .withStartMenu()
    //                            .build();

    // gameApplication->run();

    QJsonDocument document = example();
    GameConfig config(document);
    GameMainWindow window(&config);
    window.show();

    return eventLoop.exec();
}
