/****************************************************************************
** Meta object code from reading C++ file 'dock_widget.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/dock_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dock_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__dock_widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   30,   29,   29, 0x08,
      77,   68,   29,   29, 0x08,
     137,  127,   29,   29, 0x08,
     174,  160,   29,   29, 0x08,
     224,  216,   29,   29, 0x08,
     254,  249,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__dock_widget[] = {
    "ivl::qt_details::dock_widget\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "features\0featuresChanged_(QDockWidget::DockWidgetFeatures)\0"
    "top_level\0topLevelChanged_(bool)\0"
    "allowed_areas\0allowedAreasChanged_(Qt::DockWidgetAreas)\0"
    "visible\0visibilityChanged_(bool)\0area\0"
    "dockLocationChanged_(Qt::DockWidgetArea)\0"
};

const QMetaObject ivl::qt_details::dock_widget::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ivl__qt_details__dock_widget,
      qt_meta_data_ivl__qt_details__dock_widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::dock_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::dock_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::dock_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__dock_widget))
        return static_cast<void*>(const_cast< dock_widget*>(this));
    if (!strcmp(_clname, "widget_base<dock_widget>"))
        return static_cast< widget_base<dock_widget>*>(const_cast< dock_widget*>(this));
    if (!strcmp(_clname, "method_binder<dock_widget,QDockWidget>"))
        return static_cast< method_binder<dock_widget,QDockWidget>*>(const_cast< dock_widget*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ivl::qt_details::dock_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: featuresChanged_((*reinterpret_cast< QDockWidget::DockWidgetFeatures(*)>(_a[1]))); break;
        case 2: topLevelChanged_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: allowedAreasChanged_((*reinterpret_cast< Qt::DockWidgetAreas(*)>(_a[1]))); break;
        case 4: visibilityChanged_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: dockLocationChanged_((*reinterpret_cast< Qt::DockWidgetArea(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
