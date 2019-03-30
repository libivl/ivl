/****************************************************************************
** Meta object code from reading C++ file 'stacked_layout.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/kernel/stacked_layout.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stacked_layout.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__stacked_layout[] = {

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
      39,   33,   32,   32, 0x08,
      59,   33,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__stacked_layout[] = {
    "ivl::qt_details::stacked_layout\0\0index\0"
    "widgetRemoved_(int)\0currentChanged_(int)\0"
};

const QMetaObject ivl::qt_details::stacked_layout::staticMetaObject = {
    { &QStackedLayout::staticMetaObject, qt_meta_stringdata_ivl__qt_details__stacked_layout,
      qt_meta_data_ivl__qt_details__stacked_layout, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::stacked_layout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::stacked_layout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::stacked_layout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__stacked_layout))
        return static_cast<void*>(const_cast< stacked_layout*>(this));
    if (!strcmp(_clname, "method_binder<stacked_layout,QStackedLayout>"))
        return static_cast< method_binder<stacked_layout,QStackedLayout>*>(const_cast< stacked_layout*>(this));
    return QStackedLayout::qt_metacast(_clname);
}

int ivl::qt_details::stacked_layout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: widgetRemoved_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: currentChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
