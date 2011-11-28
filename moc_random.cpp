/****************************************************************************
** Meta object code from reading C++ file 'random.h'
**
** Created: Sun Nov 6 10:53:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "random.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'random.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyQWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      31,   29,   10,   10, 0x08,
      45,   10,   10,   10, 0x08,
      58,   10,   10,   10, 0x08,
      69,   10,   10,   10, 0x08,
      82,   10,   10,   10, 0x08,
      95,   29,   10,   10, 0x08,
     108,   10,   10,   10, 0x08,
     122,   10,   10,   10, 0x08,
     134,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyQWidget[] = {
    "MyQWidget\0\0setOpenFileName()\0x\0"
    "openFile(int)\0randomName()\0clearAll()\0"
    "nameChange()\0removeName()\0setFont(int)\0"
    "clockChange()\0absentAdd()\0resetFileList()\0"
};

const QMetaObject MyQWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyQWidget,
      qt_meta_data_MyQWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyQWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyQWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyQWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyQWidget))
        return static_cast<void*>(const_cast< MyQWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyQWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setOpenFileName(); break;
        case 1: openFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: randomName(); break;
        case 3: clearAll(); break;
        case 4: nameChange(); break;
        case 5: removeName(); break;
        case 6: setFont((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: clockChange(); break;
        case 8: absentAdd(); break;
        case 9: resetFileList(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
