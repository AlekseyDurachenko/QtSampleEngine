// Copyright (C) 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "qsesppwidget.h"
#include "qsemonocolorsppcoverplot.h"
#include "qsesppcursorplot.h"
#include "qsecursor.h"
#include "qsesppselectionplot.h"
#include "qseselection.h"
#include "csppsyncpeakdatasource.h"
#include "qsesppsyncsignallinearplot.h"
#include "qsesppstandardhorizontalcontroller.h"
#include "qsesppstandardverticalcontroller.h"
#include "qsesppcompositorcontroller.h"
#include "qsesppaxiswidget.h"
#include "qsespplinearmetricprovider.h"
#include "qsesppsignallinearamplmetricprovider.h"
#include "qsespptimemetricprovider.h"
#include "qsesppaxiscoverplot.h"
#include "qsesppstandardhorizontalzoomcontroller.h"
#include "qsesppstandardverticalzoomcontroller.h"
#include "qsesppstandardcursorcontroller.h"
#include "qsesppstandardselectioncontroller.h"
#include "cspplimiter.h"
#include "csppaudacitywidget.h"
#include <QDebug>
#include <math.h>
#include <QtGui>
#include <limits>
#include <limits.h>
#include <cfloat>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    /*
    QseSppAxisWidget *topAxis = new QseSppAxisWidget(QseSppAxisWidget::Top, this);
    topAxis->setBackground(QColor(Qt::gray));
    QseSppAxisWidget *bottomAxis = new QseSppAxisWidget(QseSppAxisWidget::Bottom, this);
    bottomAxis->setBackground(QColor(Qt::gray));
    QseSppAxisWidget *leftAxis = new QseSppAxisWidget(QseSppAxisWidget::Left, this);
    leftAxis->setBackground(QColor(Qt::gray));
    QseSppAxisWidget *rightAxis = new QseSppAxisWidget(QseSppAxisWidget::Right, this);
    rightAxis->setBackground(QColor(Qt::gray));

    QseSppLinearMetricProvider *sppHorizontalLinearMetricProvider =
            new QseSppLinearMetricProvider(QseSppLinearMetricProvider::Horizontal, this);
    QseSppLinearMetricProvider *sppVerticalLinearMetricProvider =
            new QseSppLinearMetricProvider(QseSppLinearMetricProvider::Vertical, this);
    QseSppSignalLinearAmplMetricProvider *signalLinearAmpl =
            new QseSppSignalLinearAmplMetricProvider(this);
    QseSppTimeMetricProvider *timeProvider = new QseSppTimeMetricProvider(this);
    timeProvider->setSampleRate(44100.0);

    m_sppWidget = new QseSppWidget(this);
    m_monocolorCoverSppPlot = new QseMonocolorSppCoverPlot(this);

    m_cursor = new QseCursor(this);
    m_cursor->setAvailableRange(QseRange(0, 1000));
    m_sppCursorPlot = new QseSppCursorPlot(this);
    m_sppCursorPlot->setCursor(m_cursor);

    QseSppAxisCoverPlot *axisPlot = new QseSppAxisCoverPlot(this);
    axisPlot->setHorizontalMetricProvider(sppHorizontalLinearMetricProvider);
    axisPlot->setVerticalMetricProvider(signalLinearAmpl);

    m_selection = new QseSelection(this);
    m_selection->setAvailableRange(QseRange(0, 1000));
    m_sppSelectionPlot = new QseSppSelectionPlot(this);
    m_sppSelectionPlot->setSelection(m_selection);

    m_sppSignalLinearPlot = new QseSppSyncSignalLinearPlot(this);
    m_sppSignalLinearPlot->setDataSource(dataSource);

    QList<QseAbstractSppPlot *> preUncachedPlots;
    preUncachedPlots << m_monocolorCoverSppPlot;

    QList<QseAbstractSppPlot *> cachedPlots;
    cachedPlots << axisPlot;
    cachedPlots << m_sppSignalLinearPlot;

    QList<QseAbstractSppPlot *> postUncachedPlots;
    postUncachedPlots << m_sppSelectionPlot;
    postUncachedPlots << m_sppCursorPlot;

    m_sppWidget->setPreUncachedPlot(preUncachedPlots);
    m_sppWidget->setCachedPlot(cachedPlots);
    m_sppWidget->setPostUncachedPlot(postUncachedPlots);



    sppHorizontalLinearMetricProvider->setFactor(1);
    signalLinearAmpl->setFactor(100);
    topAxis->setMetricProvider(sppHorizontalLinearMetricProvider);
    bottomAxis->setMetricProvider(timeProvider);
    leftAxis->setMetricProvider(signalLinearAmpl);
    rightAxis->setMetricProvider(sppVerticalLinearMetricProvider);
    connect(m_sppWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            topAxis, SLOT(setGeometry(QseSppGeometry)));
    connect(m_sppWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            bottomAxis, SLOT(setGeometry(QseSppGeometry)));
    connect(m_sppWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            leftAxis, SLOT(setGeometry(QseSppGeometry)));
    connect(m_sppWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            rightAxis, SLOT(setGeometry(QseSppGeometry)));

//    QHBoxLayout *hbox = new QHBoxLayout;
//    hbox->setSpacing(0);
//    hbox->addWidget(leftAxis);
//    hbox->addWidget(m_sppWidget);
//    hbox->addWidget(rightAxis);

