/****************************************************************************
** Meta object code from reading C++ file 'qsampleeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/templates/qsample/qsampleeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qsampleeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QsampleEditor_t {
    QByteArrayData data[23];
    char stringdata[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QsampleEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QsampleEditor_t qt_meta_stringdata_QsampleEditor = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 13),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 11),
QT_MOC_LITERAL(4, 41, 12),
QT_MOC_LITERAL(5, 54, 19),
QT_MOC_LITERAL(6, 74, 11),
QT_MOC_LITERAL(7, 86, 8),
QT_MOC_LITERAL(8, 95, 7),
QT_MOC_LITERAL(9, 103, 14),
QT_MOC_LITERAL(10, 118, 12),
QT_MOC_LITERAL(11, 131, 5),
QT_MOC_LITERAL(12, 137, 14),
QT_MOC_LITERAL(13, 152, 12),
QT_MOC_LITERAL(14, 165, 14),
QT_MOC_LITERAL(15, 180, 16),
QT_MOC_LITERAL(16, 197, 15),
QT_MOC_LITERAL(17, 213, 17),
QT_MOC_LITERAL(18, 231, 7),
QT_MOC_LITERAL(19, 239, 9),
QT_MOC_LITERAL(20, 249, 11),
QT_MOC_LITERAL(21, 261, 16),
QT_MOC_LITERAL(22, 278, 18)
    },
    "QsampleEditor\0selectPicture\0\0loadPicture\0"
    "picture_path\0updateQuestionCount\0"
    "addQuestion\0question\0answers\0"
    "correct_answer\0loadQuestion\0index\0"
    "removeQuestion\0saveQuestion\0moveQuestionUp\0"
    "moveQuestionDown\0configureUpDown\0"
    "setEditorsEnabled\0enabled\0checkName\0"
    "checkAuthor\0updateNameStatus\0"
    "updateAuthorStatus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QsampleEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08,
       3,    1,   95,    2, 0x08,
       5,    0,   98,    2, 0x08,
       6,    4,   99,    2, 0x08,
       6,    0,  108,    2, 0x08,
      10,    1,  109,    2, 0x08,
      12,    0,  112,    2, 0x08,
      13,    0,  113,    2, 0x08,
      14,    0,  114,    2, 0x08,
      15,    0,  115,    2, 0x08,
      16,    0,  116,    2, 0x08,
      17,    1,  117,    2, 0x08,
      19,    0,  120,    2, 0x08,
      20,    0,  121,    2, 0x08,
      21,    0,  122,    2, 0x08,
      22,    0,  123,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::Int, QMetaType::QString,    7,    8,    9,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QsampleEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QsampleEditor *_t = static_cast<QsampleEditor *>(_o);
        switch (_id) {
        case 0: _t->selectPicture(); break;
        case 1: _t->loadPicture((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateQuestionCount(); break;
        case 3: _t->addQuestion((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 4: _t->addQuestion(); break;
        case 5: _t->loadQuestion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->removeQuestion(); break;
        case 7: _t->saveQuestion(); break;
        case 8: _t->moveQuestionUp(); break;
        case 9: _t->moveQuestionDown(); break;
        case 10: _t->configureUpDown(); break;
        case 11: _t->setEditorsEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->checkName(); break;
        case 13: _t->checkAuthor(); break;
        case 14: _t->updateNameStatus(); break;
        case 15: _t->updateAuthorStatus(); break;
        default: ;
        }
    }
}

const QMetaObject QsampleEditor::staticMetaObject = {
    { &TemplateEditor::staticMetaObject, qt_meta_stringdata_QsampleEditor.data,
      qt_meta_data_QsampleEditor,  qt_static_metacall, 0, 0}
};


const QMetaObject *QsampleEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QsampleEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QsampleEditor.stringdata))
        return static_cast<void*>(const_cast< QsampleEditor*>(this));
    return TemplateEditor::qt_metacast(_clname);
}

int QsampleEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TemplateEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
