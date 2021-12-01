/****************************************************************************
** Meta object code from reading C++ file 'devmanagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "devmanagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devmanagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_devManageWidget_t {
    QByteArrayData data[21];
    char stringdata0[329];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_devManageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_devManageWidget_t qt_meta_stringdata_devManageWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "devManageWidget"
QT_MOC_LITERAL(1, 16, 26), // "alarmPushButoonClickSignal"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 16), // "systimeSetSignal"
QT_MOC_LITERAL(4, 61, 13), // "serverOffLine"
QT_MOC_LITERAL(5, 75, 4), // "iDex"
QT_MOC_LITERAL(6, 80, 15), // "registOutSignal"
QT_MOC_LITERAL(7, 96, 4), // "page"
QT_MOC_LITERAL(8, 101, 16), // "show_hide_Signal"
QT_MOC_LITERAL(9, 118, 5), // "value"
QT_MOC_LITERAL(10, 124, 17), // "trainNumberChange"
QT_MOC_LITERAL(11, 142, 14), // "TrainNumberStr"
QT_MOC_LITERAL(12, 157, 21), // "getDevStateSignalCtrl"
QT_MOC_LITERAL(13, 179, 24), // "alarmPushButoonClickSlot"
QT_MOC_LITERAL(14, 204, 15), // "alarmHappenSlot"
QT_MOC_LITERAL(15, 220, 19), // "alarmHappenCtrlSlot"
QT_MOC_LITERAL(16, 240, 14), // "alarmClearSlot"
QT_MOC_LITERAL(17, 255, 26), // "trainNumberButtonClickSlot"
QT_MOC_LITERAL(18, 282, 20), // "registOutButtonClick"
QT_MOC_LITERAL(19, 303, 21), // "KeyboardPressKeySlots"
QT_MOC_LITERAL(20, 325, 3) // "key"

    },
    "devManageWidget\0alarmPushButoonClickSignal\0"
    "\0systimeSetSignal\0serverOffLine\0iDex\0"
    "registOutSignal\0page\0show_hide_Signal\0"
    "value\0trainNumberChange\0TrainNumberStr\0"
    "getDevStateSignalCtrl\0alarmPushButoonClickSlot\0"
    "alarmHappenSlot\0alarmHappenCtrlSlot\0"
    "alarmClearSlot\0trainNumberButtonClickSlot\0"
    "registOutButtonClick\0KeyboardPressKeySlots\0"
    "key"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_devManageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,
       6,    1,   89,    2, 0x06 /* Public */,
       8,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   95,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x0a /* Public */,
      13,    0,   99,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    0,  101,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x0a /* Public */,
      18,    0,  104,    2, 0x0a /* Public */,
      19,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,   20,

       0        // eod
};

void devManageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<devManageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->alarmPushButoonClickSignal(); break;
        case 1: _t->systimeSetSignal(); break;
        case 2: _t->serverOffLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->registOutSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->show_hide_Signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->trainNumberChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->getDevStateSignalCtrl(); break;
        case 7: _t->alarmPushButoonClickSlot(); break;
        case 8: _t->alarmHappenSlot(); break;
        case 9: _t->alarmHappenCtrlSlot(); break;
        case 10: _t->alarmClearSlot(); break;
        case 11: _t->trainNumberButtonClickSlot(); break;
        case 12: _t->registOutButtonClick(); break;
        case 13: _t->KeyboardPressKeySlots((*reinterpret_cast< char(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (devManageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&devManageWidget::alarmPushButoonClickSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (devManageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&devManageWidget::systimeSetSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (devManageWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&devManageWidget::serverOffLine)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (devManageWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&devManageWidget::registOutSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (devManageWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&devManageWidget::show_hide_Signal)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject devManageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_devManageWidget.data,
    qt_meta_data_devManageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *devManageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *devManageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_devManageWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int devManageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void devManageWidget::alarmPushButoonClickSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void devManageWidget::systimeSetSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void devManageWidget::serverOffLine(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void devManageWidget::registOutSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void devManageWidget::show_hide_Signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
