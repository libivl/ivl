/****************************************************************************
** Meta object code from reading C++ file 'slider.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/slider.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slider.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__slider[] = {

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
      27,   25,   24,   24, 0x08,
      69,   63,   24,   24, 0x08,
      88,   24,   24,   24, 0x08,
     114,  105,   24,   24, 0x08,
     132,   24,   24,   24, 0x08,
     158,  150,   24,   24, 0x08,
     188,  181,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__slider[] = {
    "ivl::qt_details::slider\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "value\0valueChanged_(int)\0sliderPressed_()\0"
    "position\0sliderMoved_(int)\0sliderReleased_()\0"
    "min,max\0rangeChanged_(int,int)\0action\0"
    "actionTriggered_(int)\0"
};

const QMetaObject ivl::qt_details::slider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_ivl__qt_details__slider,
      qt_meta_data_ivl__qt_details__slider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::slider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::slider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::slider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__slider))
        return static_cast<void*>(const_cast< slider*>(this));
    if (!strcmp(_clname, "widget_base<slider>"))
        return static_cast< widget_base<slider>*>(const_cast< slider*>(this));
    if (!strcmp(_clname, "method_binder<slider,QSlider,QAbstractSlider>"))
        return static_cast< method_binder<slider,QSlider,QAbstractSlider>*>(const_cast< slider*>(this));
    return QSlider::qt_metacast(_clname);
}

int ivl::qt_details::slider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: valueChanged_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: sliderPressed_(); break;
        case 3: sliderMoved_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sliderReleased_(); break;
        case 5: rangeChanged_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: actionTriggered_((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
