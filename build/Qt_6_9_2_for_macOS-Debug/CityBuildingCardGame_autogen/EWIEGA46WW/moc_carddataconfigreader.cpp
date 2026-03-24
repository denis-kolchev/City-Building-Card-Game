/****************************************************************************
** Meta object code from reading C++ file 'carddataconfigreader.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../carddataconfigreader.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carddataconfigreader.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20CardDataConfigReaderE_t {};
} // unnamed namespace

template <> constexpr inline auto CardDataConfigReader::qt_create_metaobjectdata<qt_meta_tag_ZN20CardDataConfigReaderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CardDataConfigReader",
        "configDataReadyToRead",
        "",
        "sendCardData",
        "QList<std::shared_ptr<Card>>",
        "data",
        "handleReadFromRange",
        "CardId",
        "begin",
        "end",
        "handleRequestCardData",
        "std::shared_ptr<CardDataHandler>",
        "handler"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'configDataReadyToRead'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sendCardData'
        QtMocHelpers::SignalData<void(QVector<std::shared_ptr<Card>>)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'handleReadFromRange'
        QtMocHelpers::SlotData<void(CardId, CardId)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { 0x80000000 | 7, 9 },
        }}),
        // Slot 'handleRequestCardData'
        QtMocHelpers::SlotData<void(CardId, CardId, std::shared_ptr<CardDataHandler>)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { 0x80000000 | 7, 9 }, { 0x80000000 | 11, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CardDataConfigReader, qt_meta_tag_ZN20CardDataConfigReaderE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CardDataConfigReader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CardDataConfigReaderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CardDataConfigReaderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20CardDataConfigReaderE_t>.metaTypes,
    nullptr
} };

void CardDataConfigReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CardDataConfigReader *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->configDataReadyToRead(); break;
        case 1: _t->sendCardData((*reinterpret_cast< std::add_pointer_t<QList<std::shared_ptr<Card>>>>(_a[1]))); break;
        case 2: _t->handleReadFromRange((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CardId>>(_a[2]))); break;
        case 3: _t->handleRequestCardData((*reinterpret_cast< std::add_pointer_t<CardId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CardId>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<CardDataHandler>>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CardDataConfigReader::*)()>(_a, &CardDataConfigReader::configDataReadyToRead, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CardDataConfigReader::*)(QVector<std::shared_ptr<Card>> )>(_a, &CardDataConfigReader::sendCardData, 1))
            return;
    }
}

const QMetaObject *CardDataConfigReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardDataConfigReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20CardDataConfigReaderE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CardDataConfigReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CardDataConfigReader::configDataReadyToRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CardDataConfigReader::sendCardData(QVector<std::shared_ptr<Card>> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
