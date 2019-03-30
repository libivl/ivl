/****************************************************************************
** Meta object code from reading C++ file 'tree_widget.hpp'
**
** Created: Tue Jun 18 00:47:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/item_views/tree_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tree_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__tree_widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
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
     211,   68,   29,   29, 0x08,
     234,   68,   29,   29, 0x08,
     267,  258,   29,   29, 0x08,
     302,  258,   29,   29, 0x08,
     337,  258,   29,   29, 0x08,
     378,  258,   29,   29, 0x08,
     415,  258,   29,   29, 0x08,
     450,  258,   29,   29, 0x08,
     490,  485,   29,   29, 0x08,
     522,  485,   29,   29, 0x08,
     555,   29,   29,   29, 0x08,
     589,  579,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__tree_widget[] = {
    "ivl::qt_details::tree_widget\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "index\0pressed_(QModelIndex)\0"
    "clicked_(QModelIndex)\0doubleClicked_(QModelIndex)\0"
    "activated_(QModelIndex)\0entered_(QModelIndex)\0"
    "viewportEntered_()\0expanded_(QModelIndex)\0"
    "collapsed_(QModelIndex)\0item,col\0"
    "itemPressed_(QTreeWidgetItem*,int)\0"
    "itemClicked_(QTreeWidgetItem*,int)\0"
    "itemDoubleClicked_(QTreeWidgetItem*,int)\0"
    "itemActivated_(QTreeWidgetItem*,int)\0"
    "itemEntered_(QTreeWidgetItem*,int)\0"
    "itemChanged_(QTreeWidgetItem*,int)\0"
    "item\0itemExpanded_(QTreeWidgetItem*)\0"
    "itemCollapsed_(QTreeWidgetItem*)\0"
    "itemSelectionChanged_()\0curr,prev\0"
    "currentItemChanged_(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

const QMetaObject ivl::qt_details::tree_widget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_ivl__qt_details__tree_widget,
      qt_meta_data_ivl__qt_details__tree_widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::tree_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::tree_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::tree_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__tree_widget))
        return static_cast<void*>(const_cast< tree_widget*>(this));
    if (!strcmp(_clname, "widget_base<tree_widget>"))
        return static_cast< widget_base<tree_widget>*>(const_cast< tree_widget*>(this));
    if (!strcmp(_clname, "method_binder<tree_widget,QTreeWidget,QTreeView>"))
        return static_cast< method_binder<tree_widget,QTreeWidget,QTreeView>*>(const_cast< tree_widget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int ivl::qt_details::tree_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
        case 7: expanded_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: collapsed_((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: itemPressed_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: itemClicked_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: itemDoubleClicked_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: itemActivated_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: itemEntered_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: itemChanged_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: itemExpanded_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 16: itemCollapsed_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 17: itemSelectionChanged_(); break;
        case 18: currentItemChanged_((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
