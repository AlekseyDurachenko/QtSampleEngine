TEMPLATE = app
CONFIG += console
QT += testlib

include(../qtsampleengine.pri)

HEADERS +=                                  \
    $$PWD/src/test_qserange.h               \
    $$PWD/src/test_qsecursor.h              \
    $$PWD/src/test_qseselection.h           \

SOURCES +=                                  \
    $$PWD/src/test_main.cpp                 \
    $$PWD/src/test_qserange.cpp             \
    $$PWD/src/test_qsecursor.cpp            \
    $$PWD/src/test_qseselection.cpp         \

INCLUDEPATH +=                              \
    $$PWD/src                               \
