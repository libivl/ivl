/****************************************************************************
** Meta object code from reading C++ file 'item_delegate.hpp'
**
** Created: Wed Jun 19 01:44:13 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/item_views/item_delegate.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'item_delegate.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__item_delegate[] = {

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
      39,   32,   31,   31, 0x08,
      73,   61,   31,   31, 0x08,
     137,  131,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__item_delegate[] = {
    "ivl::qt_details::item_delegate\0\0editor\0"
    "commitData_(QWidget*)\0editor,hint\0"
    "closeEditor_(QWidget*,QAbstractItemDelegate::EndEditHint)\0"
    "index\0sizeHintChanged_(QModelIndex)\0"
};

const QMetaObject ivl::qt_details::item_delegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ivl__qt_details__item_delegate,
      qt_meta_data_ivl__qt_details__item_delegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::item_delegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::item_delegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::item_delegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__item_delegate))
        return static_cast<void*>(const_cast< item_delegate*>(this));
    if (!strcmp(_clname, "method_binder<item_delegate,QItemDelegate,QAbstractItemDelegate>"))
        return static_cast< method_binder<item_delegate,QItemDelegate,QAbstractItemDelegate>*>(const_cast< item_delegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int ivl::qt_details::item_delegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: commitData_((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: closeEditor_((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QAbstractItemDelegate::EndEditHint(*)>(_a[2]))); break;
        case 2: sizeHintChanged_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
