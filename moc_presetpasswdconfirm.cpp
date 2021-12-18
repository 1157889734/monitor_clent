/****************************************************************************
** Meta object code from reading C++ file 'presetpasswdconfirm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "presetpasswdconfirm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'presetpasswdconfirm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_presetPasswdConfirm_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_presetPasswdConfirm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_presetPasswdConfirm_t qt_meta_stringdata_presetPasswdConfirm = {
    {
QT_MOC_LITERAL(0, 0, 19), // "presetPasswdConfirm"
QT_MOC_LITERAL(1, 20, 15), // "sendCloseSignal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "sendOkSignal"
QT_MOC_LITERAL(4, 50, 16), // "show_hide_Signal"
QT_MOC_LITERAL(5, 67, 5), // "value"
QT_MOC_LITERAL(6, 73, 19), // "pushButtonClickSlot"
QT_MOC_LITERAL(7, 93, 21), // "KeyboardPressKeySlots"
QT_MOC_LITERAL(8, 115, 3), // "key"
QT_MOC_LITERAL(9, 119, 17) // "show_hide_Funtion"

    },
    "presetPasswdConfirm\0sendCloseSignal\0"
    "\0sendOkSignal\0show_hide_Signal\0value\0"
    "pushButtonClickSlot\0KeyboardPressKeySlots\0"
    "key\0show_hide_Funtion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_presetPasswdConfirm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    1,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   49,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char,    8,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void presetPasswdConfirm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<presetPasswdConfirm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCloseSignal(); break;
        case 1: _t->sendOkSignal(); break;
        case 2: _t->show_hide_Signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->pushButtonClickSlot(); break;
        case 4: _t->KeyboardPressKeySlots((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 5: _t->show_hide_Funtion((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (presetPasswdConfirm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&presetPasswdConfirm::sendCloseSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (presetPasswdConfirm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&presetPasswdConfirm::sendOkSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (presetPasswdConfirm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&presetPasswdConfirm::show_hide_Signal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject presetPasswdConfirm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_presetPasswdConfirm.data,
    qt_meta_data_presetPasswdConfirm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *presetPasswdConfirm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *presetPasswdConfirm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_presetPasswdConfirm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int presetPasswdConfirm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void presetPasswdConfirm::sendCloseSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void presetPasswdConfirm::sendOkSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void presetPasswdConfirm::show_hide_Signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
