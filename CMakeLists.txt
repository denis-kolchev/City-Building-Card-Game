cmake_minimum_required(VERSION 3.16)

project(CityBuildingCardGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(QT_VERSION_MAJOR EQUAL 6)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS StateMachine)
else()
    find_package(Qt5 REQUIRED COMPONENTS StateMachine) # Ensure Qt5 compatibility
endif()

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CityBuildingCardGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        logic/cards/cafe.h logic/cards/cafe.cpp
        logic/cards/card.h logic/cards/card.cpp
        logic/cards/wheatfield.h logic/cards/wheatfield.cpp
        logic/cards/bakery.h logic/cards/bakery.cpp
        logic/cards/shoppingmall.h logic/cards/shoppingmall.cpp
        logic/cards/railwaystation.h logic/cards/railwaystation.cpp
        logic/cards/amusementpark.h logic/cards/amusementpark.cpp
        logic/cards/radiotower.h logic/cards/radiotower.cpp
        logic/cards/animalfarm.h logic/cards/animalfarm.cpp
        logic/cards/shop.h logic/cards/shop.cpp
        logic/cards/forest.h logic/cards/forest.cpp
        logic/cards/stadium.h logic/cards/stadium.cpp
        logic/cards/businesscenter.h logic/cards/businesscenter.cpp
        logic/cards/tvcenter.h logic/cards/tvcenter.cpp
        logic/cards/cheesefactory.h logic/cards/cheesefactory.cpp
        logic/cards/furniturefactory.h logic/cards/furniturefactory.cpp
        logic/cards/mine.h logic/cards/mine.cpp
        logic/cards/restaurant.h logic/cards/restaurant.cpp
        logic/cards/appleorchard.h logic/cards/appleorchard.cpp
        logic/cards/fruitmarket.h logic/cards/fruitmarket.cpp

        logic/carddatahandler.h logic/carddatahandler.cpp
        logic/diceroller.h logic/diceroller.cpp
        logic/cardinventory.h logic/cardinventory.cpp
        logic/gamelogic.h logic/gamelogic.cpp
        logic/player.h logic/player.cpp

        ui/cardscrollwidget.h ui/cardscrollwidget.cpp
        ui/cardstackwidget.h ui/cardstackwidget.cpp
        ui/cardwidget.h ui/cardwidget.cpp
        ui/mainwindow.h ui/mainwindow.cpp
        ui/playerpage.h ui/playerpage.cpp
        ui/startmenu.h ui/startmenu.cpp

        carddataconfigreader.h carddataconfigreader.cpp
        cardfactory.h cardfactory.cpp
        gameapplication.h gameapplication.cpp
        gameapplicationbuilder.h gameapplicationbuilder.cpp

        cardImages.qrc
        gameSounds.qrc

        README.md
        logic/bank.h logic/bank.cpp
        logic/icardcontainer.h
        logic/icardcontainer.h
        logic/carddatahandler.h
        logic/bankcardshandler.h logic/bankcardshandler.cpp
        logic/initialplayercardshandler.h logic/initialplayercardshandler.cpp
        logic/carddatahandler.h
        ui/flowlayout.h ui/flowlayout.cpp


        network/networkmanager.h network/networkmanager.cpp
        network/server.h network/server.cpp
        network/client.h network/client.cpp
        network/jsonmessagefactory.h network/jsonmessagefactory.cpp
        network/jsons/abstractjsonstrategy.h
        network/jsons/jsongameinit.h network/jsons/jsongameinit.cpp
        network/jsons/jsongameover.h network/jsons/jsongameover.cpp
        network/jsons/jsondicerollresult.h network/jsons/jsondicerollresult.cpp
    )

    # Make CardsDataConfig.ini visible in IDEs under "Configuration Files"
    source_group("Configuration Files" FILES ${CMAKE_CURRENT_SOURCE_DIR}/CardsDataConfig.ini)

    # Copy INI file to build directory on every build
    add_custom_command(TARGET CityBuildingCardGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/CardsDataConfig.ini
            $<TARGET_FILE_DIR:CityBuildingCardGame>
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CityBuildingCardGame APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CityBuildingCardGame SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CityBuildingCardGame
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CityBuildingCardGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CityBuildingCardGame PRIVATE Qt${QT_VERSION_MAJOR}::StateMachine)
target_link_libraries(CityBuildingCardGame PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)

# To install CardsDataConfig.ini together with app (optional for deployment)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/CardsDataConfig.ini DESTINATION ${CMAKE_INSTALL_BINDIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CityBuildingCardGame)
endif()
set_target_properties(CityBuildingCardGame PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CityBuildingCardGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CityBuildingCardGame)
endif()
