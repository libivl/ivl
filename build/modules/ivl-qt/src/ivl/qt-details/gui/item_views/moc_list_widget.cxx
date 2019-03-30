/****************************************************************************
** Meta object code from reading C++ file 'list_widget.hpp'
**
** Created: Tue Jun 18 00:47:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/item_views/list_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'list_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__list_widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   30,   29,   29, 0x08,
      74,   68,   29,   29, 0x08,
      96,   68,   29,   29, 0x08,
     118,   68,   29,   29, 0x08,
     146,   68,   29,   29, 0x08,
     170,   68,   29,   29, 0x08,
     192,   29,   29,   29, 0x08,
     215,  211,   29,   29, 0x08,
     251,  246,   29,   29, 0x08,
     282,  246,   29,   29, 0x08,
     313,  246,   29,   29, 0x08,
     350,  246,   29,   29, 0x08,
     383,  246,   29,   29, 0x08,
     414,  246,   29,   29, 0x08,
     445,   29,   29,   29, 0x08,
     479,  469,   29,   29, 0x08,
     539,  534,   29,   29, 0x08,
     572,  568,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__list_widget[] = {
    "ivl::qt_details::list_widget\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "index\0pressed_(QModelIndex)\0"
    "clicked_(QModelIndex)\0doubleClicked_(QModelIndex)\0"
    "activated_(QModelIndex)\0entered_(QModelIndex)\0"
    "viewportEntered_()\0idx\0"
    "indexesMoved_(QModelIndexList)\0item\0"
    "itemPressed_(QListWidgetItem*)\0"
    "itemClicked_(QListWidgetItem*)\0"
    "itemDoubleClicked_(QListWidgetItem*)\0"
    "itemActivated_(QListWidgetItem*)\0"
    "itemEntered_(QListWidgetItem*)\0"
    "itemChanged_(QListWidgetItem*)\0"
    "itemSelectionChanged_()\0curr,prev\0"
    "currentItemChanged_(QListWidgetItem*,QListWidgetItem*)\0"
    "text\0currentTextChanged_(QString)\0row\0"
    "currentRowChanged_(int)\0"
};

const QMetaObject ivl::qt_details::list_widget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_ivl__qt_details__list_widget,
      qt_meta_data_ivl__qt_details__list_widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::list_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::list_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::list_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__list_widget))
        return static_cast<void*>(const_cast< list_widget*>(this));
    if (!strcmp(_clname, "widget_base<list_widget>"))
        return static_cast< widget_base<list_widget>*>(const_cast< list_widget*>(this));
    if (!strcmp(_clname, "method_binder<list_widget,QListWidget,QListView>"))
        return static_cast< method_binder<list_widget,QListWidget,QListView>*>(const_cast< list_widget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int ivl::qt_details::list_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
        case 8: itemPressed_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: itemClicked_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: itemDoubleClicked_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 11: itemActivated_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: itemEntered_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: itemChanged_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: itemSelectionChanged_(); break;
        case 15: currentItemChanged_((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 16: currentTextChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: currentRowChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
