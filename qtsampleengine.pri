HEADERS +=                                                              \
    $$PWD/src/canvas/qseaxiscanvasplot.h \
    $$PWD/src/canvas/qsemonocolorcanvasplot.h \
    $$PWD/src/core/qseabstractcontroller.h \
    $$PWD/src/core/qseabstractcontrollerproxy.h \
    $$PWD/src/core/qseabstractlimiter.h \
    $$PWD/src/core/qseabstractplot.h \
    $$PWD/src/core/qseabstractstandardcontroller.h \
    $$PWD/src/core/qseabstractwidget.h \
    $$PWD/src/core/qsecompositcontroller.h \
    $$PWD/src/core/qsehorizontalshiftcontrollerproxy.h \
    $$PWD/src/core/qsestandardhorizontalcontroller.h \
    $$PWD/src/core/qsestandardhorizontalzoomcontroller.h \
    $$PWD/src/core/qsestandardverticalcontroller.h \
    $$PWD/src/core/qsestandardverticalzoomcontroller.h \
    $$PWD/src/datatype/qsegeometry.h \
    $$PWD/src/datatype/qserange.h \
    $$PWD/src/helper/qsehelper.h \
    $$PWD/src/metric/qseabstractmetricprovider.h \
    $$PWD/src/metric/qselinearmetricprovider.h \
    $$PWD/src/metric/qsemetricitem.h \
    $$PWD/src/metric/qsemetricmapper.h \
    $$PWD/src/metric/qsesignallinearmetricprovider.h \
    $$PWD/src/metric/qsetimemetricprovider.h \
    $$PWD/src/position/qseposition.h \
    $$PWD/src/position/qsepositionplot.h \
    $$PWD/src/position/qsestandardpositioncontroller.h \
    $$PWD/src/selection/qseselection.h \
    $$PWD/src/selection/qseselectionplot.h \
    $$PWD/src/selection/qsestandardselectioncontroller.h \
    $$PWD/src/signal/qseabstractsignalplotdelegate.h \
    $$PWD/src/signal/qsesignalcanvasplot.h \
    $$PWD/src/signal/qsesignallinearplotdelegate.h \
    $$PWD/src/signal/qsesignalplot.h \
    $$PWD/src/widget/audacitywidget/qseaudacitycontroller.h \
    $$PWD/src/widget/axiswidget/qseabstractaxiswidget.h \
    $$PWD/src/widget/axiswidget/qsehorizontalaxiswidget.h \
    $$PWD/src/widget/axiswidget/qseverticalaxiswidget.h \
    $$PWD/src/widget/widget/qsewidget.h \
    $$PWD/src/qse_deprecated.h \
    $$PWD/src/signal/qseabstractsignaldatasource.h




SOURCES +=                                                              \
    $$PWD/src/canvas/qseaxiscanvasplot.cpp \
    $$PWD/src/canvas/qsemonocolorcanvasplot.cpp \
    $$PWD/src/core/qseabstractcontroller.cpp \
    $$PWD/src/core/qseabstractcontrollerproxy.cpp \
    $$PWD/src/core/qseabstractlimiter.cpp \
    $$PWD/src/core/qseabstractplot.cpp \
    $$PWD/src/core/qseabstractstandardcontroller.cpp \
    $$PWD/src/core/qseabstractwidget.cpp \
    $$PWD/src/core/qsecompositcontroller.cpp \
    $$PWD/src/core/qsehorizontalshiftcontrollerproxy.cpp \
    $$PWD/src/core/qsestandardhorizontalcontroller.cpp \
    $$PWD/src/core/qsestandardhorizontalzoomcontroller.cpp \
    $$PWD/src/core/qsestandardverticalcontroller.cpp \
    $$PWD/src/core/qsestandardverticalzoomcontroller.cpp \
    $$PWD/src/datatype/qsegeometry.cpp \
    $$PWD/src/datatype/qserange.cpp \
    $$PWD/src/helper/qsehelper.cpp \
    $$PWD/src/metric/qseabstractmetricprovider.cpp \
    $$PWD/src/metric/qselinearmetricprovider.cpp \
    $$PWD/src/metric/qsemetricitem.cpp \
    $$PWD/src/metric/qsemetricmapper.cpp \
    $$PWD/src/metric/qsesignallinearmetricprovider.cpp \
    $$PWD/src/metric/qsetimemetricprovider.cpp \
    $$PWD/src/position/qseposition.cpp \
    $$PWD/src/position/qsepositionplot.cpp \
    $$PWD/src/position/qsestandardpositioncontroller.cpp \
    $$PWD/src/selection/qseselection.cpp \
    $$PWD/src/selection/qseselectionplot.cpp \
    $$PWD/src/selection/qsestandardselectioncontroller.cpp \
    $$PWD/src/signal/qseabstractsignalplotdelegate.cpp \
    $$PWD/src/signal/qsesignalcanvasplot.cpp \
    $$PWD/src/signal/qsesignallinearplotdelegate.cpp \
    $$PWD/src/signal/qsesignalplot.cpp \
    $$PWD/src/widget/audacitywidget/qseaudacitycontroller.cpp \
    $$PWD/src/widget/axiswidget/qseabstractaxiswidget.cpp \
    $$PWD/src/widget/axiswidget/qsehorizontalaxiswidget.cpp \
    $$PWD/src/widget/axiswidget/qseverticalaxiswidget.cpp \
    $$PWD/src/widget/widget/qsewidget.cpp \
    $$PWD/src/signal/qseabstractsignaldatasource.cpp




OTHER_FILES +=                                                      \
    $$PWD/README.md                                                 \
    $$PWD/CHANGELOG                                                 \
    $$PWD/AUTHORS                                                   \
    $$PWD/LICENSE                                                   \
    $$PWD/S-Docs/DOC_RU.md                                          \


INCLUDEPATH +=                                                      \
    $$PWD/src                                                       \
    $$PWD/src/canvas                                                \
    $$PWD/src/core                                                  \
    $$PWD/src/datatype                                              \
    $$PWD/src/helper                                                \
    $$PWD/src/metric                                                \
    $$PWD/src/position                                              \
    $$PWD/src/selection                                             \
    $$PWD/src/signal                                                \
    $$PWD/src/widget                                                \
    $$PWD/src/widget/audacitywidget                              \
    $$PWD/src/widget/widget                                      \
    $$PWD/src/widget/axiswidget                                  \


DEFINES +=                                                          \
