/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/main_window.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__main_window[] = {

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
      32,   30,   29,   29, 0x08,
      70,   68,   29,   29, 0x08,
      94,   68,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__main_window[] = {
    "ivl::qt_details::main_window\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "s\0iconSizeChanged_(QSize)\0"
    "toolButtonStyleChanged_(Qt::ToolButtonStyle)\0"
};

const QMetaObject ivl::qt_details::main_window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ivl__qt_details__main_window,
      qt_meta_data_ivl__qt_details__main_window, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::main_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::main_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::main_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__main_window))
        return static_cast<void*>(const_cast< main_window*>(this));
    if (!strcmp(_clname, "widget_base<main_window>"))
        return static_cast< widget_base<main_window>*>(const_cast< main_window*>(this));
    if (!strcmp(_clname, "method_binder<main_window,QMainWindow>"))
        return static_cast< method_binder<main_window,QMainWindow>*>(const_cast< main_window*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ivl::qt_details::main_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: iconSizeChanged_((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 2: toolButtonStyleChanged_((*reinterpret_cast< Qt::ToolButtonStyle(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
