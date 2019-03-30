/****************************************************************************
** Meta object code from reading C++ file 'date_time_edit.hpp'
**
** Created: Wed Jun 19 01:44:13 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/date_time_edit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'date_time_edit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__date_time_edit[] = {

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
      35,   33,   32,   32, 0x08,
      71,   32,   32,   32, 0x08,
      95,   90,   32,   32, 0x08,
     123,   90,   32,   32, 0x08,
     143,   90,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__date_time_edit[] = {
    "ivl::qt_details::date_time_edit\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "editingFinished_()\0date\0"
    "dateTimeChanged_(QDateTime)\0"
    "timeChanged_(QTime)\0dateChanged_(QDate)\0"
};

const QMetaObject ivl::qt_details::date_time_edit::staticMetaObject = {
    { &QDateTimeEdit::staticMetaObject, qt_meta_stringdata_ivl__qt_details__date_time_edit,
      qt_meta_data_ivl__qt_details__date_time_edit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::date_time_edit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::date_time_edit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::date_time_edit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__date_time_edit))
        return static_cast<void*>(const_cast< date_time_edit*>(this));
    if (!strcmp(_clname, "widget_base<date_time_edit>"))
        return static_cast< widget_base<date_time_edit>*>(const_cast< date_time_edit*>(this));
    if (!strcmp(_clname, "method_binder<date_time_edit,QDateTimeEdit>"))
        return static_cast< method_binder<date_time_edit,QDateTimeEdit>*>(const_cast< date_time_edit*>(this));
    return QDateTimeEdit::qt_metacast(_clname);
}

int ivl::qt_details::date_time_edit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDateTimeEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: editingFinished_(); break;
        case 2: dateTimeChanged_((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 3: timeChanged_((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 4: dateChanged_((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
