/****************************************************************************
** Meta object code from reading C++ file 'menu.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/menu.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__menu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   23,   22,   22, 0x08,
      61,   22,   22,   22, 0x08,
      76,   22,   22,   22, 0x08,
      93,   91,   22,   22, 0x08,
     114,   91,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__menu[] = {
    "ivl::qt_details::menu\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "aboutToShow_()\0aboutToHide_()\0a\0"
    "triggered_(QAction*)\0hovered_(QAction*)\0"
};

const QMetaObject ivl::qt_details::menu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_ivl__qt_details__menu,
      qt_meta_data_ivl__qt_details__menu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::menu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::menu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::menu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__menu))
        return static_cast<void*>(const_cast< menu*>(this));
    if (!strcmp(_clname, "widget_base<menu>"))
        return static_cast< widget_base<menu>*>(const_cast< menu*>(this));
    if (!strcmp(_clname, "method_binder<menu,QMenu>"))
        return static_cast< method_binder<menu,QMenu>*>(const_cast< menu*>(this));
    return QMenu::qt_metacast(_clname);
}

int ivl::qt_details::menu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: aboutToShow_(); break;
        case 2: aboutToHide_(); break;
        case 3: triggered_((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: hovered_((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
