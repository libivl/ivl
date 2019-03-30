/****************************************************************************
** Meta object code from reading C++ file 'spin_box.hpp'
**
** Created: Wed Jun 19 01:44:13 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/spin_box.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spin_box.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__spin_box[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   27,   26,   26, 0x08,
      65,   26,   26,   26, 0x08,
      86,   84,   26,   26, 0x08,
     107,  105,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__spin_box[] = {
    "ivl::qt_details::spin_box\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "editingFinished_()\0v\0valueChanged_(int)\0"
    "s\0valueChanged_(QString)\0"
};

const QMetaObject ivl::qt_details::spin_box::staticMetaObject = {
    { &QSpinBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__spin_box,
      qt_meta_data_ivl__qt_details__spin_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::spin_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::spin_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::spin_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__spin_box))
        return static_cast<void*>(const_cast< spin_box*>(this));
    if (!strcmp(_clname, "widget_base<spin_box>"))
        return static_cast< widget_base<spin_box>*>(const_cast< spin_box*>(this));
    if (!strcmp(_clname, "method_binder<spin_box,QSpinBox>"))
        return static_cast< method_binder<spin_box,QSpinBox>*>(const_cast< spin_box*>(this));
    return QSpinBox::qt_metacast(_clname);
}

int ivl::qt_details::spin_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: editingFinished_(); break;
        case 2: valueChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: valueChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_ivl__qt_details__double_spin_box[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   34,   33,   33, 0x08,
      72,   33,   33,   33, 0x08,
      93,   91,   33,   33, 0x08,
     117,  115,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__double_spin_box[] = {
    "ivl::qt_details::double_spin_box\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "editingFinished_()\0v\0valueChanged_(double)\0"
    "s\0valueChanged_(QString)\0"
};

const QMetaObject ivl::qt_details::double_spin_box::staticMetaObject = {
    { &QDoubleSpinBox::staticMetaObject, qt_meta_stringdata_ivl__qt_details__double_spin_box,
      qt_meta_data_ivl__qt_details__double_spin_box, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::double_spin_box::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::double_spin_box::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::double_spin_box::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__double_spin_box))
        return static_cast<void*>(const_cast< double_spin_box*>(this));
    if (!strcmp(_clname, "method_binder<double_spin_box,QDoubleSpinBox,QAbstractSpinBox>"))
        return static_cast< method_binder<double_spin_box,QDoubleSpinBox,QAbstractSpinBox>*>(const_cast< double_spin_box*>(this));
    return QDoubleSpinBox::qt_metacast(_clname);
}

int ivl::qt_details::double_spin_box::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: editingFinished_(); break;
        case 2: valueChanged_((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: valueChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
