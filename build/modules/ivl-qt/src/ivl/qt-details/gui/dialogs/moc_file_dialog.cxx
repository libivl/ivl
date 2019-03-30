/****************************************************************************
** Meta object code from reading C++ file 'file_dialog.hpp'
**
** Created: Tue Jun 18 00:47:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/dialogs/file_dialog.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file_dialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__file_dialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   30,   29,   29, 0x08,
      70,   68,   29,   29, 0x08,
      85,   29,   29,   29, 0x08,
      97,   29,   29,   29, 0x08,
     114,  109,   29,   29, 0x08,
     143,  137,   29,   29, 0x08,
     176,  171,   29,   29, 0x08,
     211,  201,   29,   29, 0x08,
     245,  238,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__file_dialog[] = {
    "ivl::qt_details::file_dialog\0\0p\0"
    "customContextMenuRequested_(QPoint)\0"
    "i\0finished_(int)\0accepted_()\0rejected_()\0"
    "file\0fileSelected_(QString)\0files\0"
    "filesSelected_(QStringList)\0path\0"
    "currentChanged_(QString)\0directory\0"
    "directoryEntered_(QString)\0filter\0"
    "filterSelected_(QString)\0"
};

const QMetaObject ivl::qt_details::file_dialog::staticMetaObject = {
    { &QFileDialog::staticMetaObject, qt_meta_stringdata_ivl__qt_details__file_dialog,
      qt_meta_data_ivl__qt_details__file_dialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::file_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::file_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::file_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__file_dialog))
        return static_cast<void*>(const_cast< file_dialog*>(this));
    if (!strcmp(_clname, "widget_base<file_dialog>"))
        return static_cast< widget_base<file_dialog>*>(const_cast< file_dialog*>(this));
    if (!strcmp(_clname, "method_binder<file_dialog,QFileDialog>"))
        return static_cast< method_binder<file_dialog,QFileDialog>*>(const_cast< file_dialog*>(this));
    return QFileDialog::qt_metacast(_clname);
}

int ivl::qt_details::file_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFileDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested_((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: finished_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: accepted_(); break;
        case 3: rejected_(); break;
        case 4: fileSelected_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: filesSelected_((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: currentChanged_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: directoryEntered_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: filterSelected_((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
