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
#include "csppsyncaudiowidget.h"
#include "qseposition.h"
#include "qseselection.h"
#include "qsespppositionplot.h"
#include "qsesppselectionplot.h"
#include "qsesppsyncsignalplot.h"
#include "qsesppaxiscoverplot.h"
#include "qsesppaudacitycontroller.h"
#include "qsesppsignallinearplotdelegate.h"
#include "csppsyncpeakdatasource.h"
#include "csppsyncaudiolimiter.h"


CSppSyncAudioWidget::CSppSyncAudioWidget(QWidget *parent,
        Qt::WindowFlags f) : QseSppWidget(parent, f)
{
    m_dataSource = new CSppSyncPeakDataSource(this);
    connect(m_dataSource, SIGNAL(dataChanged()),
            this, SLOT(dataSource_dataChanged()));

    m_limiter = new CSppSyncAudioLimiter(m_dataSource, this);

    m_playPosition = new QsePosition(this);
    m_playPositionPlot = new QseSppPositionPlot(this);
    m_playPositionPlot->setPosition(m_playPosition);

    m_cursorPosition = new QsePosition(this);
    m_cursorPositionPlot = new QseSppPositionPlot(this);
    m_cursorPositionPlot->setPosition(m_cursorPosition);

    m_selection = new QseSelection(this);
    m_selectionPlot = new QseSppSelectionPlot(this);
    m_selectionPlot->setSelection(m_selection);

    m_controller = new QseSppAudacityController(this);
    m_controller->setPosition(m_cursorPosition);
    m_controller->setSelection(m_selection);
    setController(m_controller);

    m_coverPlot = new QseSppAxisCoverPlot(this);
    m_signalPlot = new QseSppSyncSignalPlot(this);
    m_signalPlot->setDataSource(m_dataSource);
    m_plotDelegate = new QseSppSignalLinearPlotDelegate(this);
    m_signalPlot->setPlotDelegate(m_plotDelegate);

    QList<QseAbstractSppPlot *> cachedPlots;
    cachedPlots << m_coverPlot;
    cachedPlots << m_signalPlot;

    QList<QseAbstractSppPlot *> postUncachedPlots;
    postUncachedPlots << m_selectionPlot;
    postUncachedPlots << m_playPositionPlot;
    postUncachedPlots << m_cursorPositionPlot;

    setCachedPlots(cachedPlots);
    setPostUncachedPlots(postUncachedPlots);
    setLimiter(m_limiter);
}

void CSppSyncAudioWidget::dataSource_dataChanged()
{
    QseRange avaibleRange(0, m_dataSource->count()-1);
    m_playPosition->setAvailableRange(avaibleRange);
    m_cursorPosition->setAvailableRange(avaibleRange);
    m_selection->setAvailableRange(avaibleRange);
}
