/****************************************************************************
** Meta object code from reading C++ file 'shelves_tab.h'
**
** Created: Sun May 11 14:30:09 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interface/GUI/tabs/shelves_tab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shelves_tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShelvesTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ShelvesTab[] = {
    "ShelvesTab\0\0shelf_selected(QListWidgetItem*)\0"
};

void ShelvesTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShelvesTab *_t = static_cast<ShelvesTab *>(_o);
        switch (_id) {
        case 0: _t->shelf_selected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShelvesTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShelvesTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ShelvesTab,
      qt_meta_data_ShelvesTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShelvesTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShelvesTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShelvesTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShelvesTab))
        return static_cast<void*>(const_cast< ShelvesTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int ShelvesTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
