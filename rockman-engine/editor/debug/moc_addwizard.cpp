/****************************************************************************
** Meta object code from reading C++ file 'addwizard.h'
**
** Created: Wed Aug 11 19:49:14 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../addwizard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addwizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_addWizard[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   10,   10,   10, 0x08,
      76,   10,   10,   10, 0x08,
     116,   10,   10,   10, 0x08,
     156,  153,   10,   10, 0x08,
     177,   10,  173,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_addWizard[] = {
    "addWizard\0\0finishedWizard()\0"
    "on_npcListCombobox_currentIndexChanged(QString)\0"
    "on_npcGraphicSizeSpin_valueChanged(int)\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "id\0pageChanged(int)\0int\0nextId()\0"
};

const QMetaObject addWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_addWizard,
      qt_meta_data_addWizard, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &addWizard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *addWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *addWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_addWizard))
        return static_cast<void*>(const_cast< addWizard*>(this));
    return QWizard::qt_metacast(_clname);
}

int addWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finishedWizard(); break;
        case 1: on_npcListCombobox_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: on_npcGraphicSizeSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: pageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { int _r = nextId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void addWizard::finishedWizard()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
