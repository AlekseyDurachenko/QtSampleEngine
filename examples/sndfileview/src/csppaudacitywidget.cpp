// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "csppaudacitywidget.h"
#include "qsecursor.h"
#include "qseselection.h"
#include "qsesppcursorplot.h"
#include "qsesppselectionplot.h"
#include "qsesppsyncsignallinearplot.h"
#include "qsesppaxiscoverplot.h"
#include "qsesppaudacitycontroller.h"
#include "csppsyncdatasource.h"
#include "cspplimiter.h"


CSppSyncAudacityWidget::CSppSyncAudacityWidget(QWidget *parent,
        Qt::WindowFlags f) : QseSppWidget(parent, f)
{
    // TEMPORARY_START
    QVector<double> datasamples(100000);
    for (int i = 0; i < 100000; ++i)
        datasamples[i] = (qrand()%100000)/100000.0-0.5;
    // TEMPORARY_END

    m_dataSource = new CSppSyncDataSource(datasamples, this);
    m_limiter = new CSppLimiter(this);

    m_playPosition = new QseCursor(this);
    m_playPosition->setAvailableRange(QseRange(0, m_dataSource->count()));
    m_playPositionPlot = new QseSppCursorPlot(this);
    m_playPositionPlot->setCursor(m_playPosition);

    m_currentPosition = new QseCursor(this);
    m_currentPosition->setAvailableRange(QseRange(0, m_dataSource->count()));
    m_currentPositionPlot = new QseSppCursorPlot(this);
    m_currentPositionPlot->setCursor(m_currentPosition);

    m_selection = new QseSelection(this);
    m_selection->setAvailableRange(QseRange(0, m_dataSource->count()));
    m_selectionPlot = new QseSppSelectionPlot(this);
    m_selectionPlot->setSelection(m_selection);

    m_controller = new QseSppAudacityController(this);
    m_controller->setCurrentPosition(m_currentPosition);
    m_controller->setSelection(m_selection);
    setController(m_controller);

    m_coverPlot = new QseSppAxisCoverPlot(this);
    m_signalPlot = new QseSppSyncSignalLinearPlot(this);
    m_signalPlot->setDataSource(m_dataSource);

    QList<QseAbstractSppPlot *> cachedPlots;
    cachedPlots << m_coverPlot;
    cachedPlots << m_signalPlot;

    QList<QseAbstractSppPlot *> postUncachedPlots;
    postUncachedPlots << m_selectionPlot;
    postUncachedPlots << m_playPositionPlot;
    postUncachedPlots << m_currentPositionPlot;

    setCachedPlots(cachedPlots);
    setPostUncachedPlots(postUncachedPlots);
    setLimiter(m_limiter);
}
