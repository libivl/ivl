/****************************************************************************
** Meta object code from reading C++ file 'message_box.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/dialogs/message_box.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'message_box.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__message_box[] = {

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
      32,   30,   29,   29, 0x08,
      70,   68,   29,   29, 0x08,
      85,   29,   29,   29, 0x08,
      97,   29,   29,   29, 0x08,
     116,  109,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__message_box[] = {
    "ivl::qt_details::message_box\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "i\0finished_(int)\0accepted_()\0rejected_()\0"
    "button\0buttonClicked_(QAbstractButton*)\0"
};

const QMetaObject ivl::qt_details::message_box::staticMetaObject = {
    { &QMessageBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__message_box,
      qt_meta_data_ivl__qt_details__message_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::message_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::message_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::message_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__message_box))
        return static_cast<void*>(const_cast< message_box*>(this));
    if (!strcmp(_clname, "widget_base<message_box>"))
        return static_cast< widget_base<message_box>*>(const_cast< message_box*>(this));
    if (!strcmp(_clname, "method_binder<message_box,QMessageBox>"))
        return static_cast< method_binder<message_box,QMessageBox>*>(const_cast< message_box*>(this));
    return QMessageBox::qt_metacast(_clname);
}

int ivl::qt_details::message_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMessageBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: finished_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: accepted_(); break;
        case 3: rejected_(); break;
        case 4: buttonClicked_((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
