/****************************************************************************
** Meta object code from reading C++ file 'tool_button.hpp'
**
** Created: Sun Jun 16 14:01:42 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/tool_button.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tool_button.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__tool_button[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   30,   29,   29, 0x08,
      68,   29,   29,   29, 0x08,
      79,   29,   29,   29, 0x08,
      99,   91,   29,   29, 0x08,
     114,   91,   29,   29, 0x08,
     131,  129,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__tool_button[] = {
    "ivl::qt_details::tool_button\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "pressed_()\0released_()\0checked\0"
    "clicked_(bool)\0toggled_(bool)\0a\0"
    "triggered_(QAction*)\0"
};

const QMetaObject ivl::qt_details::tool_button::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_ivl__qt_details__tool_button,
      qt_meta_data_ivl__qt_details__tool_button, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::tool_button::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::tool_button::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::tool_button::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__tool_button))
        return static_cast<void*>(const_cast< tool_button*>(this));
    if (!strcmp(_clname, "widget_base<tool_button>"))
        return static_cast< widget_base<tool_button>*>(const_cast< tool_button*>(this));
    if (!strcmp(_clname, "method_binder<tool_button,QToolButton,QAbstractButton>"))
        return static_cast< method_binder<tool_button,QToolButton,QAbstractButton>*>(const_cast< tool_button*>(this));
    return QToolButton::qt_metacast(_clname);
}

int ivl::qt_details::tool_button::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: pressed_(); break;
        case 2: released_(); break;
        case 3: clicked_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: toggled_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: triggered_((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
