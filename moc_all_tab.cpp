/****************************************************************************
** Meta object code from reading C++ file 'all_tab.h'
**
** Created: Sun May 11 01:30:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interface/GUI/tabs/all_tab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'all_tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AllTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x08,
      32,    7,    7,    7, 0x08,
      60,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AllTab[] = {
    "AllTab\0\0,\0cellSelected(int,int)\0"
    "customMenuRequested(QPoint)\0"
    "add_to_library()\0"
};

void AllTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AllTab *_t = static_cast<AllTab *>(_o);
        switch (_id) {
        case 0: _t->cellSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->customMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->add_to_library(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AllTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AllTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AllTab,
      qt_meta_data_AllTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AllTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AllTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AllTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AllTab))
        return static_cast<void*>(const_cast< AllTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int AllTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
