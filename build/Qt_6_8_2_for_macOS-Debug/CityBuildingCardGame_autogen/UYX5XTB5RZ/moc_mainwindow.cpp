/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "activateCardsHighlighting",
    "",
    "playerBalance",
    "buildOneMoreBuilding",
    "buttonClickSound",
    "buyButtonClicked",
    "cardFailSound",
    "cardTurnSound",
    "cardWidgetClicked",
    "cardId",
    "checkPlayerCards",
    "playerId",
    "dice1",
    "dice2",
    "createPlayers",
    "playerNames",
    "deactivateCardsHighlighting",
    "diceRollAccepted",
    "rollButtonClicked",
    "rollButtonClickedWithCanReroll",
    "skipClicked",
    "takeCardSound",
    "updatedPlayersPanel",
    "askForReroll",
    "QWidget*",
    "parent",
    "displayBankGetsCard",
    "std::shared_ptr<Card>",
    "card",
    "displayBankLoosesCard",
    "displayPlayerGetsCard",
    "displayPlayerLoosesCard",
    "displayPlayerNewCard",
    "displayWorningWindow",
    "message",
    "finishGame",
    "currentPlayerId",
    "handlePlayerCardActivatedBefore",
    "handleShowMainWindow",
    "numPlayers",
    "processDiceRoll",
    "repaintPlayerPanel",
    "unlockBuildAgainIfDubleRollDice",
    "unlockDiceReroll",
    "unlockPlayerLandmark",
    "unlockRollTwoDiceButton",
    "updatePlayerBalanceLabel",
    "balance",
    "handleCardClick",
    "onRollOneDiceClicked",
    "onRollTwoDiceClicked",
    "onSkipClicked",
    "createCircleIcon",
    "color",
    "qsizetype",
    "size"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  248,    2, 0x06,    1 /* Public */,
       4,    0,  251,    2, 0x06,    3 /* Public */,
       5,    0,  252,    2, 0x06,    4 /* Public */,
       6,    0,  253,    2, 0x06,    5 /* Public */,
       7,    0,  254,    2, 0x06,    6 /* Public */,
       8,    0,  255,    2, 0x06,    7 /* Public */,
       9,    1,  256,    2, 0x06,    8 /* Public */,
      11,    4,  259,    2, 0x06,   10 /* Public */,
      15,    1,  268,    2, 0x06,   15 /* Public */,
      17,    0,  271,    2, 0x06,   17 /* Public */,
      18,    2,  272,    2, 0x06,   18 /* Public */,
      19,    2,  277,    2, 0x06,   21 /* Public */,
      20,    2,  282,    2, 0x06,   24 /* Public */,
      21,    0,  287,    2, 0x06,   27 /* Public */,
      22,    0,  288,    2, 0x06,   28 /* Public */,
      23,    0,  289,    2, 0x06,   29 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      24,    1,  290,    2, 0x0a,   30 /* Public */,
      27,    1,  293,    2, 0x0a,   32 /* Public */,
      30,    1,  296,    2, 0x0a,   34 /* Public */,
      31,    2,  299,    2, 0x0a,   36 /* Public */,
      32,    2,  304,    2, 0x0a,   39 /* Public */,
      33,    1,  309,    2, 0x0a,   42 /* Public */,
      34,    1,  312,    2, 0x0a,   44 /* Public */,
      36,    1,  315,    2, 0x0a,   46 /* Public */,
      38,    2,  318,    2, 0x0a,   48 /* Public */,
      39,    1,  323,    2, 0x0a,   51 /* Public */,
      41,    2,  326,    2, 0x0a,   53 /* Public */,
      42,    1,  331,    2, 0x0a,   56 /* Public */,
      43,    0,  334,    2, 0x0a,   58 /* Public */,
      44,    0,  335,    2, 0x0a,   59 /* Public */,
      45,    1,  336,    2, 0x0a,   60 /* Public */,
      46,    0,  339,    2, 0x0a,   62 /* Public */,
      47,    2,  340,    2, 0x0a,   63 /* Public */,
      49,    1,  345,    2, 0x08,   66 /* Private */,
      50,    0,  348,    2, 0x08,   68 /* Private */,
      51,    0,  349,    2, 0x08,   69 /* Private */,
      52,    0,  350,    2, 0x08,   70 /* Private */,
      53,    2,  351,    2, 0x08,   71 /* Private */,
      53,    1,  356,    2, 0x28,   74 /* Private | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::UChar, QMetaType::UChar,   10,   12,   13,   14,
    QMetaType::Void, QMetaType::QStringList,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   13,   14,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   13,   14,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 28,   12,   29,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 28,   12,   29,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   13,   14,
    QMetaType::Void, QMetaType::UChar,   40,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,   13,   14,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   48,   12,
    QMetaType::Void, QMetaType::UChar,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QIcon, QMetaType::QColor, 0x80000000 | 55,   54,   56,
    QMetaType::QIcon, QMetaType::QColor,   54,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'activateCardsHighlighting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'buildOneMoreBuilding'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'buttonClickSound'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'buyButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cardFailSound'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cardTurnSound'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cardWidgetClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'checkPlayerCards'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'createPlayers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<QString>, std::false_type>,
        // method 'deactivateCardsHighlighting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'diceRollAccepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'rollButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'rollButtonClickedWithCanReroll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'skipClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'takeCardSound'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatedPlayersPanel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'askForReroll'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'displayBankGetsCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'displayBankLoosesCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'displayPlayerGetsCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'displayPlayerLoosesCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'displayPlayerNewCard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'displayWorningWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'finishGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handlePlayerCardActivatedBefore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'handleShowMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'processDiceRoll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'repaintPlayerPanel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'unlockBuildAgainIfDubleRollDice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unlockDiceReroll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unlockPlayerLandmark'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Card>, std::false_type>,
        // method 'unlockRollTwoDiceButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePlayerBalanceLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleCardClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uchar, std::false_type>,
        // method 'onRollOneDiceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRollTwoDiceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSkipClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createCircleIcon'
        QtPrivate::TypeAndForceComplete<QIcon, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor, std::false_type>,
        QtPrivate::TypeAndForceComplete<qsizetype, std::false_type>,
        // method 'createCircleIcon'
        QtPrivate::TypeAndForceComplete<QIcon, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activateCardsHighlighting((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->buildOneMoreBuilding(); break;
        case 2: _t->buttonClickSound(); break;
        case 3: _t->buyButtonClicked(); break;
        case 4: _t->cardFailSound(); break;
        case 5: _t->cardTurnSound(); break;
        case 6: _t->cardWidgetClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 7: _t->checkPlayerCards((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[4]))); break;
        case 8: _t->createPlayers((*reinterpret_cast< std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 9: _t->deactivateCardsHighlighting(); break;
        case 10: _t->diceRollAccepted((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 11: _t->rollButtonClicked((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 12: _t->rollButtonClickedWithCanReroll((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 13: _t->skipClicked(); break;
        case 14: _t->takeCardSound(); break;
        case 15: _t->updatedPlayersPanel(); break;
        case 16: { bool _r = _t->askForReroll((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->displayBankGetsCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 18: _t->displayBankLoosesCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 19: _t->displayPlayerGetsCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 20: _t->displayPlayerLoosesCard((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[2]))); break;
        case 21: _t->displayPlayerNewCard((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 22: _t->displayWorningWindow((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->finishGame((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->handlePlayerCardActivatedBefore((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 25: _t->handleShowMainWindow((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 26: _t->processDiceRoll((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uchar>>(_a[2]))); break;
        case 27: _t->repaintPlayerPanel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->unlockBuildAgainIfDubleRollDice(); break;
        case 29: _t->unlockDiceReroll(); break;
        case 30: _t->unlockPlayerLandmark((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Card>>>(_a[1]))); break;
        case 31: _t->unlockRollTwoDiceButton(); break;
        case 32: _t->updatePlayerBalanceLabel((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 33: _t->handleCardClick((*reinterpret_cast< std::add_pointer_t<uchar>>(_a[1]))); break;
        case 34: _t->onRollOneDiceClicked(); break;
        case 35: _t->onRollTwoDiceClicked(); break;
        case 36: _t->onSkipClicked(); break;
        case 37: { QIcon _r = _t->createCircleIcon((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qsizetype>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        case 38: { QIcon _r = _t->createCircleIcon((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MainWindow::*)(int );
            if (_q_method_type _q_method = &MainWindow::activateCardsHighlighting; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::buildOneMoreBuilding; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::buttonClickSound; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::buyButtonClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::cardFailSound; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::cardTurnSound; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(uchar );
            if (_q_method_type _q_method = &MainWindow::cardWidgetClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(uchar , int , uchar , uchar );
            if (_q_method_type _q_method = &MainWindow::checkPlayerCards; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(QList<QString> );
            if (_q_method_type _q_method = &MainWindow::createPlayers; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::deactivateCardsHighlighting; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(uchar , uchar );
            if (_q_method_type _q_method = &MainWindow::diceRollAccepted; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(uchar , uchar );
            if (_q_method_type _q_method = &MainWindow::rollButtonClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)(uchar , uchar );
            if (_q_method_type _q_method = &MainWindow::rollButtonClickedWithCanReroll; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::skipClicked; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::takeCardSound; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::updatedPlayersPanel; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::activateCardsHighlighting(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::buildOneMoreBuilding()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::buttonClickSound()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::buyButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::cardFailSound()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::cardTurnSound()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::cardWidgetClicked(uchar _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::checkPlayerCards(uchar _t1, int _t2, uchar _t3, uchar _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::createPlayers(QList<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::deactivateCardsHighlighting()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MainWindow::diceRollAccepted(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::rollButtonClicked(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::rollButtonClickedWithCanReroll(uchar _t1, uchar _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::skipClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MainWindow::takeCardSound()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void MainWindow::updatedPlayersPanel()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}
QT_WARNING_POP
