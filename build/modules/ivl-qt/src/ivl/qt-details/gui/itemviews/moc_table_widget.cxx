/****************************************************************************
** Meta object code from reading C++ file 'table_widget.hpp'
**
** Created: Fri May 17 20:39:19 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/itemviews/table_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'table_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__table_widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   31,   30,   30, 0x08,
      75,   69,   30,   30, 0x08,
      97,   69,   30,   30, 0x08,
     119,   69,   30,   30, 0x08,
     147,   69,   30,   30, 0x08,
     171,   69,   30,   30, 0x08,
     193,   30,   30,   30, 0x08,
     217,  212,   30,   30, 0x08,
     249,  212,   30,   30, 0x08,
     281,  212,   30,   30, 0x08,
     319,  212,   30,   30, 0x08,
     353,  212,   30,   30, 0x08,
     385,  212,   30,   30, 0x08,
     425,  417,   30,   30, 0x08,
     447,  417,   30,   30, 0x08,
     469,  417,   30,   30, 0x08,
     497,  417,   30,   30, 0x08,
     521,  417,   30,   30, 0x08,
     543,  417,   30,   30, 0x08,
     565,   30,   30,   30, 0x08,
     599,  589,   30,   30, 0x08,
     692,  656,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__table_widget[] = {
    "ivl::qt_details::table_widget\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "index\0pressed_(QModelIndex)\0"
    "clicked_(QModelIndex)\0doubleClicked_(QModelIndex)\0"
    "activated_(QModelIndex)\0entered_(QModelIndex)\0"
    "viewportEntered_()\0item\0"
    "itemPressed_(QTableWidgetItem*)\0"
    "itemClicked_(QTableWidgetItem*)\0"
    "itemDoubleClicked_(QTableWidgetItem*)\0"
    "itemActivated_(QTableWidgetItem*)\0"
    "itemEntered_(QTableWidgetItem*)\0"
    "itemChanged_(QTableWidgetItem*)\0row,col\0"
    "cellPressed_(int,int)\0cellClicked_(int,int)\0"
    "cellDoubleClicked_(int,int)\0"
    "cellActivated_(int,int)\0cellEntered_(int,int)\0"
    "cellChanged_(int,int)\0itemSelectionChanged_()\0"
    "curr,prev\0"
    "currentItemChanged_(QTableWidgetItem*,QTableWidgetItem*)\0"
    "curr_row,curr_col,prev_row,prev_col\0"
    "currentCellChanged_(int,int,int,int)\0"
};

const QMetaObject ivl::qt_details::table_widget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_ivl__qt_details__table_widget,
      qt_meta_data_ivl__qt_details__table_widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::table_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::table_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::table_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__table_widget))
        return static_cast<void*>(const_cast< table_widget*>(this));
    if (!strcmp(_clname, "widget_base<table_widget>"))
        return static_cast< widget_base<table_widget>*>(const_cast< table_widget*>(this));
    if (!strcmp(_clname, "method_binder<table_widget,QTableWidget,QTableView>"))
        return static_cast< method_binder<table_widget,QTableWidget,QTableView>*>(const_cast< table_widget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int ivl::qt_details::table_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
        case 7: itemPressed_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 8: itemClicked_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 9: itemDoubleClicked_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 10: itemActivated_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 11: itemEntered_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 12: itemChanged_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 13: cellPressed_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: cellClicked_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: cellDoubleClicked_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: cellActivated_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: cellEntered_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: cellChanged_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: itemSelectionChanged_(); break;
        case 20: currentItemChanged_((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 21: currentCellChanged_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
