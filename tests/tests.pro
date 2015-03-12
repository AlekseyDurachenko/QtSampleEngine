TEMPLATE = app
CONFIG += console
QT += testlib

include(../qtsampleengine.pri)

INCLUDEPATH +=                              \
    src                                     \

SOURCES +=                                  \
    src/test_main.cpp                       \
    src/test_qserange.cpp                   \
    src/test_qsecursor.cpp                  \

HEADERS +=                                  \
    src/test_qserange.h                     \
    src/test_qsecursor.h                    \
