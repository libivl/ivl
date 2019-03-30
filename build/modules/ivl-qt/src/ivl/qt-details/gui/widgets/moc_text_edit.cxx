/****************************************************************************
** Meta object code from reading C++ file 'text_edit.hpp'
**
** Created: Sat Jun 15 16:29:42 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/widgets/text_edit.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'text_edit.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__text_edit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   28,   27,   27, 0x08,
      66,   27,   27,   27, 0x08,
      83,   81,   27,   27, 0x08,
     104,   81,   27,   27, 0x08,
     127,  125,   27,   27, 0x08,
     170,   81,   27,   27, 0x08,
     191,   27,   27,   27, 0x08,
     211,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__text_edit[] = {
    "ivl::qt_details::text_edit\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "textChanged_()\0b\0undoAvailable_(bool)\0"
    "redoAvailable_(bool)\0f\0"
    "currentCharFormatChanged_(QTextCharFormat)\0"
    "copyAvailable_(bool)\0selectionChanged_()\0"
    "cursorPositionChanged_()\0"
};

const QMetaObject ivl::qt_details::text_edit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_ivl__qt_details__text_edit,
      qt_meta_data_ivl__qt_details__text_edit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::text_edit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::text_edit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::text_edit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__text_edit))
        return static_cast<void*>(const_cast< text_edit*>(this));
    if (!strcmp(_clname, "widget_base<text_edit>"))
        return static_cast< widget_base<text_edit>*>(const_cast< text_edit*>(this));
    if (!strcmp(_clname, "method_binder<text_edit,QTextEdit>"))
        return static_cast< method_binder<text_edit,QTextEdit>*>(const_cast< text_edit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int ivl::qt_details::text_edit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: textChanged_(); break;
        case 2: undoAvailable_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: redoAvailable_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: currentCharFormatChanged_((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 5: copyAvailable_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: selectionChanged_(); break;
        case 7: cursorPositionChanged_(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
