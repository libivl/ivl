/****************************************************************************
** Meta object code from reading C++ file 'list_view.hpp'
**
** Created: Mon Jun 17 00:46:30 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/item_views/list_view.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'list_view.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__list_view[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   28,   27,   27, 0x08,
      72,   66,   27,   27, 0x08,
      94,   66,   27,   27, 0x08,
     116,   66,   27,   27, 0x08,
     144,   66,   27,   27, 0x08,
     168,   66,   27,   27, 0x08,
     190,   27,   27,   27, 0x08,
     213,  209,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__list_view[] = {
    "ivl::qt_details::list_view\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "index\0pressed_(QModelIndex)\0"
    "clicked_(QModelIndex)\0doubleClicked_(QModelIndex)\0"
    "activated_(QModelIndex)\0entered_(QModelIndex)\0"
    "viewportEntered_()\0idx\0"
    "indexesMoved_(QModelIndexList)\0"
};

const QMetaObject ivl::qt_details::list_view::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_ivl__qt_details__list_view,
      qt_meta_data_ivl__qt_details__list_view, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::list_view::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::list_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::list_view::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__list_view))
        return static_cast<void*>(const_cast< list_view*>(this));
    if (!strcmp(_clname, "widget_base<list_view>"))
        return static_cast< widget_base<list_view>*>(const_cast< list_view*>(this));
    if (!strcmp(_clname, "method_binder<list_view,QListView>"))
        return static_cast< method_binder<list_view,QListView>*>(const_cast< list_view*>(this));
    return QListView::qt_metacast(_clname);
}

int ivl::qt_details::list_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: pressed_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: clicked_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: doubleClicked_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: activated_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: entered_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: viewportEntered_(); break;
        case 7: indexesMoved_((*reinterpret_cast< const QModelIndexList(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
