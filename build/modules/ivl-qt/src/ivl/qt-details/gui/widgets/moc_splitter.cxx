/****************************************************************************
** Meta object code from reading C++ file 'splitter.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/splitter.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'splitter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__splitter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   27,   26,   26, 0x08,
      75,   65,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__splitter[] = {
    "ivl::qt_details::splitter\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "pos,index\0splitterMoved_(int,int)\0"
};

const QMetaObject ivl::qt_details::splitter::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_ivl__qt_details__splitter,
      qt_meta_data_ivl__qt_details__splitter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::splitter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::splitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::splitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__splitter))
        return static_cast<void*>(const_cast< splitter*>(this));
    if (!strcmp(_clname, "widget_base<splitter>"))
        return static_cast< widget_base<splitter>*>(const_cast< splitter*>(this));
    if (!strcmp(_clname, "method_binder<splitter,QSplitter>"))
        return static_cast< method_binder<splitter,QSplitter>*>(const_cast< splitter*>(this));
    return QSplitter::qt_metacast(_clname);
}

int ivl::qt_details::splitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: splitterMoved_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
