/****************************************************************************
** Meta object code from reading C++ file 'plotfromfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI_for_CHAI/plotfromfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotfromfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlotFromFile_t {
    QByteArrayData data[19];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotFromFile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotFromFile_t qt_meta_stringdata_PlotFromFile = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PlotFromFile"
QT_MOC_LITERAL(1, 13, 10), // "openWindow"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "OpenFileSystem"
QT_MOC_LITERAL(4, 40, 14), // "CreateNewGraph"
QT_MOC_LITERAL(5, 55, 9), // "graphName"
QT_MOC_LITERAL(6, 65, 5), // "color"
QT_MOC_LITERAL(7, 71, 20), // "on_Scale_sliderMoved"
QT_MOC_LITERAL(8, 92, 8), // "position"
QT_MOC_LITERAL(9, 101, 27), // "on_xAxisReplace_sliderMoved"
QT_MOC_LITERAL(10, 129, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(11, 153, 4), // "arg1"
QT_MOC_LITERAL(12, 158, 21), // "on_SaveButton_clicked"
QT_MOC_LITERAL(13, 180, 11), // "getPlotFile"
QT_MOC_LITERAL(14, 192, 8), // "fileName"
QT_MOC_LITERAL(15, 201, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(16, 223, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(17, 247, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(18, 271, 21) // "on_OpenButton_clicked"

    },
    "PlotFromFile\0openWindow\0\0OpenFileSystem\0"
    "CreateNewGraph\0graphName\0color\0"
    "on_Scale_sliderMoved\0position\0"
    "on_xAxisReplace_sliderMoved\0"
    "on_spinBox_valueChanged\0arg1\0"
    "on_SaveButton_clicked\0getPlotFile\0"
    "fileName\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_OpenButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotFromFile[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   76,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
       9,    1,   84,    2, 0x08 /* Private */,
      10,    1,   87,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,
      17,    0,   96,    2, 0x08 /* Private */,
      18,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Int,
    QMetaType::Int,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlotFromFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlotFromFile *_t = static_cast<PlotFromFile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->openWindow();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->OpenFileSystem();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: _t->CreateNewGraph((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->on_Scale_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_xAxisReplace_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_SaveButton_clicked(); break;
        case 7: _t->getPlotFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        case 10: _t->on_pushButton_3_clicked(); break;
        case 11: _t->on_OpenButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (PlotFromFile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlotFromFile::openWindow)) {
                *result = 0;
                return;
            }
        }
        {
            typedef int (PlotFromFile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlotFromFile::OpenFileSystem)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PlotFromFile::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PlotFromFile.data,
      qt_meta_data_PlotFromFile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlotFromFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotFromFile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlotFromFile.stringdata0))
        return static_cast<void*>(const_cast< PlotFromFile*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PlotFromFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
int PlotFromFile::openWindow()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int PlotFromFile::OpenFileSystem()
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
