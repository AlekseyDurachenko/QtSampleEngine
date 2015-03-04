TEMPLATE = app
CONFIG += console
QT += core gui

include($$PWD/../../qtsampleengine.pri)
include($$PWD/submodules/QtAttoDateTime/qtattodatetime.pri)

INCLUDEPATH +=                              \
    src                                     \

SOURCES +=                                  \
    src/main.cpp                            \

HEADERS +=                                  \
