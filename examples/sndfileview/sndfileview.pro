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
    src/csppsyncaudiolimiter.cpp \
    src/csppsyncaudiowidget.cpp \
    src/ccomplexmonoaudiowidget.cpp

HEADERS +=                                  \
    $$PWD/src/csppsyncpeakdatasource.h \
    src/cmainwindow.h \
    src/csppsyncaudiowidget.h \
    src/csppsyncaudiolimiter.h \
    src/ccomplexmonoaudiowidget.h

FORMS += \
    src/cmainwindow.ui
