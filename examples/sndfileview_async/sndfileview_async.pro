TEMPLATE = app
CONFIG += console debug_and_release
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4):QT+=widgets

include($$PWD/../../qtsampleengine.pri)

INCLUDEPATH +=                                              \
    $$PWD/src                                               \

SOURCES +=                                                  \
    $$PWD/src/main.cpp                                      \
    $$PWD/src/csppasyncpeakdatasource.cpp                   \
    $$PWD/src/cmainwindow.cpp                               \
    $$PWD/src/csppasyncaudiolimiter.cpp                     \
    $$PWD/src/csppasyncaudiowidget.cpp                      \
    $$PWD/src/ccomplexmonoaudiowidget.cpp                   \
    $$PWD/src/cspppeakreply.cpp                             \

HEADERS +=                                                  \
    $$PWD/src/csppasyncpeakdatasource.h                     \
    $$PWD/src/cmainwindow.h                                 \
    $$PWD/src/csppasyncaudiowidget.h                        \
    $$PWD/src/csppasyncaudiolimiter.h                       \
    $$PWD/src/ccomplexmonoaudiowidget.h                     \
    $$PWD/src/cspppeakreply.h                               \

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