//    qDebug() << QFontMetrics(font()).boundingRect("01234");
//    qDebug() << QFontMetrics(font()).boundingRect("...");

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(topAxis, 0, 1);
    grid->addWidget(leftAxis, 1, 0);
    grid->addWidget(m_sppWidget, 1, 1);
    grid->addWidget(rightAxis, 1, 2);
    grid->addWidget(bottomAxis, 2, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(m_sppWidget);
    layout->addItem(grid);
    layout->setSpacing(0);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    //layout->addWidget(topAxis);
    //layout->addWidget(m_sppWidget);
    //layout->addItem(hbox);
    //layout->addWidget(downAxis);
    m_sppWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QScrollBar *scrollBar = new QScrollBar(Qt::Horizontal, widget);
    QScrollBar *scrollBar2 = new QScrollBar(Qt::Horizontal, widget);
    layout->addWidget(scrollBar);
    layout->addWidget(scrollBar2);
    scrollBar->setRange(-100, 10000);
    scrollBar->setValue(-1);
    scrollBar2->setRange(-200, 10000);
    scrollBar2->setValue(0);
    connect(scrollBar, SIGNAL(valueChanged(int)),
            this, SLOT(scrollBar_valueChanged(int)));
    connect(scrollBar2, SIGNAL(valueChanged(int)),
            this, SLOT(scrollBar2_valueChanged(int)));
    setCentralWidget(widget);

    QList<QseAbstractSppController *> sppControllers;

    QseSppStandardHorizontalController *hctrl = new QseSppStandardHorizontalController(this);
    hctrl->setKeyboardModifiers(Qt::NoModifier);
    hctrl->setMouseButtons(Qt::RightButton);
    sppControllers << hctrl;

    QseSppStandardVerticalController *vctrl = new QseSppStandardVerticalController(this);
    vctrl->setKeyboardModifiers(Qt::NoModifier);
    vctrl->setMouseButtons(Qt::RightButton);
    sppControllers << vctrl;

    QseSppStandardVerticalZoomController *vzctrl = new QseSppStandardVerticalZoomController(this);
    vzctrl->setKeyboardModifiers(Qt::ControlModifier);
    sppControllers << vzctrl;

    QseSppStandardHorizontalZoomController *hzctrl = new QseSppStandardHorizontalZoomController(this);
    hzctrl->setKeyboardModifiers(Qt::NoModifier);
    sppControllers << hzctrl;

//    QseSppStandardCursorController *cctrl = new QseSppStandardCursorController(this);
//    cctrl->setMouseButtons(Qt::MiddleButton);
//    cctrl->setCursor(m_cursor);
//    sppControllers << cctrl;

    QseSppStandardSelectionController *sctrl = new QseSppStandardSelectionController(this);
    sctrl->setMouseButtons(Qt::LeftButton);
    sctrl->setKeyboardModifiers(Qt::NoModifier);
    sctrl->setSelection(m_selection);
    sppControllers << sctrl;

    //sppControllers << new QseSppVerticalController(this);
    //sppControllers << new QseSppHorizontalZoomController(this);
    //sppControllers << new QseSppVerticalZoomController(this);
    //QseSppCursorController *cursorController = new QseSppCursorController(this);
    //cursorController->setCursor(m_cursor);
    //sppControllers << cursorController;
    //QseSppSelectionController *selectionController = new QseSppSelectionController(this);
    //selectionController->setSelection(m_selection);
    //sppControllers << selectionController;

    QseSppCompositorController *sppCompositorController =
            new QseSppCompositorController(this);
    sppCompositorController->setControllers(sppControllers);

    m_sppWidget->setGeometry(m_sppWidget->geometry().replaceSamplesPerPixel(-1));
    m_sppWidget->setController(sppCompositorController);

    m_sppWidget->setLimiter(new CSppLimiter(this));

    qDebug() << m_sppWidget->geometry();
    */

    QVector<double> datasamples(100000);
    for (int i = 0; i < 100000; ++i)
        datasamples[i] = (qrand()%100000)/100000.0-0.5;
    CSppSyncPeakDataSource *dataSource = new CSppSyncPeakDataSource(datasamples);

    m_monocolorCoverSppPlot = new QseMonocolorSppCoverPlot(this);

//    m_sppWidget = new QseSppWidget(this);
//    m_sppWidget->setLimiter(new CSppLimiter(this));

    m_sppSignalLinearPlot = new QseSppSyncSignalLinearPlot(this);
    m_sppSignalLinearPlot->setDataSource(dataSource);

    CSppSyncAudacityWidget *audacityWidget = new CSppSyncAudacityWidget(this);
    setCentralWidget(audacityWidget);

}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_action_Test_moncolorplot_triggered()
{
    m_monocolorCoverSppPlot->setColor(Qt::black);
}

void CMainWindow::on_actionAdd_cursor_triggered()
{
    if (m_cursor->isNull())
        m_cursor->setIndex(10);
    else
        m_cursor->setIndex(m_cursor->index()+15);

    m_sppCursorPlot->setProperty("pen", QPen(QColor(Qt::red)));
}

void CMainWindow::on_actionTest_Selection_triggered()
{
    m_selection->setSelectedRange(QseRange(10, 100));
}

void CMainWindow::scrollBar_valueChanged(int value)
{
    m_sppWidget->setGeometry(m_sppWidget->geometry().replaceSamplesPerPixel(value));
    qDebug() << m_sppWidget->geometry();

}

void CMainWindow::scrollBar2_valueChanged(int value)
{
    if (m_sppWidget->geometry().samplesPerPixel() > 0)
    {
        qDebug() << m_sppWidget->geometry().replaceX(value*m_sppWidget->geometry().samplesPerPixel());
        m_sppWidget->setGeometry(m_sppWidget->geometry().replaceX(value*m_sppWidget->geometry().samplesPerPixel()));
    }
    else
    {
        qDebug() << m_sppWidget->geometry().replaceX(value*m_sppWidget->geometry().samplesPerPixel());
        m_sppWidget->setGeometry(m_sppWidget->geometry().replaceX(value));
    }
}
