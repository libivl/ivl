/****************************************************************************
** Meta object code from reading C++ file 'tool_bar.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/tool_bar.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tool_bar.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__tool_bar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   27,   26,   26, 0x08,
      72,   65,   26,   26, 0x08,
     107,   99,   26,   26, 0x08,
     135,  129,   26,   26, 0x08,
     186,  174,   26,   26, 0x08,
     232,  223,   26,   26, 0x08,
     262,  256,   26,   26, 0x08,
     316,  307,   26,   26, 0x08,
     347,  339,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__tool_bar[] = {
    "ivl::qt_details::tool_bar\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "action\0actionTriggered_(QAction*)\0"
    "movable\0movableChanged_(bool)\0areas\0"
    "allowedAreasChanged_(Qt::ToolBarAreas)\0"
    "orientation\0orientationChanged_(Qt::Orientation)\0"
    "iconSize\0iconSizeChanged_(QSize)\0style\0"
    "toolButtonStyleChanged_(Qt::ToolButtonStyle)\0"
    "topLevel\0topLevelChanged_(bool)\0visible\0"
    "visibilityChanged_(bool)\0"
};

const QMetaObject ivl::qt_details::tool_bar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_ivl__qt_details__tool_bar,
      qt_meta_data_ivl__qt_details__tool_bar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::tool_bar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::tool_bar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::tool_bar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__tool_bar))
        return static_cast<void*>(const_cast< tool_bar*>(this));
    if (!strcmp(_clname, "widget_base<tool_bar>"))
        return static_cast< widget_base<tool_bar>*>(const_cast< tool_bar*>(this));
    if (!strcmp(_clname, "method_binder<tool_bar,QToolBar>"))
        return static_cast< method_binder<tool_bar,QToolBar>*>(const_cast< tool_bar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int ivl::qt_details::tool_bar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: actionTriggered_((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: movableChanged_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: allowedAreasChanged_((*reinterpret_cast< Qt::ToolBarAreas(*)>(_a[1]))); break;
        case 4: orientationChanged_((*reinterpret_cast< Qt::Orientation(*)>(_a[1]))); break;
        case 5: iconSizeChanged_((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 6: toolButtonStyleChanged_((*reinterpret_cast< Qt::ToolButtonStyle(*)>(_a[1]))); break;
        case 7: topLevelChanged_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: visibilityChanged_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
