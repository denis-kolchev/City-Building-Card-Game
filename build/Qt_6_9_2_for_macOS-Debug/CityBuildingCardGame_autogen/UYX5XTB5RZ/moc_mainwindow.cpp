/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ui/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "cardClickedForPurchase",
        "",
        "CardId",
        "cardId",
        "createPlayers",
        "playerCount",
        "rollDiceButtonClicked",
        "diceRollCount",
        "sendDiceRerollResponse",
        "QList<int>",
        "rollResults",
        "confirmed",
        "skipButtonClicked",
        "setIncomeState",
        "playerId",
        "setPurchaseState",
        "setWaitState",
        "handleFinishIncomeState",
        "handleFinishPurchaseState",
        "handleFinishWaitState",
        "handleGameWon",
        "handleRequestDiceRerollConfirmation",
        "rools",
        "handleShowMainWindow",
        "playersCount",
        "handleSwitchToPlayerTurn",
        "receiveBankLoosesCard",
        "std::shared_ptr<Card>",
        "card",
        "receiveBankGetsCard",
        "receiveCardPurchaseFailed",
        "message",
        "receiveDiceRollResult",
        "rolls",
        "receivePlayerBalanceChanged",
        "balance",
        "receivePlayerGetsCard",
        "receivePlayerLoosesCard",
        "receiveRollTwoDiceAvailable",
        "handleCardClick",
        "id"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'cardClickedForPurchase'
        QtMocHelpers::SignalData<void(CardId)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'createPlayers'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'rollDiceButtonClicked'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Signal 'sendDiceRerollResponse'
        QtMocHelpers::SignalData<void(QVector<int>, bool)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 }, { QMetaType::Bool, 12 },
        }}),
        // Signal 'skipButtonClicked'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'setIncomeState'
        QtMocHelpers::SignalData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Signal 'setPurchaseState'
        QtMocHelpers::SignalData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Signal 'setWaitState'
        QtMocHelpers::SignalData<void(int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleFinishIncomeState'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleFinishPurchaseState'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleFinishWaitState'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleGameWon'
        QtMocHelpers::SlotData<void(int)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleRequestDiceRerollConfirmation'
        QtMocHelpers::SlotData<void(int, QVector<int>)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 10, 23 },
        }}),
        // Slot 'handleShowMainWindow'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 25 },
        }}),
        // Slot 'handleSwitchToPlayerTurn'
        QtMocHelpers::SlotData<void(int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'receiveBankLoosesCard'
        QtMocHelpers::SlotData<void(std::shared_ptr<Card>)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 28, 29 },
        }}),
        // Slot 'receiveBankGetsCard'
        QtMocHelpers::SlotData<void(std::shared_ptr<Card>)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 28, 29 },
        }}),
        // Slot 'receiveCardPurchaseFailed'
        QtMocHelpers::SlotData<void(int, CardId, QString)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 3, 4 }, { QMetaType::QString, 32 },
        }}),
        // Slot 'receiveDiceRollResult'
        QtMocHelpers::SlotData<void(int, QVector<int>)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 10, 34 },
        }}),
        // Slot 'receivePlayerBalanceChanged'
        QtMocHelpers::SlotData<void(int, int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { QMetaType::Int, 36 },
        }}),
        // Slot 'receivePlayerGetsCard'
        QtMocHelpers::SlotData<void(int, std::shared_ptr<Card>)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 28, 29 },
        }}),
        // Slot 'receivePlayerLoosesCard'
        QtMocHelpers::SlotData<void(int, std::shared_ptr<Card>)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 28, 29 },
        }}),
        // Slot 'receiveRollTwoDiceAvailable'
        QtMocHelpers::SlotData<void(int)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'handleCardClick'
        QtMocHelpers::SlotData<void(CardId)>(40, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 41 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->cardClickedForPurchase((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1]))); break;
        case 1: _t->createPlayers((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->rollDiceButtonClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->sendDiceRerollResponse((*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 4: _t->skipButtonClicked(); break;
        case 5: _t->setIncomeState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->setPurchaseState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->setWaitState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->handleFinishIncomeState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->handleFinishPurchaseState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->handleFinishWaitState((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->handleGameWon((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->handleRequestDiceRerollConfirmation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[2]))); break;
        case 13: _t->handleShowMainWindow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->handleSwitchToPlayerTurn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->receiveBankLoosesCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 16: _t->receiveBankGetsCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 17: _t->receiveCardPurchaseFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CardId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 18: _t->receiveDiceRollResult((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[2]))); break;
        case 19: _t->receivePlayerBalanceChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 20: _t->receivePlayerGetsCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 21: _t->receivePlayerLoosesCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 22: _t->receiveRollTwoDiceAvailable((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 23: _t->handleCardClick((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(CardId )>(_a, &MainWindow::cardClickedForPurchase, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(int )>(_a, &MainWindow::createPlayers, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(int )>(_a, &MainWindow::rollDiceButtonClicked, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(QVector<int> , bool )>(_a, &MainWindow::sendDiceRerollResponse, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::skipButtonClicked, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(int )>(_a, &MainWindow::setIncomeState, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(int )>(_a, &MainWindow::setPurchaseState, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)(int )>(_a, &MainWindow::setWaitState, 7))
            return;
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::cardClickedForPurchase(CardId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MainWindow::createPlayers(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void MainWindow::rollDiceButtonClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void MainWindow::sendDiceRerollResponse(QVector<int> _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void MainWindow::skipButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::setIncomeState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void MainWindow::setPurchaseState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void MainWindow::setWaitState(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
