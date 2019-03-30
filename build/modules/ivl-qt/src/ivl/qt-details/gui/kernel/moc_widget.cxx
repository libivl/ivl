/****************************************************************************
** Meta object code from reading C++ file 'widget.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/kernel/widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   25,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__widget[] = {
    "ivl::qt_details::widget\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
};

const QMetaObject ivl::qt_details::widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ivl__qt_details__widget,
      qt_meta_data_ivl__qt_details__widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__widget))
        return static_cast<void*>(const_cast< widget*>(this));
    if (!strcmp(_clname, "widget_base<widget>"))
        return static_cast< widget_base<widget>*>(const_cast< widget*>(this));
    if (!strcmp(_clname, "method_binder<widget,QWidget>"))
        return static_cast< method_binder<widget,QWidget>*>(const_cast< widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ivl::qt_details::widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
