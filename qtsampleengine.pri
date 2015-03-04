HEADERS +=                                                          \
    $$PWD/src/axis/qseabsolutemetricprovider.h                      \
    $$PWD/src/axis/qseverticalcontroller.h                          \
    $$PWD/src/axis/qseaxiswidget.h                                  \
    $$PWD/src/axis/qsecoverplot.h                                   \
    $$PWD/src/axis/qsehorizontalcontroller.h                        \
    $$PWD/src/axis/qsetimemetricprovider.h                          \
    $$PWD/src/axis/qselinemetricprovider.h                          \
    $$PWD/src/core/qseabstractcontroller.h                          \
    $$PWD/src/core/qseabstractplot.h                                \
    $$PWD/src/core/qseabstractwidget.h                              \
    $$PWD/src/core/qsegeometry.h                                    \
    $$PWD/src/cursor/qsecursorplot.h                                \
    $$PWD/src/cursor/qsecursor.h                                    \
    $$PWD/src/metric/qseabstractmetricprovider.h                    \
    $$PWD/src/metric/qsemetricitem.h                                \
    $$PWD/src/metric/qsemetricmapper.h                              \
    $$PWD/src/selection/qseselectionplot.h                          \
    $$PWD/src/selection/qseselection.h                              \
    $$PWD/src/singlesignal/qsesinglesignallinearplot.h              \
    $$PWD/src/singlesignal/qsesinglesignalabstractpeakreader.h      \
    $$PWD/src/singlesignal/qsesinglesignalabstractplot.h            \
    $$PWD/src/core/qsehelper.h                                      \

SOURCES +=                                                          \
    $$PWD/src/axis/qseabsolutemetricprovider.cpp                    \
    $$PWD/src/axis/qseverticalcontroller.cpp                        \
    $$PWD/src/axis/qseaxiswidget.cpp                                \
    $$PWD/src/axis/qsecoverplot.cpp                                 \
    $$PWD/src/axis/qsehorizontalcontroller.cpp                      \
    $$PWD/src/axis/qsetimemetricprovider.cpp                        \
    $$PWD/src/axis/qselinemetricprovider.cpp                        \
    $$PWD/src/core/qseabstractcontroller.cpp                        \
    $$PWD/src/core/qseabstractplot.cpp                              \
    $$PWD/src/core/qseabstractwidget.cpp                            \
    $$PWD/src/core/qsegeometry.cpp                                  \
    $$PWD/src/cursor/qsecursorplot.cpp                              \
    $$PWD/src/cursor/qsecursor.cpp                                  \
    $$PWD/src/metric/qseabstractmetricprovider.cpp                  \
    $$PWD/src/metric/qsemetricitem.cpp                              \
    $$PWD/src/metric/qsemetricmapper.cpp                            \
    $$PWD/src/selection/qseselectionplot.cpp                        \
    $$PWD/src/selection/qseselection.cpp                            \
    $$PWD/src/singlesignal/qsesinglesignallinearplot.cpp            \
    $$PWD/src/singlesignal/qsesinglesignalabstractpeakreader.cpp    \
    $$PWD/src/singlesignal/qsesinglesignalabstractplot.cpp          \
    $$PWD/src/core/qsehelper.cpp                                    \

OTHER_FILES +=                                                      \
    $$PWD/README                                                    \
    $$PWD/CHANGELOG                                                 \
    $$PWD/AUTHORS                                                   \
    $$PWD/LICENSE                                                   \
    $$PWD/README.md                                                 \
    $$PWD/S-Docs/DOC_RU.md                                          \

INCLUDEPATH +=                                                      \
    $$PWD/src                                                       \
    $$PWD/src/axis                                                  \
    $$PWD/src/core                                                  \
    $$PWD/src/cursor                                                \
    $$PWD/src/metric                                                \
    $$PWD/src/selection                                             \
    $$PWD/src/singlesignal                                          \

DEFINES +=                                                          \
