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
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 5)
    qt_add_executable(CityBuildingCardGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        diceroller.h diceroller.cpp
        gamelogic.h gamelogic.cpp
        player.h player.cpp
        cardreserve.h cardreserve.cpp

        README.md

        cards/cafe.h cards/cafe.cpp
        cards/card.h cards/card.cpp
        cards/wheatfield.h cards/wheatfield.cpp
        cards/bakery.h cards/bakery.cpp
        cards/shoppingmall.h cards/shoppingmall.cpp
        cardImages.qrc
        cardwidget.h cardwidget.cpp
        gamecontroller.h gamecontroller.cpp
        cardfactory.h cardfactory.cpp
        carddataconfigreader.h carddataconfigreader.cpp
        cards/railwaystation.h cards/railwaystation.cpp
        cards/amusementpark.h cards/amusementpark.cpp
        cards/radiotower.h cards/radiotower.cpp
        cards/animalfarm.h cards/animalfarm.cpp
        cards/shop.h cards/shop.cpp
        cards/forest.h cards/forest.cpp
        cards/stadium.h cards/stadium.cpp
        cards/businesscenter.h cards/businesscenter.cpp
        cards/tvcenter.h cards/tvcenter.cpp
        cards/cheesefactory.h cards/cheesefactory.cpp
        cards/furniturefactory.h cards/furniturefactory.cpp
        cards/mine.h cards/mine.cpp
        cards/restaurant.h cards/restaurant.cpp
        cards/appleorchard.h cards/appleorchard.cpp
        cards/fruitmarket.h cards/fruitmarket.cpp
        startmenu.h startmenu.cpp
        cardstackwidget.h cardstackwidget.cpp
        gameSounds.qrc
        playerpage.h playerpage.cpp
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

if(QT_VERSION_MAJOR EQUAL 5)
    qt_finalize_executable(CityBuildingCardGame)
endif()
