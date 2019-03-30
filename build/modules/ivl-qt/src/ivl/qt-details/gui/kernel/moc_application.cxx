/****************************************************************************
** Meta object code from reading C++ file 'application.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/kernel/application.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__application[] = {

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
      30,   29,   29,   29, 0x08,
      47,   45,   29,   29, 0x08,
      64,   29,   29,   29, 0x08,
      92,   84,   29,   29, 0x08,
     125,   29,   29,   29, 0x08,
     150,  148,   29,   29, 0x08,
     187,  148,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__application[] = {
    "ivl::qt_details::application\0\0"
    "aboutToQuit_()\0i\0unixSignal_(int)\0"
    "lastWindowClosed_()\0old,now\0"
    "focusChanged_(QWidget*,QWidget*)\0"
    "fontDatabaseChanged_()\0m\0"
    "commitDataRequest_(QSessionManager&)\0"
    "saveStateRequest_(QSessionManager&)\0"
};

const QMetaObject ivl::qt_details::application::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_ivl__qt_details__application,
      qt_meta_data_ivl__qt_details__application, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::application::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__application))
        return static_cast<void*>(const_cast< application*>(this));
    if (!strcmp(_clname, "method_binder<application,QApplication,QCoreApplication>"))
        return static_cast< method_binder<application,QApplication,QCoreApplication>*>(const_cast< application*>(this));
    return QApplication::qt_metacast(_clname);
}

int ivl::qt_details::application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: aboutToQuit_(); break;
        case 1: unixSignal_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: lastWindowClosed_(); break;
        case 3: focusChanged_((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 4: fontDatabaseChanged_(); break;
        case 5: commitDataRequest_((*reinterpret_cast< QSessionManager(*)>(_a[1]))); break;
        case 6: saveStateRequest_((*reinterpret_cast< QSessionManager(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
