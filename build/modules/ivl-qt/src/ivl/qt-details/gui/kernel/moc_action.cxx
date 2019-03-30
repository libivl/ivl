/****************************************************************************
** Meta object code from reading C++ file 'action.hpp'
**
** Created: Sat Jun 15 16:14:39 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/kernel/action.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'action.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__action[] = {

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
      25,   24,   24,   24, 0x08,
      44,   36,   24,   24, 0x08,
      61,   24,   24,   24, 0x08,
      72,   36,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__action[] = {
    "ivl::qt_details::action\0\0changed_()\0"
    "checked\0triggered_(bool)\0hovered_()\0"
    "toggled_(bool)\0"
};

const QMetaObject ivl::qt_details::action::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_ivl__qt_details__action,
      qt_meta_data_ivl__qt_details__action, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::action::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::action::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::action::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__action))
        return static_cast<void*>(const_cast< action*>(this));
    if (!strcmp(_clname, "method_binder<action,QAction>"))
        return static_cast< method_binder<action,QAction>*>(const_cast< action*>(this));
    return QAction::qt_metacast(_clname);
}

int ivl::qt_details::action::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed_(); break;
        case 1: triggered_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: hovered_(); break;
        case 3: toggled_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
