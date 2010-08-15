/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Aug 11 19:49:11 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x08,
      62,   11,   11,   11, 0x08,
      92,   86,   11,   11, 0x08,
     123,   12,   11,   11, 0x08,
     166,   11,   11,   11, 0x08,
     196,   86,   11,   11, 0x08,
     237,   11,   11,   11, 0x08,
     266,   86,   11,   11, 0x08,
     305,   11,   11,   11, 0x08,
     337,   11,   11,   11, 0x08,
     364,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x08,
     414,   11,   11,   11, 0x08,
     440,   11,   11,   11, 0x08,
     467,   12,   11,   11, 0x08,
     504,   11,   11,   11, 0x08,
     538,   11,   11,   11, 0x08,
     568,   86,   11,   11, 0x08,
     605,   11,   11,   11, 0x08,
     633,   11,   11,   11, 0x08,
     659,   11,   11,   11, 0x08,
     694,  685,   11,   11, 0x08,
     731,   11,   11,   11, 0x08,
     756,   11,   11,   11, 0x08,
     782,   11,   11,   11, 0x08,
     810,   11,   11,   11, 0x08,
     843,   11,   11,   11, 0x08,
     874,   11,   11,   11, 0x08,
     908,   11,   11,   11, 0x08,
     934,   11,   11,   11, 0x08,
     960,   11,   11,   11, 0x08,
     986,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0currentRow\0"
    "on_listWidget_2_currentRowChanged(int)\0"
    "on_pushButton_clicked()\0index\0"
    "on_toolBox_currentChanged(int)\0"
    "on_objectListWidget_currentRowChanged(int)\0"
    "on_editObjectButton_clicked()\0"
    "on_mapListCombo_currentIndexChanged(int)\0"
    "on_newObjectButton_clicked()\0"
    "on_comboBox_2_currentIndexChanged(int)\0"
    "on_actionAdd_Object_triggered()\0"
    "on_actionThree_triggered()\0"
    "on_actionTwo_triggered()\0"
    "on_actionOne_triggered()\0"
    "on_newNPCButton_clicked()\0"
    "on_editNPCButton_clicked()\0"
    "on_listWidget_currentRowChanged(int)\0"
    "on_actionEdit_Tileset_triggered()\0"
    "on_actionEdit_NPC_triggered()\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "on_actionStairs_triggered()\0"
    "on_addNpcButton_clicked()\0"
    "on_actionLink_triggered()\0iconSize\0"
    "on_MainWindow_iconSizeChanged(QSize)\0"
    "on_actionNew_triggered()\0"
    "on_actionFill_triggered()\0"
    "on_actionEraser_triggered()\0"
    "on_actionNormal_Edit_triggered()\0"
    "on_actionLock_Edit_triggered()\0"
    "on_pallete_signalPalleteChanged()\0"
    "on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionQuit_triggered()\0reloadComboItems()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_listWidget_2_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_pushButton_clicked(); break;
        case 2: on_toolBox_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_objectListWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_editObjectButton_clicked(); break;
        case 5: on_mapListCombo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_newObjectButton_clicked(); break;
        case 7: on_comboBox_2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: on_actionAdd_Object_triggered(); break;
        case 9: on_actionThree_triggered(); break;
        case 10: on_actionTwo_triggered(); break;
        case 11: on_actionOne_triggered(); break;
        case 12: on_newNPCButton_clicked(); break;
        case 13: on_editNPCButton_clicked(); break;
        case 14: on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: on_actionEdit_Tileset_triggered(); break;
        case 16: on_actionEdit_NPC_triggered(); break;
        case 17: on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: on_actionStairs_triggered(); break;
        case 19: on_addNpcButton_clicked(); break;
        case 20: on_actionLink_triggered(); break;
        case 21: on_MainWindow_iconSizeChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 22: on_actionNew_triggered(); break;
        case 23: on_actionFill_triggered(); break;
        case 24: on_actionEraser_triggered(); break;
        case 25: on_actionNormal_Edit_triggered(); break;
        case 26: on_actionLock_Edit_triggered(); break;
        case 27: on_pallete_signalPalleteChanged(); break;
        case 28: on_actionOpen_triggered(); break;
        case 29: on_actionSave_triggered(); break;
        case 30: on_actionQuit_triggered(); break;
        case 31: reloadComboItems(); break;
        default: ;
        }
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
