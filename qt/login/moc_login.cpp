/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created: Wed Nov 16 18:42:18 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "login.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyLogin[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyLogin[] = {
    "MyLogin\0\0accept()\0"
};

const QMetaObject MyLogin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyLogin,
      qt_meta_data_MyLogin, 0 }
};

const QMetaObject *MyLogin::metaObject() const
{
    return &staticMetaObject;
}

void *MyLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyLogin))
        return static_cast<void*>(const_cast< MyLogin*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accept(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
