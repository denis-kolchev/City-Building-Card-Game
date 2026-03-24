/****************************************************************************
** Meta object code from reading C++ file 'playerpage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ui/playerpage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerpage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10PlayerPageE_t {};
} // unnamed namespace

template <> constexpr inline auto PlayerPage::qt_create_metaobjectdata<qt_meta_tag_ZN10PlayerPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlayerPage",
        "activateCardsHighlighting",
        "",
        "playerBalance",
        "deactivateCardsHighlighting",
        "rollOneDiceClicked",
        "playerId",
        "rollTwoDiceClicked",
        "skipClicked",
        "cardClicked",
        "CardId",
        "id",
        "handleCardClicked",
        "buttonBlocked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'activateCardsHighlighting'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'deactivateCardsHighlighting'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'rollOneDiceClicked'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'rollTwoDiceClicked'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'skipClicked'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'cardClicked'
        QtMocHelpers::SignalData<void(CardId)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'handleCardClicked'
        QtMocHelpers::SlotData<void(CardId)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'buttonBlocked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlayerPage, qt_meta_tag_ZN10PlayerPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlayerPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10PlayerPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10PlayerPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10PlayerPageE_t>.metaTypes,
    nullptr
} };

void PlayerPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlayerPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activateCardsHighlighting((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->deactivateCardsHighlighting(); break;
        case 2: _t->rollOneDiceClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->rollTwoDiceClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->skipClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->cardClicked((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1]))); break;
        case 6: _t->handleCardClicked((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1]))); break;
        case 7: _t->buttonBlocked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)(int )>(_a, &PlayerPage::activateCardsHighlighting, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)()>(_a, &PlayerPage::deactivateCardsHighlighting, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)(int )>(_a, &PlayerPage::rollOneDiceClicked, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)(int )>(_a, &PlayerPage::rollTwoDiceClicked, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)(int )>(_a, &PlayerPage::skipClicked, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerPage::*)(CardId )>(_a, &PlayerPage::cardClicked, 5))
            return;
    }
}

const QMetaObject *PlayerPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10PlayerPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PlayerPage::activateCardsHighlighting(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void PlayerPage::deactivateCardsHighlighting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayerPage::rollOneDiceClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PlayerPage::rollTwoDiceClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PlayerPage::skipClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void PlayerPage::cardClicked(CardId _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
