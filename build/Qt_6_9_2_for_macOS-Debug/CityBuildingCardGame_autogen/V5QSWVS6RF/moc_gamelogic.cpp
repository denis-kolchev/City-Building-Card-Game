/****************************************************************************
** Meta object code from reading C++ file 'gamelogic.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
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
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
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

template <> constexpr inline auto GameLogic::qt_create_metaobjectdata<qt_meta_tag_ZN9GameLogicE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GameLogic",
        "gameWon",
        "",
        "playerId",
        "requestCardData",
        "CardId",
        "startCardId",
        "finishCardId",
        "std::shared_ptr<CardDataHandler>",
        "handler",
        "requestDiceRerollConfirmation",
        "QList<int>",
        "rools",
        "sendBankGetsCard",
        "std::shared_ptr<Card>",
        "card",
        "sendBankLoosesCard",
        "sendCardPurchaseFailed",
        "cardId",
        "message",
        "sendDiceRollResult",
        "rolls",
        "sendPlayerBalanceChanged",
        "balance",
        "sendPlayerGetsCard",
        "sendPlayerLoosesCard",
        "sendRollTwoDiceAvailable",
        "switchToPlayerTurn",
        "finishIncomeState",
        "finishPurchaseState",
        "finishWaitState",
        "handleCardClickedForPurchase",
        "handleConfigDataReadyToRead",
        "handleCreatePlayers",
        "playerCount",
        "handleRollDiceButtonClicked",
        "diceRollCount",
        "handleSkipButtonClicked",
        "receiveDiceRerollResponse",
        "rollResults",
        "confirmed"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'gameWon'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'requestCardData'
        QtMocHelpers::SignalData<void(CardId, CardId, std::shared_ptr<CardDataHandler>)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { 0x80000000 | 5, 7 }, { 0x80000000 | 8, 9 },
        }}),
        // Signal 'requestDiceRerollConfirmation'
        QtMocHelpers::SignalData<void(int, QVector<int>)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 11, 12 },
        }}),
        // Signal 'sendBankGetsCard'
        QtMocHelpers::SignalData<void(std::shared_ptr<Card>)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'sendBankLoosesCard'
        QtMocHelpers::SignalData<void(std::shared_ptr<Card>)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'sendCardPurchaseFailed'
        QtMocHelpers::SignalData<void(int, CardId, QString)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 5, 18 }, { QMetaType::QString, 19 },
        }}),
        // Signal 'sendDiceRollResult'
        QtMocHelpers::SignalData<void(int, QVector<int>)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 11, 21 },
        }}),
        // Signal 'sendPlayerBalanceChanged'
        QtMocHelpers::SignalData<void(int, int)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 23 },
        }}),
        // Signal 'sendPlayerGetsCard'
        QtMocHelpers::SignalData<void(int, std::shared_ptr<Card>)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 14, 15 },
        }}),
        // Signal 'sendPlayerLoosesCard'
        QtMocHelpers::SignalData<void(int, std::shared_ptr<Card>)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 14, 15 },
        }}),
        // Signal 'sendRollTwoDiceAvailable'
        QtMocHelpers::SignalData<void(int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'switchToPlayerTurn'
        QtMocHelpers::SignalData<void(int)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'finishIncomeState'
        QtMocHelpers::SignalData<void(int)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'finishPurchaseState'
        QtMocHelpers::SignalData<void(int)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'finishWaitState'
        QtMocHelpers::SignalData<void(int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'handleCardClickedForPurchase'
        QtMocHelpers::SlotData<void(CardId)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 18 },
        }}),
        // Slot 'handleConfigDataReadyToRead'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleCreatePlayers'
        QtMocHelpers::SlotData<void(int)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'handleRollDiceButtonClicked'
        QtMocHelpers::SlotData<void(int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 36 },
        }}),
        // Slot 'handleSkipButtonClicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'receiveDiceRerollResponse'
        QtMocHelpers::SlotData<void(QVector<int>, bool)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 39 }, { QMetaType::Bool, 40 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GameLogic, qt_meta_tag_ZN9GameLogicE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GameLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9GameLogicE_t>.metaTypes,
    nullptr
} };

void GameLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameLogic *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->gameWon((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->requestCardData((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CardId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<CardDataHandler>>>(_a[3]))); break;
        case 2: _t->requestDiceRerollConfirmation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[2]))); break;
        case 3: _t->sendBankGetsCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 4: _t->sendBankLoosesCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 5: _t->sendCardPurchaseFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CardId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 6: _t->sendDiceRollResult((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[2]))); break;
        case 7: _t->sendPlayerBalanceChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->sendPlayerGetsCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 9: _t->sendPlayerLoosesCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 10: _t->sendRollTwoDiceAvailable((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->switchToPlayerTurn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->finishIncomeState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->finishPurchaseState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->finishWaitState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->handleCardClickedForPurchase((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1]))); break;
        case 16: _t->handleConfigDataReadyToRead(); break;
        case 17: _t->handleCreatePlayers((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->handleRollDiceButtonClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->handleSkipButtonClicked(); break;
        case 20: _t->receiveDiceRerollResponse((*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::gameWon, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(CardId , CardId , std::shared_ptr<CardDataHandler> )>(_a, &GameLogic::requestCardData, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , QVector<int> )>(_a, &GameLogic::requestDiceRerollConfirmation, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(std::shared_ptr<Card> )>(_a, &GameLogic::sendBankGetsCard, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(std::shared_ptr<Card> )>(_a, &GameLogic::sendBankLoosesCard, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , CardId , QString )>(_a, &GameLogic::sendCardPurchaseFailed, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , QVector<int> )>(_a, &GameLogic::sendDiceRollResult, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , int )>(_a, &GameLogic::sendPlayerBalanceChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , std::shared_ptr<Card> )>(_a, &GameLogic::sendPlayerGetsCard, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int , std::shared_ptr<Card> )>(_a, &GameLogic::sendPlayerLoosesCard, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::sendRollTwoDiceAvailable, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::switchToPlayerTurn, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::finishIncomeState, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::finishPurchaseState, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameLogic::*)(int )>(_a, &GameLogic::finishWaitState, 14))
            return;
    }
}

const QMetaObject *GameLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9GameLogicE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void GameLogic::gameWon(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void GameLogic::requestCardData(CardId _t1, CardId _t2, std::shared_ptr<CardDataHandler> _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void GameLogic::requestDiceRerollConfirmation(int _t1, QVector<int> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void GameLogic::sendBankGetsCard(std::shared_ptr<Card> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void GameLogic::sendBankLoosesCard(std::shared_ptr<Card> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void GameLogic::sendCardPurchaseFailed(int _t1, CardId _t2, QString _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2, _t3);
}

// SIGNAL 6
void GameLogic::sendDiceRollResult(int _t1, QVector<int> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void GameLogic::sendPlayerBalanceChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void GameLogic::sendPlayerGetsCard(int _t1, std::shared_ptr<Card> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void GameLogic::sendPlayerLoosesCard(int _t1, std::shared_ptr<Card> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2);
}

// SIGNAL 10
void GameLogic::sendRollTwoDiceAvailable(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void GameLogic::switchToPlayerTurn(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void GameLogic::finishIncomeState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void GameLogic::finishPurchaseState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void GameLogic::finishWaitState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}
QT_WARNING_POP
