HEADERS +=                                                          \
    $$PWD/src/qse_deprecated.h                                      \
    $$PWD/src/datatype/qserange.h                                   \
    $$PWD/src/datatype/qsesppgeometry.h                             \
    $$PWD/src/datatype/qsespwgeometry.h                             \
    $$PWD/src/core/qsehelper.h                                      \
    $$PWD/src/core/qseabstractcontroller.h                          \
    $$PWD/src/core/qseabstractplot.h                                \
    $$PWD/src/core/qseabstractwidget.h                              \
    $$PWD/src/core/spp/qseabstractsppcontroller.h                   \
    $$PWD/src/core/spp/qseabstractsppplot.h                         \
    $$PWD/src/core/spp/qseabstractsppwidget.h                       \
    $$PWD/src/core/spw/qseabstractspwcontroller.h                   \
    $$PWD/src/core/spw/qseabstractspwplot.h                         \
    $$PWD/src/core/spw/qseabstractspwwidget.h                       \
    $$PWD/src/cursor/qsecursor.h                                    \
    $$PWD/src/selection/qseselection.h                              \
    #$$PWD/src/axis/qseabsolutemetricprovider.h                      \
    #$$PWD/src/axis/qseverticalcontroller.h                          \
    #$$PWD/src/axis/qseaxiswidget.h                                  \
    #$$PWD/src/axis/qsecoverplot.h                                   \
    #$$PWD/src/axis/qsehorizontalcontroller.h                        \
    #$$PWD/src/axis/qsetimemetricprovider.h                          \
    #$$PWD/src/axis/qselinemetricprovider.h                          \
    #$$PWD/src/cursor/qsecursorplot.h                                \
    #$$PWD/src/metric/qseabstractmetricprovider.h                    \
    #$$PWD/src/metric/qsemetricitem.h                                \
    #$$PWD/src/metric/qsemetricmapper.h                              \
    #$$PWD/src/selection/qseselectionplot.h                          \
    #$$PWD/src/singlesignal/qsesinglesignallinearplot.h              \
    #$$PWD/src/singlesignal/qsesinglesignalabstractpeakreader.h      \
    #$$PWD/src/singlesignal/qsesinglesignalabstractplot.h            \
    #$$PWD/src/core/qsehelper.h                                      \

SOURCES +=                                                          \
    $$PWD/src/datatype/qserange.cpp                                 \
    $$PWD/src/datatype/qsesppgeometry.cpp                           \
    $$PWD/src/datatype/qsespwgeometry.cpp                           \
    $$PWD/src/core/qsehelper.cpp                                    \
    $$PWD/src/core/qseabstractcontroller.cpp                        \
    $$PWD/src/core/qseabstractplot.cpp                              \
    $$PWD/src/core/qseabstractwidget.cpp                            \
    $$PWD/src/core/spp/qseabstractsppcontroller.cpp                 \
    $$PWD/src/core/spp/qseabstractsppplot.cpp                       \
    $$PWD/src/core/spp/qseabstractsppwidget.cpp                     \
    $$PWD/src/core/spw/qseabstractspwcontroller.cpp                 \
    $$PWD/src/core/spw/qseabstractspwplot.cpp                       \
    $$PWD/src/core/spw/qseabstractspwwidget.cpp                     \
    $$PWD/src/cursor/qsecursor.cpp                                  \
    $$PWD/src/selection/qseselection.cpp                            \
    #$$PWD/src/axis/qseabsolutemetricprovider.cpp                    \
    #$$PWD/src/axis/qseverticalcontroller.cpp                        \
    #$$PWD/src/axis/qseaxiswidget.cpp                                \
    #$$PWD/src/axis/qsecoverplot.cpp                                 \
    #$$PWD/src/axis/qsehorizontalcontroller.cpp                      \
    #$$PWD/src/axis/qsetimemetricprovider.cpp                        \
    #$$PWD/src/axis/qselinemetricprovider.cpp                        \
    #$$PWD/src/cursor/qsecursorplot.cpp                              \
    #$$PWD/src/metric/qseabstractmetricprovider.cpp                  \
    #$$PWD/src/metric/qsemetricitem.cpp                              \
    #$$PWD/src/metric/qsemetricmapper.cpp                            \
    #$$PWD/src/selection/qseselectionplot.cpp                        \
    #$$PWD/src/singlesignal/qsesinglesignallinearplot.cpp            \
    #$$PWD/src/singlesignal/qsesinglesignalabstractpeakreader.cpp    \
    #$$PWD/src/singlesignal/qsesinglesignalabstractplot.cpp          \
    #$$PWD/src/core/qsehelper.cpp                                    \

OTHER_FILES +=                                                      \
    $$PWD/README.md                                                 \
    $$PWD/CHANGELOG                                                 \
    $$PWD/AUTHORS                                                   \
    $$PWD/LICENSE                                                   \
    $$PWD/S-Docs/DOC_RU.md                                          \

INCLUDEPATH +=                                                      \
    $$PWD/src                                                       \
    $$PWD/src/datatype                                              \
    $$PWD/src/core                                                  \
    $$PWD/src/core/spp                                              \
    $$PWD/src/core/spw                                              \
    $$PWD/src/axis                                                  \
    $$PWD/src/cursor                                                \
    $$PWD/src/metric                                                \
    $$PWD/src/selection                                             \
    $$PWD/src/singlesignal                                          \

DEFINES +=                                                          \
