/****************************************************************************
** Meta object code from reading C++ file 'picanimationwid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Album/picanimationwid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'picanimationwid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PicAnimationWid_t {
    QByteArrayData data[13];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PicAnimationWid_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PicAnimationWid_t qt_meta_stringdata_PicAnimationWid = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PicAnimationWid"
QT_MOC_LITERAL(1, 16, 12), // "SigUpPreList"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 47, 13), // "SigSelectItem"
QT_MOC_LITERAL(5, 61, 8), // "SigStart"
QT_MOC_LITERAL(6, 70, 7), // "SigStop"
QT_MOC_LITERAL(7, 78, 13), // "SigStartMusic"
QT_MOC_LITERAL(8, 92, 12), // "SigStopMusic"
QT_MOC_LITERAL(9, 105, 16), // "SlotUpSelectShow"
QT_MOC_LITERAL(10, 122, 4), // "path"
QT_MOC_LITERAL(11, 127, 15), // "SlotStartOrStop"
QT_MOC_LITERAL(12, 143, 7) // "TimeOut"

    },
    "PicAnimationWid\0SigUpPreList\0\0"
    "QTreeWidgetItem*\0SigSelectItem\0SigStart\0"
    "SigStop\0SigStartMusic\0SigStopMusic\0"
    "SlotUpSelectShow\0path\0SlotStartOrStop\0"
    "TimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PicAnimationWid[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    0,   65,    2, 0x06 /* Public */,
       6,    0,   66,    2, 0x06 /* Public */,
       7,    0,   67,    2, 0x06 /* Public */,
       8,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   69,    2, 0x0a /* Public */,
      11,    0,   72,    2, 0x0a /* Public */,
      12,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PicAnimationWid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PicAnimationWid *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigUpPreList((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->SigSelectItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->SigStart(); break;
        case 3: _t->SigStop(); break;
        case 4: _t->SigStartMusic(); break;
        case 5: _t->SigStopMusic(); break;
        case 6: _t->SlotUpSelectShow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->SlotStartOrStop(); break;
        case 8: _t->TimeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PicAnimationWid::*)(QTreeWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigUpPreList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PicAnimationWid::*)(QTreeWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigSelectItem)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PicAnimationWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigStart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PicAnimationWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigStop)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PicAnimationWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigStartMusic)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PicAnimationWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicAnimationWid::SigStopMusic)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PicAnimationWid::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PicAnimationWid.data,
    qt_meta_data_PicAnimationWid,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PicAnimationWid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PicAnimationWid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PicAnimationWid.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PicAnimationWid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PicAnimationWid::SigUpPreList(QTreeWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PicAnimationWid::SigSelectItem(QTreeWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PicAnimationWid::SigStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PicAnimationWid::SigStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PicAnimationWid::SigStartMusic()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PicAnimationWid::SigStopMusic()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
