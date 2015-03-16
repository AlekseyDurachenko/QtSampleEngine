TEMPLATE = app
CONFIG += console
QT += core gui

include($$PWD/../../qtsampleengine.pri)
include($$PWD/submodules/QtAttoDateTime/qtattodatetime.pri)

INCLUDEPATH +=                              \
    src                                     \

SOURCES +=                                  \
    $$PWD/src/main.cpp                            \
    $$PWD/src/csppsyncdatasource.cpp

HEADERS +=                                  \
    $$PWD/src/csppsyncdatasource.h
