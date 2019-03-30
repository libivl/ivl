/****************************************************************************
** Meta object code from reading C++ file 'line_edit.hpp'
**
** Created: Wed Jun 12 23:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/line_edit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'line_edit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__line_edit[] = {

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
      30,   28,   27,   27, 0x08,
      68,   66,   27,   27, 0x08,
      90,   66,   27,   27, 0x08,
     117,  111,   27,   27, 0x08,
     149,   27,   27,   27, 0x08,
     166,   27,   27,   27, 0x08,
     185,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__line_edit[] = {
    "ivl::qt_details::line_edit\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "s\0textChanged_(QString)\0textEdited_(QString)\0"
    "i1,i2\0cursorPositionChanged_(int,int)\0"
    "returnPressed_()\0editingFinished_()\0"
    "selectionChanged_()\0"
};

const QMetaObject ivl::qt_details::line_edit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_ivl__qt_details__line_edit,
      qt_meta_data_ivl__qt_details__line_edit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::line_edit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::line_edit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::line_edit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__line_edit))
        return static_cast<void*>(const_cast< line_edit*>(this));
    if (!strcmp(_clname, "widget_base<line_edit>"))
        return static_cast< widget_base<line_edit>*>(const_cast< line_edit*>(this));
    if (!strcmp(_clname, "method_binder<line_edit,QLineEdit>"))
        return static_cast< method_binder<line_edit,QLineEdit>*>(const_cast< line_edit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int ivl::qt_details::line_edit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: textChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: textEdited_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: cursorPositionChanged_((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: returnPressed_(); break;
        case 5: editingFinished_(); break;
        case 6: selectionChanged_(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
