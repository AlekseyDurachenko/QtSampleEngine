TEMPLATE = app
CONFIG += console
QT += core gui

include($$PWD/../../qtsampleengine.pri)

INCLUDEPATH +=                              \
    src                                     \

SOURCES +=                                  \
    $$PWD/src/main.cpp                            \
    $$PWD/src/csppsyncpeakdatasource.cpp \
    src/cmainwindow.cpp \
    src/cspplimiter.cpp \
    src/csppaudacitywidget.cpp

HEADERS +=                                  \
    $$PWD/src/csppsyncpeakdatasource.h \
    src/cmainwindow.h \
    src/cspplimiter.h \
    src/csppaudacitywidget.h

FORMS += \
    src/cmainwindow.ui
