TEMPLATE = app
CONFIG += console
QT += testlib
greaterThan(QT_MAJOR_VERSION, 4):QT+=widgets

include(../qtsampleengine.pri)

HEADERS +=                                  \
    $$PWD/src/test_qserange.h               \
    $$PWD/src/test_qseposition.h            \
    $$PWD/src/test_qseselection.h           \
    $$PWD/src/test_qsesppgeometry.h         \
    $$PWD/src/test_qsepeakarray.h           \
    $$PWD/src/test_qsespwgeometry.h         \

SOURCES +=                                  \
    $$PWD/src/test_main.cpp                 \
    $$PWD/src/test_qserange.cpp             \
    $$PWD/src/test_qseposition.cpp          \
    $$PWD/src/test_qseselection.cpp         \
    $$PWD/src/test_qsesppgeometry.cpp       \
    $$PWD/src/test_qsepeakarray.cpp         \
    $$PWD/src/test_qsespwgeometry.cpp       \

INCLUDEPATH +=                              \
    $$PWD/src                               \
