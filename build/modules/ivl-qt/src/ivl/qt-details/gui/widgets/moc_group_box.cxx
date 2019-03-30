/****************************************************************************
** Meta object code from reading C++ file 'group_box.hpp'
**
** Created: Sat Jun 15 16:29:42 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/group_box.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'group_box.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__group_box[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   28,   27,   27, 0x08,
      74,   66,   27,   27, 0x08,
      89,   66,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__group_box[] = {
    "ivl::qt_details::group_box\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "checked\0clicked_(bool)\0toggled_(bool)\0"
};

const QMetaObject ivl::qt_details::group_box::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__group_box,
      qt_meta_data_ivl__qt_details__group_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::group_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::group_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::group_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__group_box))
        return static_cast<void*>(const_cast< group_box*>(this));
    if (!strcmp(_clname, "widget_base<group_box>"))
        return static_cast< widget_base<group_box>*>(const_cast< group_box*>(this));
    if (!strcmp(_clname, "method_binder<group_box,QGroupBox>"))
        return static_cast< method_binder<group_box,QGroupBox>*>(const_cast< group_box*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int ivl::qt_details::group_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: clicked_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: toggled_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
