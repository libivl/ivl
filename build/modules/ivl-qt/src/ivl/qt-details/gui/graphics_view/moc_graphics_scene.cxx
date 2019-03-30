/****************************************************************************
** Meta object code from reading C++ file 'graphics_scene.hpp'
**
** Created: Sat Jun 15 16:17:44 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../modules/ivl-qt/src/ivl/qt-details/gui/graphics_view/graphics_scene.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphics_scene.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ivl__qt_details__graphics_scene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   33,   32,   32, 0x08,
      69,   64,   32,   32, 0x08,
      95,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ivl__qt_details__graphics_scene[] = {
    "ivl::qt_details::graphics_scene\0\0"
    "region\0changed_(QList<QRectF>)\0rect\0"
    "sceneRectChanged_(QRectF)\0selectionChanged_()\0"
};

const QMetaObject ivl::qt_details::graphics_scene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_ivl__qt_details__graphics_scene,
      qt_meta_data_ivl__qt_details__graphics_scene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ivl::qt_details::graphics_scene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ivl::qt_details::graphics_scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ivl::qt_details::graphics_scene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ivl__qt_details__graphics_scene))
        return static_cast<void*>(const_cast< graphics_scene*>(this));
    if (!strcmp(_clname, "method_binder<graphics_scene,QGraphicsScene>"))
        return static_cast< method_binder<graphics_scene,QGraphicsScene>*>(const_cast< graphics_scene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int ivl::qt_details::graphics_scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed_((*reinterpret_cast< const QList<QRectF>(*)>(_a[1]))); break;
        case 1: sceneRectChanged_((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 2: selectionChanged_(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
