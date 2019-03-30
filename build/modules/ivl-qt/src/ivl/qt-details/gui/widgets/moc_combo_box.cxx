/****************************************************************************
** Meta object code from reading C++ file 'combo_box.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/combo_box.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'combo_box.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__combo_box[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   28,   27,   27, 0x08,
      65,   59,   27,   27, 0x08,
      81,   28,   27,   27, 0x08,
     101,   59,   27,   27, 0x08,
     119,   28,   27,   27, 0x08,
     141,   59,   27,   27, 0x08,
     167,   28,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__combo_box[] = {
    "ivl::qt_details::combo_box\0\0text\0"
    "editTextChanged_(QString)\0index\0"
    "activated_(int)\0activated_(QString)\0"
    "highlighted_(int)\0highlighted_(QString)\0"
    "currentIndexChanged_(int)\0"
    "currentIndexChanged_(QString)\0"
};

const QMetaObject ivl::qt_details::combo_box::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__combo_box,
      qt_meta_data_ivl__qt_details__combo_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::combo_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::combo_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::combo_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__combo_box))
        return static_cast<void*>(const_cast< combo_box*>(this));
    if (!strcmp(_clname, "widget_base<combo_box>"))
        return static_cast< widget_base<combo_box>*>(const_cast< combo_box*>(this));
    if (!strcmp(_clname, "method_binder<combo_box,QComboBox>"))
        return static_cast< method_binder<combo_box,QComboBox>*>(const_cast< combo_box*>(this));
    return QComboBox::qt_metacast(_clname);
}

int ivl::qt_details::combo_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editTextChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: activated_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: activated_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: highlighted_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: highlighted_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: currentIndexChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: currentIndexChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
