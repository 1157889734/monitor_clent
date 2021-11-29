/****************************************************************************
** Meta object code from reading C++ file 'pvmsmonitorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "pvmsmonitorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pvmsmonitorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pvmsMonitorWidget_t {
    QByteArrayData data[61];
    char stringdata0[1192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pvmsMonitorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pvmsMonitorWidget_t qt_meta_stringdata_pvmsMonitorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "pvmsMonitorWidget"
QT_MOC_LITERAL(1, 18, 26), // "alarmPushButoonClickSignal"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 15), // "registOutSignal"
QT_MOC_LITERAL(4, 62, 4), // "page"
QT_MOC_LITERAL(5, 67, 26), // "chStateLabelTextCtrlSignal"
QT_MOC_LITERAL(6, 94, 5), // "iFlag"
QT_MOC_LITERAL(7, 100, 29), // "camSwitchButtonTextCtrlSignal"
QT_MOC_LITERAL(8, 130, 24), // "chLabelDisplayCtrlSignal"
QT_MOC_LITERAL(9, 155, 35), // "fillLightSwitchButtonTextCtrl..."
QT_MOC_LITERAL(10, 191, 20), // "recordPlayCtrlSignal"
QT_MOC_LITERAL(11, 212, 19), // "setFullScreenSignal"
QT_MOC_LITERAL(12, 232, 21), // "hideAlarmWidgetSignal"
QT_MOC_LITERAL(13, 254, 21), // "showAlarmWidgetSignal"
QT_MOC_LITERAL(14, 276, 18), // "videoPollingSignal"
QT_MOC_LITERAL(15, 295, 18), // "presetReturnSignal"
QT_MOC_LITERAL(16, 314, 9), // "iCameraNO"
QT_MOC_LITERAL(17, 324, 19), // "cmpOptionCtrlSignal"
QT_MOC_LITERAL(18, 344, 5), // "iType"
QT_MOC_LITERAL(19, 350, 3), // "iCh"
QT_MOC_LITERAL(20, 354, 17), // "getDevStateSignal"
QT_MOC_LITERAL(21, 372, 13), // "setTimeSignal"
QT_MOC_LITERAL(22, 386, 28), // "presetNoGroupButtonClickSlot"
QT_MOC_LITERAL(23, 415, 9), // "iButtonNo"
QT_MOC_LITERAL(24, 425, 24), // "alarmPushButoonClickSlot"
QT_MOC_LITERAL(25, 450, 16), // "startPollingSlot"
QT_MOC_LITERAL(26, 467, 16), // "pausePollingSlot"
QT_MOC_LITERAL(27, 484, 26), // "manualSwitchLastCameraSlot"
QT_MOC_LITERAL(28, 511, 26), // "manualSwitchNextCameraSlot"
QT_MOC_LITERAL(29, 538, 17), // "presetSetCtrlSlot"
QT_MOC_LITERAL(30, 556, 17), // "presetGetCtrlSlot"
QT_MOC_LITERAL(31, 574, 22), // "temporarySaveBeginSlot"
QT_MOC_LITERAL(32, 597, 20), // "temporarySaveEndSlot"
QT_MOC_LITERAL(33, 618, 16), // "cameraSwitchSlot"
QT_MOC_LITERAL(34, 635, 19), // "fillLightSwitchSlot"
QT_MOC_LITERAL(35, 655, 19), // "manualSwitchEndSlot"
QT_MOC_LITERAL(36, 675, 25), // "closePresetPasswdPageSlot"
QT_MOC_LITERAL(37, 701, 13), // "setPresetSlot"
QT_MOC_LITERAL(38, 715, 20), // "registOutButtonClick"
QT_MOC_LITERAL(39, 736, 22), // "fillLightSwitchEndSlot"
QT_MOC_LITERAL(40, 759, 22), // "chLabelDisplayCtrlSlot"
QT_MOC_LITERAL(41, 782, 15), // "alarmHappenSlot"
QT_MOC_LITERAL(42, 798, 14), // "alarmClearSlot"
QT_MOC_LITERAL(43, 813, 19), // "alarmHappenCtrlSlot"
QT_MOC_LITERAL(44, 833, 17), // "setRecordPlayFlag"
QT_MOC_LITERAL(45, 851, 22), // "videoPollingSignalCtrl"
QT_MOC_LITERAL(46, 874, 23), // "setFullScreenSignalCtrl"
QT_MOC_LITERAL(47, 898, 22), // "presetReturnSignalCtrl"
QT_MOC_LITERAL(48, 921, 18), // "recordPlayCtrlSlot"
QT_MOC_LITERAL(49, 940, 24), // "chStateLabelTextCtrlSlot"
QT_MOC_LITERAL(50, 965, 27), // "camSwitchButtonTextCtrlSlot"
QT_MOC_LITERAL(51, 993, 33), // "fillLightSwitchButtonTextCtrl..."
QT_MOC_LITERAL(52, 1027, 17), // "cmpOptionCtrlSlot"
QT_MOC_LITERAL(53, 1045, 16), // "pvmsDownEndSlot1"
QT_MOC_LITERAL(54, 1062, 16), // "pvmsDownEndSlot2"
QT_MOC_LITERAL(55, 1079, 16), // "pvmsDownEndSlot3"
QT_MOC_LITERAL(56, 1096, 16), // "pvmsDownEndSlot4"
QT_MOC_LITERAL(57, 1113, 14), // "systimeSetSlot"
QT_MOC_LITERAL(58, 1128, 19), // "blackScreenCtrlSlot"
QT_MOC_LITERAL(59, 1148, 23), // "blackScreenExitCtrlSlot"
QT_MOC_LITERAL(60, 1172, 19) // "cameraSwitchEndSlot"

    },
    "pvmsMonitorWidget\0alarmPushButoonClickSignal\0"
    "\0registOutSignal\0page\0chStateLabelTextCtrlSignal\0"
    "iFlag\0camSwitchButtonTextCtrlSignal\0"
    "chLabelDisplayCtrlSignal\0"
    "fillLightSwitchButtonTextCtrlSignal\0"
    "recordPlayCtrlSignal\0setFullScreenSignal\0"
    "hideAlarmWidgetSignal\0showAlarmWidgetSignal\0"
    "videoPollingSignal\0presetReturnSignal\0"
    "iCameraNO\0cmpOptionCtrlSignal\0iType\0"
    "iCh\0getDevStateSignal\0setTimeSignal\0"
    "presetNoGroupButtonClickSlot\0iButtonNo\0"
    "alarmPushButoonClickSlot\0startPollingSlot\0"
    "pausePollingSlot\0manualSwitchLastCameraSlot\0"
    "manualSwitchNextCameraSlot\0presetSetCtrlSlot\0"
    "presetGetCtrlSlot\0temporarySaveBeginSlot\0"
    "temporarySaveEndSlot\0cameraSwitchSlot\0"
    "fillLightSwitchSlot\0manualSwitchEndSlot\0"
    "closePresetPasswdPageSlot\0setPresetSlot\0"
    "registOutButtonClick\0fillLightSwitchEndSlot\0"
    "chLabelDisplayCtrlSlot\0alarmHappenSlot\0"
    "alarmClearSlot\0alarmHappenCtrlSlot\0"
    "setRecordPlayFlag\0videoPollingSignalCtrl\0"
    "setFullScreenSignalCtrl\0presetReturnSignalCtrl\0"
    "recordPlayCtrlSlot\0chStateLabelTextCtrlSlot\0"
    "camSwitchButtonTextCtrlSlot\0"
    "fillLightSwitchButtonTextCtrlSlot\0"
    "cmpOptionCtrlSlot\0pvmsDownEndSlot1\0"
    "pvmsDownEndSlot2\0pvmsDownEndSlot3\0"
    "pvmsDownEndSlot4\0systimeSetSlot\0"
    "blackScreenCtrlSlot\0blackScreenExitCtrlSlot\0"
    "cameraSwitchEndSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pvmsMonitorWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  279,    2, 0x06 /* Public */,
       3,    1,  280,    2, 0x06 /* Public */,
       5,    1,  283,    2, 0x06 /* Public */,
       7,    1,  286,    2, 0x06 /* Public */,
       8,    0,  289,    2, 0x06 /* Public */,
       9,    1,  290,    2, 0x06 /* Public */,
      10,    0,  293,    2, 0x06 /* Public */,
      11,    0,  294,    2, 0x06 /* Public */,
      12,    0,  295,    2, 0x06 /* Public */,
      13,    0,  296,    2, 0x06 /* Public */,
      14,    0,  297,    2, 0x06 /* Public */,
      15,    1,  298,    2, 0x06 /* Public */,
      17,    2,  301,    2, 0x06 /* Public */,
      20,    0,  306,    2, 0x06 /* Public */,
      21,    0,  307,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    1,  308,    2, 0x0a /* Public */,
      24,    0,  311,    2, 0x0a /* Public */,
      25,    0,  312,    2, 0x0a /* Public */,
      26,    0,  313,    2, 0x0a /* Public */,
      27,    0,  314,    2, 0x0a /* Public */,
      28,    0,  315,    2, 0x0a /* Public */,
      29,    0,  316,    2, 0x0a /* Public */,
      30,    0,  317,    2, 0x0a /* Public */,
      31,    0,  318,    2, 0x0a /* Public */,
      32,    0,  319,    2, 0x0a /* Public */,
      33,    0,  320,    2, 0x0a /* Public */,
      34,    0,  321,    2, 0x0a /* Public */,
      35,    0,  322,    2, 0x0a /* Public */,
      36,    0,  323,    2, 0x0a /* Public */,
      37,    0,  324,    2, 0x0a /* Public */,
      38,    0,  325,    2, 0x0a /* Public */,
      39,    0,  326,    2, 0x0a /* Public */,
      40,    0,  327,    2, 0x0a /* Public */,
      41,    0,  328,    2, 0x0a /* Public */,
      42,    0,  329,    2, 0x0a /* Public */,
      43,    0,  330,    2, 0x0a /* Public */,
      44,    1,  331,    2, 0x0a /* Public */,
      45,    0,  334,    2, 0x0a /* Public */,
      46,    0,  335,    2, 0x0a /* Public */,
      47,    1,  336,    2, 0x0a /* Public */,
      48,    0,  339,    2, 0x0a /* Public */,
      49,    1,  340,    2, 0x0a /* Public */,
      50,    1,  343,    2, 0x0a /* Public */,
      51,    1,  346,    2, 0x0a /* Public */,
      52,    2,  349,    2, 0x0a /* Public */,
      53,    0,  354,    2, 0x0a /* Public */,
      54,    0,  355,    2, 0x0a /* Public */,
      55,    0,  356,    2, 0x0a /* Public */,
      56,    0,  357,    2, 0x0a /* Public */,
      57,    0,  358,    2, 0x0a /* Public */,
      58,    0,  359,    2, 0x0a /* Public */,
      59,    0,  360,    2, 0x0a /* Public */,
      60,    0,  361,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void pvmsMonitorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pvmsMonitorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->alarmPushButoonClickSignal(); break;
        case 1: _t->registOutSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->chStateLabelTextCtrlSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->camSwitchButtonTextCtrlSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->chLabelDisplayCtrlSignal(); break;
        case 5: _t->fillLightSwitchButtonTextCtrlSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->recordPlayCtrlSignal(); break;
        case 7: _t->setFullScreenSignal(); break;
        case 8: _t->hideAlarmWidgetSignal(); break;
        case 9: _t->showAlarmWidgetSignal(); break;
        case 10: _t->videoPollingSignal(); break;
        case 11: _t->presetReturnSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->cmpOptionCtrlSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->getDevStateSignal(); break;
        case 14: _t->setTimeSignal(); break;
        case 15: _t->presetNoGroupButtonClickSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->alarmPushButoonClickSlot(); break;
        case 17: _t->startPollingSlot(); break;
        case 18: _t->pausePollingSlot(); break;
        case 19: _t->manualSwitchLastCameraSlot(); break;
        case 20: _t->manualSwitchNextCameraSlot(); break;
        case 21: _t->presetSetCtrlSlot(); break;
        case 22: _t->presetGetCtrlSlot(); break;
        case 23: _t->temporarySaveBeginSlot(); break;
        case 24: _t->temporarySaveEndSlot(); break;
        case 25: _t->cameraSwitchSlot(); break;
        case 26: _t->fillLightSwitchSlot(); break;
        case 27: _t->manualSwitchEndSlot(); break;
        case 28: _t->closePresetPasswdPageSlot(); break;
        case 29: _t->setPresetSlot(); break;
        case 30: _t->registOutButtonClick(); break;
        case 31: _t->fillLightSwitchEndSlot(); break;
        case 32: _t->chLabelDisplayCtrlSlot(); break;
        case 33: _t->alarmHappenSlot(); break;
        case 34: _t->alarmClearSlot(); break;
        case 35: _t->alarmHappenCtrlSlot(); break;
        case 36: _t->setRecordPlayFlag((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->videoPollingSignalCtrl(); break;
        case 38: _t->setFullScreenSignalCtrl(); break;
        case 39: _t->presetReturnSignalCtrl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->recordPlayCtrlSlot(); break;
        case 41: _t->chStateLabelTextCtrlSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->camSwitchButtonTextCtrlSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->fillLightSwitchButtonTextCtrlSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->cmpOptionCtrlSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 45: _t->pvmsDownEndSlot1(); break;
        case 46: _t->pvmsDownEndSlot2(); break;
        case 47: _t->pvmsDownEndSlot3(); break;
        case 48: _t->pvmsDownEndSlot4(); break;
        case 49: _t->systimeSetSlot(); break;
        case 50: _t->blackScreenCtrlSlot(); break;
        case 51: _t->blackScreenExitCtrlSlot(); break;
        case 52: _t->cameraSwitchEndSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::alarmPushButoonClickSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::registOutSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::chStateLabelTextCtrlSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::camSwitchButtonTextCtrlSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::chLabelDisplayCtrlSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::fillLightSwitchButtonTextCtrlSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::recordPlayCtrlSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::setFullScreenSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::hideAlarmWidgetSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::showAlarmWidgetSignal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::videoPollingSignal)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::presetReturnSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::cmpOptionCtrlSignal)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::getDevStateSignal)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (pvmsMonitorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&pvmsMonitorWidget::setTimeSignal)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pvmsMonitorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_pvmsMonitorWidget.data,
    qt_meta_data_pvmsMonitorWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *pvmsMonitorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pvmsMonitorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pvmsMonitorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pvmsMonitorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void pvmsMonitorWidget::alarmPushButoonClickSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void pvmsMonitorWidget::registOutSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void pvmsMonitorWidget::chStateLabelTextCtrlSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void pvmsMonitorWidget::camSwitchButtonTextCtrlSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void pvmsMonitorWidget::chLabelDisplayCtrlSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void pvmsMonitorWidget::fillLightSwitchButtonTextCtrlSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void pvmsMonitorWidget::recordPlayCtrlSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void pvmsMonitorWidget::setFullScreenSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void pvmsMonitorWidget::hideAlarmWidgetSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void pvmsMonitorWidget::showAlarmWidgetSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void pvmsMonitorWidget::videoPollingSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void pvmsMonitorWidget::presetReturnSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void pvmsMonitorWidget::cmpOptionCtrlSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void pvmsMonitorWidget::getDevStateSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void pvmsMonitorWidget::setTimeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
