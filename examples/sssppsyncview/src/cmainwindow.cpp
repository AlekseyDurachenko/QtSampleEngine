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
#include "csppsyncdatasource.h"
#include "qsesppsyncsignallinearplot.h"
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
qDebug() << DBL_MAX_10_EXP << 5e307 << 5e-308;
    QVector<double> datasamples(100000);
    for (int i = 0; i < 100000; ++i)
        //datasamples[i] = ((qrand()%1000)/1000.0-0.5)*sin(i);
        //datasamples[i] = 1.0*sin(i/100.0);
        datasamples[i] = (qrand()%100000)/100000.0-0.5;
    CSppSyncDataSource *dataSource = new CSppSyncDataSource(datasamples);

    m_sppWidget = new QseSppWidget(this);
    m_monocolorCoverSppPlot = new QseMonocolorSppCoverPlot(this);

    m_cursor = new QseCursor(this);
    m_cursor->setAvailableRange(QseRange(0, 1000));
    m_sppCursorPlot = new QseSppCursorPlot(this);
    m_sppCursorPlot->setCursor(m_cursor);

    m_selection = new QseSelection(this);
    m_selection->setAvailableRange(QseRange(0, 1000));
    m_sppSelectionPlot = new QseSppSelectionPlot(this);
    m_sppSelectionPlot->setSelection(m_selection);

    m_sppSignalLinearPlot = new QseSppSyncSignalLinearPlot(this);
    m_sppSignalLinearPlot->setDataSource(dataSource);

    QList<QseAbstractSppPlot *> preUncachedPlots;
    preUncachedPlots << m_monocolorCoverSppPlot;

    QList<QseAbstractSppPlot *> cachedPlots;
    cachedPlots << m_sppSignalLinearPlot;

    QList<QseAbstractSppPlot *> postUncachedPlots;
    postUncachedPlots << m_sppSelectionPlot;
    postUncachedPlots << m_sppCursorPlot;

    m_sppWidget->setPreUncachedPlot(preUncachedPlots);
    m_sppWidget->setCachedPlot(cachedPlots);
    m_sppWidget->setPostUncachedPlot(postUncachedPlots);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    layout->addWidget(m_sppWidget);
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

    m_sppWidget->setGeometry(m_sppWidget->geometry().replaceSamplesPerPixel(-1));
    qDebug() << m_sppWidget->geometry();
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
