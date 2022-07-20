/****************************************************************************
** Meta object code from reading C++ file 'dealclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dectVelocity/dealclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dealclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dealClass_t {
    QByteArrayData data[8];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dealClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dealClass_t qt_meta_stringdata_dealClass = {
    {
QT_MOC_LITERAL(0, 0, 9), // "dealClass"
QT_MOC_LITERAL(1, 10, 7), // "sendVel"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 10), // "sendSignal"
QT_MOC_LITERAL(4, 30, 10), // "send2Frame"
QT_MOC_LITERAL(5, 41, 3), // "Mat"
QT_MOC_LITERAL(6, 45, 8), // "recFrame"
QT_MOC_LITERAL(7, 54, 10) // "recSendRes"

    },
    "dealClass\0sendVel\0\0sendSignal\0send2Frame\0"
    "Mat\0recFrame\0recSendRes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dealClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       3,    1,   44,    2, 0x06 /* Public */,
       4,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   52,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Float,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    2,    2,
    QMetaType::Void,

       0        // eod
};

void dealClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dealClass *_t = static_cast<dealClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendVel((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->sendSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->send2Frame((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 3: _t->recFrame((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 4: _t->recSendRes(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dealClass::*)(const int , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dealClass::sendVel)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (dealClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dealClass::sendSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (dealClass::*)(Mat , Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dealClass::send2Frame)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dealClass::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_dealClass.data,
    qt_meta_data_dealClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dealClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dealClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dealClass.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int dealClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void dealClass::sendVel(const int _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dealClass::sendSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void dealClass::send2Frame(Mat _t1, Mat _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
