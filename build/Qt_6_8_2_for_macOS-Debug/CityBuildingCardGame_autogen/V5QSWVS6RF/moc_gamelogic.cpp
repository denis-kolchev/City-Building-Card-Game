/****************************************************************************
** Meta object code from reading C++ file 'gamelogic.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../logic/gamelogic.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamelogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN9GameLogicE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN9GameLogicE = QtMocHelpers::stringData(
    "GameLogic",
    "buildStageFinished",
    "",
    "currentPlayerId",
    "gameIsFinished",
    "playerId",
    "playerCardActivatedBefore",
    "dice1",
    "dice2",
    "playerHasAmusementPark",
    "playerHasNotEnoughCoins",
    "message",
    "playerHasRadioTower",
    "playerHasRailwayStation",
    "playerBalanceChanged",
    "balance",
    "playerBuildLandmark",
    "std::shared_ptr<Card>",
    "card",
    "playerBuildNewBuilding",
    "requestCardData",
    "begin",
    "end",
    "std::shared_ptr<CardDataHandler>",
    "handler",
    "requestReadFromRange",
    "tryToBuyCard",
    "cardId",
    "playerBalance",
    "checkCoinBalanceForCard",
    "processCheckPlayerCards",
    "giveCardToPlayer",
    "handleCardDataReceived",
    "QList<std::shared_ptr<Card>>",
    "data",
    "handleConfigDataReady",
    "handleCreatePlayers",
    "playerNames",
    "handlePlayerHasAmusementPark",
    "handlePlayerHasRadioTower",
    "handlePlayerHasRailwayStation",
    "handleRollButtonClicked",
    "handleTryToBuyCard",
    "moveToNextPlaer",
    "prepateNextTurn"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN9GameLogicE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  170,    2, 0x06,    1 /* Public */,
       4,    1,  173,    2, 0x06,    3 /* Public */,
       6,    2,  176,    2, 0x06,    5 /* Public */,
       9,    0,  181,    2, 0x06,    8 /* Public */,
      10,    1,  182,    2, 0x06,    9 /* Public */,
      12,    0,  185,    2, 0x06,   11 /* Public */,
      13,    0,  186,    2, 0x06,   12 /* Public */,
      14,    2,  187,    2, 0x06,   13 /* Public */,
      16,    1,  192,    2, 0x06,   16 /* Public */,
      19,    1,  195,    2, 0x06,   18 /* Public */,
      20,    3,  198,    2, 0x06,   20 /* Public */,
      25,    2,  205,    2, 0x06,   24 /* Public */,
      26,    2,  210,    2, 0x06,   27 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      29,    1,  215,    2, 0x0a,   30 /* Public */,
      30,    4,  218,    2, 0x0a,   32 /* Public */,
      31,    1,  227,    2, 0x0a,   37 /* Public */,
      32,    1,  230,    2, 0x0a,   39 /* Public */,
      35,    0,  233,    2, 0x0a,   41 /* Public */,
      36,    1,  234,    2, 0x0a,   42 /* Public */,
      38,    0,  237,    2, 0x0a,   44 /* Public */,
      39,    0,  238,    2, 0x0a,   45 /* Public */,
      40,    0,  239,    2, 0x0a,   46 /* Public */,
      41,    2,  240,    2, 0x0a,   47 /* Public */,
      42,    1,  245,    2, 0x0a,   50 /* Public */,
      43,    0,  248,    2, 0x0a,   52 /* Public */,
      44,    0,  249,    2, 0x0a,   53 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   15,    5,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 23,   21,   22,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   22,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   27,   28,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,   27,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::UChar, QMetaType::UChar,   27,    5,    7,    8,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    7,    8,
    QMetaType::Void, QMetaType::UChar,   27,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN9GameLogicE.offsetsAndSizes,
    qt_meta_data_ZN9GameLogicE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN9GameLogicE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameLogic, std::true_type>,
        // method 'buildStageFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'gameIsFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'playerCardActivatedBefore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'playerHasAmusementPark'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playerHasNotEnoughCoins'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'playerHasRadioTower'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playerHasRailwayStation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playerBalanceChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'playerBuildLandmark'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'playerBuildNewBuilding'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'requestCardData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<CardDataHandler>, std::false_type>,
        // method 'requestReadFromRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'tryToBuyCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'checkCoinBalanceForCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'processCheckPlayerCards'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'giveCardToPlayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'handleCardDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<std::shared_ptr<Card>>, std::false_type>,
        // method 'handleConfigDataReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleCreatePlayers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<QString>, std::false_type>,
        // method 'handlePlayerHasAmusementPark'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handlePlayerHasRadioTower'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handlePlayerHasRailwayStation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleRollButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'handleTryToBuyCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'moveToNextPlaer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prepateNextTurn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameLogic *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->buildStageFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->gameIsFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->playerCardActivatedBefore((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 3: _t->playerHasAmusementPark(); break;
        case 4: _t->playerHasNotEnoughCoins((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->playerHasRadioTower(); break;
        case 6: _t->playerHasRailwayStation(); break;
        case 7: _t->playerBalanceChanged((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->playerBuildLandmark((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 9: _t->playerBuildNewBuilding((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 10: _t->requestCardData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<CardDataHandler>>>(_a[3]))); break;
        case 11: _t->requestReadFromRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 12: _t->tryToBuyCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 13: _t->checkCoinBalanceForCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 14: _t->processCheckPlayerCards((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[4]))); break;
        case 15: _t->giveCardToPlayer((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 16: _t->handleCardDataReceived((*reinterpret_cast< std::add_pointer_t<QList<std::shared_ptr<Card>>>>(_a[1]))); break;
        case 17: _t->handleConfigDataReady(); break;
        case 18: _t->handleCreatePlayers((*reinterpret_cast< std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 19: _t->handlePlayerHasAmusementPark(); break;
        case 20: _t->handlePlayerHasRadioTower(); break;
        case 21: _t->handlePlayerHasRailwayStation(); break;
        case 22: _t->handleRollButtonClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 23: _t->handleTryToBuyCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 24: _t->moveToNextPlaer(); break;
        case 25: _t->prepateNextTurn(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (GameLogic::*)(int );
            if (_q_method_type _q_method = &GameLogic::buildStageFinished; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int );
            if (_q_method_type _q_method = &GameLogic::gameIsFinished; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(uchar , uchar );
            if (_q_method_type _q_method = &GameLogic::playerCardActivatedBefore; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasAmusementPark; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(QString );
            if (_q_method_type _q_method = &GameLogic::playerHasNotEnoughCoins; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasRadioTower; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasRailwayStation; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(uchar , int );
            if (_q_method_type _q_method = &GameLogic::playerBalanceChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerBuildLandmark; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerBuildNewBuilding; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , int , std::shared_ptr<CardDataHandler> );
            if (_q_method_type _q_method = &GameLogic::requestCardData; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , int );
            if (_q_method_type _q_method = &GameLogic::requestReadFromRange; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(uchar , uchar );
            if (_q_method_type _q_method = &GameLogic::tryToBuyCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
    }
}

const QMetaObject *GameLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN9GameLogicE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void GameLogic::buildStageFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameLogic::gameIsFinished(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameLogic::playerCardActivatedBefore(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameLogic::playerHasAmusementPark()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GameLogic::playerHasNotEnoughCoins(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GameLogic::playerHasRadioTower()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GameLogic::playerHasRailwayStation()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GameLogic::playerBalanceChanged(uchar _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GameLogic::playerBuildLandmark(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GameLogic::playerBuildNewBuilding(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GameLogic::requestCardData(int _t1, int _t2, std::shared_ptr<CardDataHandler> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GameLogic::requestReadFromRange(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GameLogic::tryToBuyCard(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
