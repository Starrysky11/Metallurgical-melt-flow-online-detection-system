/****************************************************************************
** Meta object code from reading C++ file 'camclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dectVelocity/camclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_camClass_t {
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_camClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_camClass_t qt_meta_stringdata_camClass = {
    {
QT_MOC_LITERAL(0, 0, 8), // "camClass"
QT_MOC_LITERAL(1, 9, 9), // "sendFrame"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 3), // "Mat"
QT_MOC_LITERAL(4, 24, 9), // "send2Deal"
QT_MOC_LITERAL(5, 34, 7), // "sendRes"
QT_MOC_LITERAL(6, 42, 13), // "sendFpsSignal"
QT_MOC_LITERAL(7, 56, 7), // "recMess"
QT_MOC_LITERAL(8, 64, 12), // "recSendFrame"
QT_MOC_LITERAL(9, 77, 13), // "recDealSignal"
QT_MOC_LITERAL(10, 91, 10) // "recFpsSlot"

    },
    "camClass\0sendFrame\0\0Mat\0send2Deal\0"
    "sendRes\0sendFpsSignal\0recMess\0"
    "recSendFrame\0recDealSignal\0recFpsSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_camClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    2,   57,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       6,    2,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void camClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        camClass *_t = static_cast<camClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendFrame((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->send2Deal((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 2: _t->sendRes((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->sendFpsSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->recMess(); break;
        case 5: _t->recSendFrame(); break;
        case 6: _t->recDealSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->recFpsSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (camClass::*)(Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camClass::sendFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (camClass::*)(Mat , Mat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camClass::send2Deal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (camClass::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camClass::sendRes)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (camClass::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&camClass::sendFpsSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject camClass::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_camClass.data,
    qt_meta_data_camClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *camClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *camClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_camClass.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int camClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void camClass::sendFrame(Mat _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void camClass::send2Deal(Mat _t1, Mat _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void camClass::sendRes(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void camClass::sendFpsSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
