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
    "bankGetsCard",
    "std::shared_ptr<Card>",
    "card",
    "bankLoosesCard",
    "playerGetsCard",
    "playerLoosesCard",
    "playerHasAmusementPark",
    "playerHasNotEnoughCoins",
    "message",
    "playerHasRadioTower",
    "playerHasRailwayStation",
    "playerBalanceChanged",
    "balance",
    "playerBuildLandmark",
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
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  194,    2, 0x06,    1 /* Public */,
       4,    1,  197,    2, 0x06,    3 /* Public */,
       6,    2,  200,    2, 0x06,    5 /* Public */,
       9,    1,  205,    2, 0x06,    8 /* Public */,
      12,    1,  208,    2, 0x06,   10 /* Public */,
      13,    2,  211,    2, 0x06,   12 /* Public */,
      14,    2,  216,    2, 0x06,   15 /* Public */,
      15,    0,  221,    2, 0x06,   18 /* Public */,
      16,    1,  222,    2, 0x06,   19 /* Public */,
      18,    0,  225,    2, 0x06,   21 /* Public */,
      19,    0,  226,    2, 0x06,   22 /* Public */,
      20,    2,  227,    2, 0x06,   23 /* Public */,
      22,    1,  232,    2, 0x06,   26 /* Public */,
      23,    1,  235,    2, 0x06,   28 /* Public */,
      24,    3,  238,    2, 0x06,   30 /* Public */,
      29,    2,  245,    2, 0x06,   34 /* Public */,
      30,    2,  250,    2, 0x06,   37 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      33,    1,  255,    2, 0x0a,   40 /* Public */,
      34,    4,  258,    2, 0x0a,   42 /* Public */,
      35,    1,  267,    2, 0x0a,   47 /* Public */,
      36,    1,  270,    2, 0x0a,   49 /* Public */,
      39,    0,  273,    2, 0x0a,   51 /* Public */,
      40,    1,  274,    2, 0x0a,   52 /* Public */,
      42,    0,  277,    2, 0x0a,   54 /* Public */,
      43,    0,  278,    2, 0x0a,   55 /* Public */,
      44,    0,  279,    2, 0x0a,   56 /* Public */,
      45,    2,  280,    2, 0x0a,   57 /* Public */,
      46,    1,  285,    2, 0x0a,   60 /* Public */,
      47,    0,  288,    2, 0x0a,   62 /* Public */,
      48,    0,  289,    2, 0x0a,   63 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    5,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    5,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   21,    5,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 27,   25,   26,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,   26,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   31,   32,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,   31,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::UChar, QMetaType::UChar,   31,    5,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 37,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    7,    8,
    QMetaType::Void, QMetaType::UChar,   31,
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
        // method 'bankGetsCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'bankLoosesCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'playerGetsCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'playerLoosesCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
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
        case 3: _t->bankGetsCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 4: _t->bankLoosesCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 5: _t->playerGetsCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 6: _t->playerLoosesCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 7: _t->playerHasAmusementPark(); break;
        case 8: _t->playerHasNotEnoughCoins((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->playerHasRadioTower(); break;
        case 10: _t->playerHasRailwayStation(); break;
        case 11: _t->playerBalanceChanged((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 12: _t->playerBuildLandmark((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 13: _t->playerBuildNewBuilding((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 14: _t->requestCardData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<CardDataHandler>>>(_a[3]))); break;
        case 15: _t->requestReadFromRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 16: _t->tryToBuyCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 17: _t->checkCoinBalanceForCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 18: _t->processCheckPlayerCards((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[4]))); break;
        case 19: _t->giveCardToPlayer((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 20: _t->handleCardDataReceived((*reinterpret_cast< std::add_pointer_t<QList<std::shared_ptr<Card>>>>(_a[1]))); break;
        case 21: _t->handleConfigDataReady(); break;
        case 22: _t->handleCreatePlayers((*reinterpret_cast< std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 23: _t->handlePlayerHasAmusementPark(); break;
        case 24: _t->handlePlayerHasRadioTower(); break;
        case 25: _t->handlePlayerHasRailwayStation(); break;
        case 26: _t->handleRollButtonClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 27: _t->handleTryToBuyCard((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 28: _t->moveToNextPlaer(); break;
        case 29: _t->prepateNextTurn(); break;
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
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::bankGetsCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::bankLoosesCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerGetsCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerLoosesCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasAmusementPark; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(QString );
            if (_q_method_type _q_method = &GameLogic::playerHasNotEnoughCoins; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasRadioTower; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)();
            if (_q_method_type _q_method = &GameLogic::playerHasRailwayStation; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(uchar , int );
            if (_q_method_type _q_method = &GameLogic::playerBalanceChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerBuildLandmark; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(std::shared_ptr<Card> );
            if (_q_method_type _q_method = &GameLogic::playerBuildNewBuilding; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , int , std::shared_ptr<CardDataHandler> );
            if (_q_method_type _q_method = &GameLogic::requestCardData; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(int , int );
            if (_q_method_type _q_method = &GameLogic::requestReadFromRange; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _q_method_type = void (GameLogic::*)(uchar , uchar );
            if (_q_method_type _q_method = &GameLogic::tryToBuyCard; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 16;
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
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
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
void GameLogic::bankGetsCard(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameLogic::bankLoosesCard(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GameLogic::playerGetsCard(int _t1, std::shared_ptr<Card> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GameLogic::playerLoosesCard(int _t1, std::shared_ptr<Card> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GameLogic::playerHasAmusementPark()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GameLogic::playerHasNotEnoughCoins(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GameLogic::playerHasRadioTower()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void GameLogic::playerHasRailwayStation()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void GameLogic::playerBalanceChanged(uchar _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GameLogic::playerBuildLandmark(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void GameLogic::playerBuildNewBuilding(std::shared_ptr<Card> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void GameLogic::requestCardData(int _t1, int _t2, std::shared_ptr<CardDataHandler> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void GameLogic::requestReadFromRange(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void GameLogic::tryToBuyCard(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
