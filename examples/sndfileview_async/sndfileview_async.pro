TEMPLATE = app
CONFIG += console debug_and_release
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4):QT+=widgets

include($$PWD/../../qtsampleengine.pri)

INCLUDEPATH +=                                              \
    $$PWD/src                                               \

SOURCES +=                                                  \
    $$PWD/src/main.cpp                                      \
    $$PWD/src/csppsyncpeakdatasource.cpp                    \
    $$PWD/src/cmainwindow.cpp                               \
    $$PWD/src/csppsyncaudiolimiter.cpp                      \
    $$PWD/src/csppsyncaudiowidget.cpp                       \
    $$PWD/src/ccomplexmonoaudiowidget.cpp                   \

HEADERS +=                                                  \
    $$PWD/src/csppsyncpeakdatasource.h                      \
    $$PWD/src/cmainwindow.h                                 \
    $$PWD/src/csppsyncaudiowidget.h                         \
    $$PWD/src/csppsyncaudiolimiter.h                        \
    $$PWD/src/ccomplexmonoaudiowidget.h                     \

FORMS +=                                                    \
    $$PWD/src/cmainwindow.ui                                \

build_pass:CONFIG(debug, debug|release) {
    win32 {
        LIBS    +=
    }

    unix {
        LIBS    += -lsndfile
    }
}

build_pass:CONFIG(release, debug|release) {
    win32 {
        LIBS    +=
    }

    unix {
        LIBS    += -lsndfile
    }
}
