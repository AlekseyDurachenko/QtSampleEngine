HEADERS +=                                                          \
    $$PWD/src/core/spp/qseabstractsppcontroller.h \
    $$PWD/src/core/spp/qseabstractsppplot.h \
    $$PWD/src/core/spp/qseabstractsppwidget.h \
    $$PWD/src/core/spw/qseabstractspwcontroller.h \
    $$PWD/src/core/spw/qseabstractspwplot.h \
    $$PWD/src/core/spw/qseabstractspwwidget.h \
    $$PWD/src/core/qseabstractcontroller.h \
    $$PWD/src/core/qseabstractplot.h \
    $$PWD/src/core/qseabstractwidget.h \
    $$PWD/src/core/qsehelper.h \
    $$PWD/src/cover/spp/plot/qsemonocolorsppcoverplot.h \
    $$PWD/src/cursor/spp/plot/qsesppcursorplot.h \
    $$PWD/src/cursor/qsecursor.h \
    $$PWD/src/datasource/spp/qseabstractsppasyncdatasource.h \
    $$PWD/src/datasource/spp/qseabstractspppeakreply.h \
    $$PWD/src/datasource/spp/qseabstractsppsyncdatasource.h \
    $$PWD/src/datasource/spw/qseabstractspwasyncdatasource.h \
    $$PWD/src/datasource/spw/qseabstractspwpeakreply.h \
    $$PWD/src/datasource/spw/qseabstractspwsyncdatasource.h \
    $$PWD/src/datasource/qseabstractdatasource.h \
    $$PWD/src/datasource/qseabstractpeakreply.h \
    $$PWD/src/datatype/qsepeakarray.h \
    $$PWD/src/datatype/qserange.h \
    $$PWD/src/datatype/qsesppgeometry.h \
    $$PWD/src/datatype/qsespwgeometry.h \
    $$PWD/src/metric/spp/qseabstractsppmetricprovider.h \
    $$PWD/src/metric/qseabstractmetricprovider.h \
    $$PWD/src/metric/qsemetricitem.h \
    $$PWD/src/metric/qsemetricmapper.h \
    $$PWD/src/selection/spp/plot/qsesppselectionplot.h \
    $$PWD/src/selection/qseselection.h \
    $$PWD/src/signal/spp/plot/qseabstractsppsignalplot.h \
    $$PWD/src/signal/spp/plot/qseabstractsppsyncsignalplot.h \
    $$PWD/src/signal/spp/plot/qsesppsyncsignallinearplot.h \
    $$PWD/src/widget/sppwidget/qsesppwidget.h \
    $$PWD/src/qse_deprecated.h


SOURCES +=                                                          \
    $$PWD/src/core/spp/qseabstractsppcontroller.cpp \
    $$PWD/src/core/spp/qseabstractsppplot.cpp \
    $$PWD/src/core/spp/qseabstractsppwidget.cpp \
    $$PWD/src/core/spw/qseabstractspwcontroller.cpp \
    $$PWD/src/core/spw/qseabstractspwplot.cpp \
    $$PWD/src/core/spw/qseabstractspwwidget.cpp \
    $$PWD/src/core/qseabstractcontroller.cpp \
    $$PWD/src/core/qseabstractplot.cpp \
    $$PWD/src/core/qseabstractwidget.cpp \
    $$PWD/src/core/qsehelper.cpp \
    $$PWD/src/cover/spp/plot/qsemonocolorsppcoverplot.cpp \
    $$PWD/src/cursor/spp/plot/qsesppcursorplot.cpp \
    $$PWD/src/cursor/qsecursor.cpp \
    $$PWD/src/datasource/spp/qseabstractsppasyncdatasource.cpp \
    $$PWD/src/datasource/spp/qseabstractspppeakreply.cpp \
    $$PWD/src/datasource/spp/qseabstractsppsyncdatasource.cpp \
    $$PWD/src/datasource/spw/qseabstractspwasyncdatasource.cpp \
    $$PWD/src/datasource/spw/qseabstractspwpeakreply.cpp \
    $$PWD/src/datasource/spw/qseabstractspwsyncdatasource.cpp \
    $$PWD/src/datasource/qseabstractdatasource.cpp \
    $$PWD/src/datasource/qseabstractpeakreply.cpp \
    $$PWD/src/datatype/qsepeakarray.cpp \
    $$PWD/src/datatype/qserange.cpp \
    $$PWD/src/datatype/qsesppgeometry.cpp \
    $$PWD/src/datatype/qsespwgeometry.cpp \
    $$PWD/src/metric/spp/qseabstractsppmetricprovider.cpp \
    $$PWD/src/metric/qseabstractmetricprovider.cpp \
    $$PWD/src/metric/qsemetricitem.cpp \
    $$PWD/src/metric/qsemetricmapper.cpp \
    $$PWD/src/selection/spp/plot/qsesppselectionplot.cpp \
    $$PWD/src/selection/qseselection.cpp \
    $$PWD/src/signal/spp/plot/qseabstractsppsignalplot.cpp \
    $$PWD/src/signal/spp/plot/qseabstractsppsyncsignalplot.cpp \
    $$PWD/src/signal/spp/plot/qsesppsyncsignallinearplot.cpp \
    $$PWD/src/widget/sppwidget/qsesppwidget.cpp


OTHER_FILES +=                                                      \
    $$PWD/README.md                                                 \
    $$PWD/CHANGELOG                                                 \
    $$PWD/AUTHORS                                                   \
    $$PWD/LICENSE                                                   \
    $$PWD/S-Docs/DOC_RU.md                                          \

INCLUDEPATH +=                                                      \
    $$PWD/src                                                       \
    $$PWD/axis                                                      \
    $$PWD/src/core                                                  \
    $$PWD/src/core/spp                                              \
    $$PWD/src/core/spw                                              \
    $$PWD/src/cover                                                 \
    $$PWD/src/cover/spp/plot                                        \
    $$PWD/src/cursor                                                \
    $$PWD/src/cursor/spp/plot                                       \
    $$PWD/src/datasource                                            \
    $$PWD/src/datasource/spp                                        \
    $$PWD/src/datasource/spw                                        \
    $$PWD/src/datatype                                              \
    $$PWD/src/metric                                                \
    $$PWD/src/metric/spp                                            \
    $$PWD/src/metric/spw                                            \
    $$PWD/src/selection                                             \
    $$PWD/src/selection/spp/plot                                    \
    $$PWD/src/signal                                                \
    $$PWD/src/signal/spp/plot                                       \
    $$PWD/src/widget                                                \
    $$PWD/src/widget/sppwidget                                      \

DEFINES +=                                                          \
