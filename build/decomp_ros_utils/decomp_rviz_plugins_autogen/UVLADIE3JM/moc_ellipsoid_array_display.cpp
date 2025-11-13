/****************************************************************************
** Meta object code from reading C++ file 'ellipsoid_array_display.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Utils/DecompROS/decomp_ros_utils/src/ellipsoid_array_display.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ellipsoid_array_display.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay_t {
    QByteArrayData data[3];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay_t qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay = {
    {
QT_MOC_LITERAL(0, 0, 42), // "decomp_rviz_plugins::Ellipsoi..."
QT_MOC_LITERAL(1, 43, 19), // "updateColorAndAlpha"
QT_MOC_LITERAL(2, 63, 0) // ""

    },
    "decomp_rviz_plugins::EllipsoidArrayDisplay\0"
    "updateColorAndAlpha\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_decomp_rviz_plugins__EllipsoidArrayDisplay[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void decomp_rviz_plugins::EllipsoidArrayDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EllipsoidArrayDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateColorAndAlpha(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject decomp_rviz_plugins::EllipsoidArrayDisplay::staticMetaObject = { {
    &rviz::MessageFilterDisplay<decomp_ros_msgs::EllipsoidArray>::staticMetaObject,
    qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay.data,
    qt_meta_data_decomp_rviz_plugins__EllipsoidArrayDisplay,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *decomp_rviz_plugins::EllipsoidArrayDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *decomp_rviz_plugins::EllipsoidArrayDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_decomp_rviz_plugins__EllipsoidArrayDisplay.stringdata0))
        return static_cast<void*>(this);
    return rviz::MessageFilterDisplay<decomp_ros_msgs::EllipsoidArray>::qt_metacast(_clname);
}

int decomp_rviz_plugins::EllipsoidArrayDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz::MessageFilterDisplay<decomp_ros_msgs::EllipsoidArray>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
