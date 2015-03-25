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
    src/csppsyncaudacitylimiter.cpp \
    src/csppsyncaudacitywidget.cpp

HEADERS +=                                  \
    $$PWD/src/csppsyncpeakdatasource.h \
    src/cmainwindow.h \
    src/csppsyncaudacitylimiter.h \
    src/csppsyncaudacitywidget.h

FORMS += \
    src/cmainwindow.ui
