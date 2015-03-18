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
    $$PWD/src/datasource/qseabstractdatasource.h \
    $$PWD/src/datasource/qseabstractsppsyncdatasource.h \
    $$PWD/src/datatype/qsepeakarray.h \
    $$PWD/src/datasource/qseabstractspwsyncdatasource.h \
    $$PWD/src/datasource/qseabstractsppasyncdatasource.h \
    $$PWD/src/datasource/qseabstractpeakreply.h \
    $$PWD/src/datasource/qseabstractspppeakreply.h \
    $$PWD/src/datasource/qseabstractspwpeakreply.h \
    $$PWD/src/datasource/qseabstractspwasyncdatasource.h \
    $$PWD/src/widget/sppwidget/qsesppwidget.h \
    $$PWD/src/plot/cover/qsemonocolorsppcoverplot.h \
    $$PWD/src/plot/cursor/qsesppcursorplot.h \
    $$PWD/src/plot/selection/qsesppselectionplot.h \
    $$PWD/src/plot/signal/qseabstractsppsignalplot.h \
    $$PWD/src/plot/signal/qseabstractsppsyncsignalplot.h \
    $$PWD/src/plot/signal/qsesppsyncsignallinearplot.h \
    $$PWD/src/metric/qsemetricitem.h \
    $$PWD/src/metric/qsemetricmapper.h \
    $$PWD/src/metric/qseabstractmetricprovider.h \
    $$PWD/src/metric/qseabstractsppmetricprovider.h

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
    $$PWD/src/datasource/qseabstractdatasource.cpp \
    $$PWD/src/datasource/qseabstractsppsyncdatasource.cpp \
    $$PWD/src/datatype/qsepeakarray.cpp \
    $$PWD/src/datasource/qseabstractspwsyncdatasource.cpp \
    $$PWD/src/datasource/qseabstractsppasyncdatasource.cpp \
    $$PWD/src/datasource/qseabstractpeakreply.cpp \
    $$PWD/src/datasource/qseabstractspppeakreply.cpp \
    $$PWD/src/datasource/qseabstractspwpeakreply.cpp \
    $$PWD/src/datasource/qseabstractspwasyncdatasource.cpp \
    $$PWD/src/widget/sppwidget/qsesppwidget.cpp \
    $$PWD/src/plot/cover/qsemonocolorsppcoverplot.cpp \
    $$PWD/src/plot/cursor/qsesppcursorplot.cpp \
    $$PWD/src/plot/selection/qsesppselectionplot.cpp \
    $$PWD/src/plot/signal/qseabstractsppsignalplot.cpp \
    $$PWD/src/plot/signal/qseabstractsppsyncsignalplot.cpp \
    $$PWD/src/plot/signal/qsesppsyncsignallinearplot.cpp \
    $$PWD/src/metric/qsemetricitem.cpp \
    $$PWD/src/metric/qsemetricmapper.cpp \
    $$PWD/src/metric/qseabstractmetricprovider.cpp \
    $$PWD/src/metric/qseabstractsppmetricprovider.cpp

OTHER_FILES +=                                                      \
    $$PWD/README.md                                                 \
    $$PWD/CHANGELOG                                                 \
    $$PWD/AUTHORS                                                   \
    $$PWD/LICENSE                                                   \
    $$PWD/S-Docs/DOC_RU.md                                          \

INCLUDEPATH +=                                                      \
    $$PWD/src                                                       \
    $$PWD/src/datatype                                              \
    $$PWD/src/datasource                                            \
    $$PWD/src/core                                                  \
    $$PWD/src/core/spp                                              \
    $$PWD/src/core/spw                                              \
    $$PWD/src/axis                                                  \
    $$PWD/src/cursor                                                \
    $$PWD/src/metric                                                \
    $$PWD/src/selection                                             \
    $$PWD/src/singlesignal                                          \
    $$PWD/src/widget/sppwidget                                      \
    $$PWD/src/plot/cover                                            \
    $$PWD/src/plot/cursor                                           \
    $$PWD/src/plot/selection                                        \
    $$PWD/src/plot/signal                                           \



DEFINES +=                                                          \
