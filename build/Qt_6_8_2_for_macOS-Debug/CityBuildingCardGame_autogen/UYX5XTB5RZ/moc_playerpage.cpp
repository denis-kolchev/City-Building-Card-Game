/****************************************************************************
** Meta object code from reading C++ file 'playerpage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
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
struct qt_meta_tag_ZN10PlayerPageE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10PlayerPageE = QtMocHelpers::stringData(
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
    "id",
    "handleCardClicked",
    "buttonBlocked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10PlayerPageE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    0,   65,    2, 0x06,    3 /* Public */,
       5,    1,   66,    2, 0x06,    4 /* Public */,
       7,    1,   69,    2, 0x06,    6 /* Public */,
       8,    1,   72,    2, 0x06,    8 /* Public */,
       9,    1,   75,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   78,    2, 0x0a,   12 /* Public */,
      12,    0,   81,    2, 0x0a,   14 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,    6,
    QMetaType::Void, QMetaType::UChar,    6,
    QMetaType::Void, QMetaType::UChar,    6,
    QMetaType::Void, QMetaType::UChar,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject PlayerPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN10PlayerPageE.offsetsAndSizes,
    qt_meta_data_ZN10PlayerPageE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10PlayerPageE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PlayerPage, std::true_type>,
        // method 'activateCardsHighlighting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'deactivateCardsHighlighting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rollOneDiceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'rollTwoDiceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'skipClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'cardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'handleCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'buttonBlocked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void PlayerPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlayerPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activateCardsHighlighting((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->deactivateCardsHighlighting(); break;
        case 2: _t->rollOneDiceClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 3: _t->rollTwoDiceClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 4: _t->skipClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 5: _t->cardClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 6: _t->handleCardClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 7: _t->buttonBlocked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (PlayerPage::*)(int );
            if (_q_method_type _q_method = &PlayerPage::activateCardsHighlighting; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (PlayerPage::*)();
            if (_q_method_type _q_method = &PlayerPage::deactivateCardsHighlighting; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (PlayerPage::*)(uchar );
            if (_q_method_type _q_method = &PlayerPage::rollOneDiceClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (PlayerPage::*)(uchar );
            if (_q_method_type _q_method = &PlayerPage::rollTwoDiceClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (PlayerPage::*)(uchar );
            if (_q_method_type _q_method = &PlayerPage::skipClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (PlayerPage::*)(uchar );
            if (_q_method_type _q_method = &PlayerPage::cardClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *PlayerPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10PlayerPageE.stringdata0))
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
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerPage::deactivateCardsHighlighting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayerPage::rollOneDiceClicked(uchar _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayerPage::rollTwoDiceClicked(uchar _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayerPage::skipClicked(uchar _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlayerPage::cardClicked(uchar _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
