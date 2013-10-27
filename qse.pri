HEADERS +=                                              \
    $$PWD/src/axis/qseabsolutemetricprovider.h          \
    $$PWD/src/axis/qseverticalcontroller.h              \
    $$PWD/src/axis/qseaxiswidget.h                      \
    $$PWD/src/axis/qsecoverplot.h                       \
    $$PWD/src/axis/qsehorizontalcontroller.h            \
    $$PWD/src/axis/qsetimemetricprovider.h              \
    $$PWD/src/core/qseabstractcontroller.h              \
    $$PWD/src/core/qseabstractplot.h                    \
    $$PWD/src/core/qseabstractwidget.h                  \
    $$PWD/src/core/qsefunc.h                            \
    $$PWD/src/core/qsegeometry.h                        \
    $$PWD/src/cursor/qsecursorplot.h                    \
    $$PWD/src/cursor/qsecursor.h                        \
    $$PWD/src/metric/qseabstractmetricprovider.h        \
    $$PWD/src/metric/qsemetricitem.h                    \
    $$PWD/src/metric/qsemetricmapper.h                  \
    $$PWD/src/selection/qseselectionplot.h              \
    $$PWD/src/selection/qseselection.h                  \

SOURCES +=                                              \
    $$PWD/src/axis/qseabsolutemetricprovider.cpp        \
    $$PWD/src/axis/qseverticalcontroller.cpp            \
    $$PWD/src/axis/qseaxiswidget.cpp                    \
    $$PWD/src/axis/qsecoverplot.cpp                     \
    $$PWD/src/axis/qsehorizontalcontroller.cpp          \
    $$PWD/src/axis/qsetimemetricprovider.cpp            \
    $$PWD/src/core/qseabstractcontroller.cpp            \
    $$PWD/src/core/qseabstractplot.cpp                  \
    $$PWD/src/core/qseabstractwidget.cpp                \
    $$PWD/src/core/qsefunc.cpp                          \
    $$PWD/src/core/qsegeometry.cpp                      \
    $$PWD/src/cursor/qsecursorplot.cpp                  \
    $$PWD/src/cursor/qsecursor.cpp                      \
    $$PWD/src/metric/qseabstractmetricprovider.cpp      \
    $$PWD/src/metric/qsemetricitem.cpp                  \
    $$PWD/src/metric/qsemetricmapper.cpp                \
    $$PWD/src/selection/qseselectionplot.cpp            \
    $$PWD/src/selection/qseselection.cpp                \

OTHER_FILES +=                                          \

INCLUDEPATH +=                                          \
    $$PWD/src                                           \
    $$PWD/src/axis                                      \
    $$PWD/src/core                                      \
    $$PWD/src/cursor                                    \
    $$PWD/src/metric                                    \
    $$PWD/src/selection                                 \
    $$PWD/src/waveform                                  \

DEFINES +=                                              \
