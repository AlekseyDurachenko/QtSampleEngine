TEMPLATE = app
CONFIG += console debug_and_release
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4):QT+=widgets

include($$PWD/../../qtsampleengine.pri)

INCLUDEPATH +=                                              \
    $$PWD/src                                               \

SOURCES +=                                                  \
    $$PWD/src/main.cpp                                      \
    $$PWD/src/signaldatasource.cpp                          \
    $$PWD/src/mainwindow.cpp                                \
    $$PWD/src/audiolimiter.cpp                              \
    $$PWD/src/audiowidget.cpp                               \
    $$PWD/src/complexmonoaudiowidget.cpp                    \

HEADERS +=                                                  \
    $$PWD/src/signaldatasource.h                            \
    $$PWD/src/mainwindow.h                                  \
    $$PWD/src/audiowidget.h                                 \
    $$PWD/src/audiolimiter.h                                \
    $$PWD/src/complexmonoaudiowidget.h                      \

FORMS +=                                                    \
    $$PWD/src/mainwindow.ui                                 \

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
