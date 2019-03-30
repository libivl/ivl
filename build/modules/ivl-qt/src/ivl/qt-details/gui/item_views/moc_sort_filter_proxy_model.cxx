/****************************************************************************
** Meta object code from reading C++ file 'sort_filter_proxy_model.hpp'
**
** Created: Tue Jun 18 12:27:21 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/item_views/sort_filter_proxy_model.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sort_filter_proxy_model.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__sort_filter_proxy_model[] = {

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
      64,   42,   41,   41, 0x08,
     117,  102,   41,   41, 0x08,
     161,   41,   41,   41, 0x08,
     178,   41,   41,   41, 0x08,
     219,  204,   41,   41, 0x08,
     263,  204,   41,   41, 0x08,
     298,  204,   41,   41, 0x08,
     341,  204,   41,   41, 0x08,
     375,  204,   41,   41, 0x08,
     422,  204,   41,   41, 0x08,
     460,  204,   41,   41, 0x08,
     506,  204,   41,   41, 0x08,
     543,   41,   41,   41, 0x08,
     566,   41,   41,   41, 0x08,
     604,  580,   41,   41, 0x08,
     661,  580,   41,   41, 0x08,
     733,  709,   41,   41, 0x08,
     793,  709,   41,   41, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__sort_filter_proxy_model[] = {
    "ivl::qt_details::sort_filter_proxy_model\0"
    "\0top_left,bottom_right\0"
    "dataChanged_(QModelIndex,QModelIndex)\0"
    "orient,from,to\0"
    "headerDataChanged_(Qt::Orientation,int,int)\0"
    "layoutChanged_()\0layoutAboutToBeChanged_()\0"
    "parent,from,to\0"
    "rowsAboutToBeInserted_(QModelIndex,int,int)\0"
    "rowsInserted_(QModelIndex,int,int)\0"
    "rowsAboutToBeRemoved_(QModelIndex,int,int)\0"
    "rowsRemoved_(QModelIndex,int,int)\0"
    "columnsAboutToBeInserted_(QModelIndex,int,int)\0"
    "columnsInserted_(QModelIndex,int,int)\0"
    "columnsAboutToBeRemoved_(QModelIndex,int,int)\0"
    "columnsRemoved_(QModelIndex,int,int)\0"
    "modelAboutToBeReset_()\0modelReset_()\0"
    "parent,from,to,dest,row\0"
    "rowsAboutToBeMoved_(QModelIndex,int,int,QModelIndex,int)\0"
    "rowsMoved_(QModelIndex,int,int,QModelIndex,int)\0"
    "parent,from,to,dest,col\0"
    "columnsAboutToBeMoved_(QModelIndex,int,int,QModelIndex,int)\0"
    "columnsMoved_(QModelIndex,int,int,QModelIndex,int)\0"
};

const QMetaObject ivl::qt_details::sort_filter_proxy_model::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_ivl__qt_details__sort_filter_proxy_model,
      qt_meta_data_ivl__qt_details__sort_filter_proxy_model, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::sort_filter_proxy_model::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::sort_filter_proxy_model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::sort_filter_proxy_model::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__sort_filter_proxy_model))
        return static_cast<void*>(const_cast< sort_filter_proxy_model*>(this));
    if (!strcmp(_clname, "method_binder<sort_filter_proxy_model,QSortFilterProxyModel>"))
        return static_cast< method_binder<sort_filter_proxy_model,QSortFilterProxyModel>*>(const_cast< sort_filter_proxy_model*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int ivl::qt_details::sort_filter_proxy_model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataChanged_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 1: headerDataChanged_((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: layoutChanged_(); break;
        case 3: layoutAboutToBeChanged_(); break;
        case 4: rowsAboutToBeInserted_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: rowsInserted_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: rowsAboutToBeRemoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: rowsRemoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: columnsAboutToBeInserted_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: columnsInserted_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: columnsAboutToBeRemoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: columnsRemoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: modelAboutToBeReset_(); break;
        case 13: modelReset_(); break;
        case 14: rowsAboutToBeMoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 15: rowsMoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 16: columnsAboutToBeMoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 17: columnsMoved_((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
