/****************************************************************************
** Meta object code from reading C++ file 'usergroupmanage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "usergroupmanage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usergroupmanage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_usergroupManage_t {
    QByteArrayData data[11];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_usergroupManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_usergroupManage_t qt_meta_stringdata_usergroupManage = {
    {
QT_MOC_LITERAL(0, 0, 15), // "usergroupManage"
QT_MOC_LITERAL(1, 16, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 24), // "on_addpushButton_clicked"
QT_MOC_LITERAL(4, 56, 25), // "on_savepushButton_clicked"
QT_MOC_LITERAL(5, 82, 27), // "on_deletepushButton_clicked"
QT_MOC_LITERAL(6, 110, 20), // "choose_type_function"
QT_MOC_LITERAL(7, 131, 4), // "type"
QT_MOC_LITERAL(8, 136, 20), // "table_choose_fuction"
QT_MOC_LITERAL(9, 157, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(10, 175, 4) // "item"

    },
    "usergroupManage\0buttonClicked\0\0"
    "on_addpushButton_clicked\0"
    "on_savepushButton_clicked\0"
    "on_deletepushButton_clicked\0"
    "choose_type_function\0type\0"
    "table_choose_fuction\0QTableWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_usergroupManage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   47,    2, 0x0a /* Public */,
       4,    0,   48,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void usergroupManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<usergroupManage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_addpushButton_clicked(); break;
        case 2: _t->on_savepushButton_clicked(); break;
        case 3: _t->on_deletepushButton_clicked(); break;
        case 4: _t->choose_type_function((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->table_choose_fuction((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (usergroupManage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&usergroupManage::buttonClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject usergroupManage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_usergroupManage.data,
    qt_meta_data_usergroupManage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *usergroupManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usergroupManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_usergroupManage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int usergroupManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void usergroupManage::buttonClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
