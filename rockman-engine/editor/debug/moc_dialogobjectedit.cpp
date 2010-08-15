/****************************************************************************
** Meta object code from reading C++ file 'dialogobjectedit.h'
**
** Created: Wed Aug 11 19:49:18 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogobjectedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogobjectedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogObjectEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   17,   17,   17, 0x0a,
      58,   17,   17,   17, 0x08,
      82,   17,   17,   17, 0x08,
     133,   17,   17,   17, 0x08,
     175,   17,   17,   17, 0x08,
     217,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogObjectEdit[] = {
    "DialogObjectEdit\0\0finishedObjectEditor()\0"
    "setObjectFrame()\0on_buttonBox_rejected()\0"
    "on_objectListCombobox_currentIndexChanged(QString)\0"
    "on_npcGraphicSizeSpin_h_valueChanged(int)\0"
    "on_npcGraphicSizeSpin_w_valueChanged(int)\0"
    "on_buttonBox_accepted()\0"
};

const QMetaObject DialogObjectEdit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogObjectEdit,
      qt_meta_data_DialogObjectEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogObjectEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogObjectEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogObjectEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogObjectEdit))
        return static_cast<void*>(const_cast< DialogObjectEdit*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogObjectEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finishedObjectEditor(); break;
        case 1: setObjectFrame(); break;
        case 2: on_buttonBox_rejected(); break;
        case 3: on_objectListCombobox_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: on_npcGraphicSizeSpin_h_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_npcGraphicSizeSpin_w_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_buttonBox_accepted(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DialogObjectEdit::finishedObjectEditor()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
