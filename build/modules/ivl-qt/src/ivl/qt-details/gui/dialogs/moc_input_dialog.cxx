/****************************************************************************
** Meta object code from reading C++ file 'input_dialog.hpp'
**
** Created: Tue Jun 18 00:47:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/dialogs/input_dialog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'input_dialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__input_dialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   31,   30,   30, 0x08,
      71,   69,   30,   30, 0x08,
      86,   30,   30,   30, 0x08,
      98,   30,   30,   30, 0x08,
     115,  110,   30,   30, 0x08,
     142,  110,   30,   30, 0x08,
     176,  170,   30,   30, 0x08,
     198,  170,   30,   30, 0x08,
     221,  170,   30,   30, 0x08,
     249,  170,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__input_dialog[] = {
    "ivl::qt_details::input_dialog\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "i\0finished_(int)\0accepted_()\0rejected_()\0"
    "text\0textValueChanged_(QString)\0"
    "textValueSelected_(QString)\0value\0"
    "intValueChanged_(int)\0intValueSelected_(int)\0"
    "doubleValueChanged_(double)\0"
    "doubleValueSelected_(double)\0"
};

const QMetaObject ivl::qt_details::input_dialog::staticMetaObject = {
    { &QInputDialog::staticMetaObject, qt_meta_stringdata_ivl__qt_details__input_dialog,
      qt_meta_data_ivl__qt_details__input_dialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::input_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::input_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::input_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__input_dialog))
        return static_cast<void*>(const_cast< input_dialog*>(this));
    if (!strcmp(_clname, "widget_base<input_dialog>"))
        return static_cast< widget_base<input_dialog>*>(const_cast< input_dialog*>(this));
    if (!strcmp(_clname, "method_binder<input_dialog,QInputDialog>"))
        return static_cast< method_binder<input_dialog,QInputDialog>*>(const_cast< input_dialog*>(this));
    return QInputDialog::qt_metacast(_clname);
}

int ivl::qt_details::input_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: finished_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: accepted_(); break;
        case 3: rejected_(); break;
        case 4: textValueChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: textValueSelected_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: intValueChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: intValueSelected_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: doubleValueChanged_((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: doubleValueSelected_((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
