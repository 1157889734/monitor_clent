/****************************************************************************
** Meta object code from reading C++ file 'inteanalywidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "inteanalywidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inteanalywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_inteAnalyWidget_t {
    QByteArrayData data[20];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_inteAnalyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_inteAnalyWidget_t qt_meta_stringdata_inteAnalyWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "inteAnalyWidget"
QT_MOC_LITERAL(1, 16, 15), // "registOutSignal"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "page"
QT_MOC_LITERAL(4, 38, 26), // "alarmPushButoonClickSignal"
QT_MOC_LITERAL(5, 65, 20), // "registOutButtonClick"
QT_MOC_LITERAL(6, 86, 24), // "alarmPushButoonClickSlot"
QT_MOC_LITERAL(7, 111, 15), // "alarmHappenSlot"
QT_MOC_LITERAL(8, 127, 19), // "alarmHappenCtrlSlot"
QT_MOC_LITERAL(9, 147, 14), // "alarmClearSlot"
QT_MOC_LITERAL(10, 162, 14), // "timeSetRecvMsg"
QT_MOC_LITERAL(11, 177, 4), // "year"
QT_MOC_LITERAL(12, 182, 5), // "month"
QT_MOC_LITERAL(13, 188, 3), // "day"
QT_MOC_LITERAL(14, 192, 4), // "hour"
QT_MOC_LITERAL(15, 197, 3), // "min"
QT_MOC_LITERAL(16, 201, 3), // "sec"
QT_MOC_LITERAL(17, 205, 26), // "openStartTimeSetWidgetSlot"
QT_MOC_LITERAL(18, 232, 25), // "openStopTimeSetWidgetSlot"
QT_MOC_LITERAL(19, 258, 15) // "recordQuerySlot"

    },
    "inteAnalyWidget\0registOutSignal\0\0page\0"
    "alarmPushButoonClickSignal\0"
    "registOutButtonClick\0alarmPushButoonClickSlot\0"
    "alarmHappenSlot\0alarmHappenCtrlSlot\0"
    "alarmClearSlot\0timeSetRecvMsg\0year\0"
    "month\0day\0hour\0min\0sec\0"
    "openStartTimeSetWidgetSlot\0"
    "openStopTimeSetWidgetSlot\0recordQuerySlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_inteAnalyWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   73,    2, 0x0a /* Public */,
       6,    0,   74,    2, 0x0a /* Public */,
       7,    0,   75,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    6,   78,    2, 0x0a /* Public */,
      17,    0,   91,    2, 0x0a /* Public */,
      18,    0,   92,    2, 0x0a /* Public */,
      19,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void inteAnalyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<inteAnalyWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->registOutSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->alarmPushButoonClickSignal(); break;
        case 2: _t->registOutButtonClick(); break;
        case 3: _t->alarmPushButoonClickSlot(); break;
        case 4: _t->alarmHappenSlot(); break;
        case 5: _t->alarmHappenCtrlSlot(); break;
        case 6: _t->alarmClearSlot(); break;
        case 7: _t->timeSetRecvMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 8: _t->openStartTimeSetWidgetSlot(); break;
        case 9: _t->openStopTimeSetWidgetSlot(); break;
        case 10: _t->recordQuerySlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (inteAnalyWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inteAnalyWidget::registOutSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (inteAnalyWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inteAnalyWidget::alarmPushButoonClickSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject inteAnalyWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_inteAnalyWidget.data,
    qt_meta_data_inteAnalyWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *inteAnalyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *inteAnalyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_inteAnalyWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int inteAnalyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void inteAnalyWidget::registOutSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void inteAnalyWidget::alarmPushButoonClickSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
