/****************************************************************************
** Meta object code from reading C++ file 'dialog_button_box.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/dialog_button_box.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_button_box.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__dialog_button_box[] = {

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
      38,   36,   35,   35, 0x08,
      76,   74,   35,   35, 0x08,
     103,   35,   35,   35, 0x08,
     115,   35,   35,   35, 0x08,
     132,   35,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__dialog_button_box[] = {
    "ivl::qt_details::dialog_button_box\0\0"
    "p\0customContextMenuRequested_(QPoint)\0"
    "b\0clicked_(QAbstractButton*)\0accepted_()\0"
    "helpRequested_()\0rejected_()\0"
};

const QMetaObject ivl::qt_details::dialog_button_box::staticMetaObject = {
    { &QDialogButtonBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__dialog_button_box,
      qt_meta_data_ivl__qt_details__dialog_button_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::dialog_button_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::dialog_button_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::dialog_button_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__dialog_button_box))
        return static_cast<void*>(const_cast< dialog_button_box*>(this));
    if (!strcmp(_clname, "widget_base<dialog_button_box>"))
        return static_cast< widget_base<dialog_button_box>*>(const_cast< dialog_button_box*>(this));
    if (!strcmp(_clname, "method_binder<dialog_button_box,QDialogButtonBox>"))
        return static_cast< method_binder<dialog_button_box,QDialogButtonBox>*>(const_cast< dialog_button_box*>(this));
    return QDialogButtonBox::qt_metacast(_clname);
}

int ivl::qt_details::dialog_button_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialogButtonBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: clicked_((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: accepted_(); break;
        case 3: helpRequested_(); break;
        case 4: rejected_(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
