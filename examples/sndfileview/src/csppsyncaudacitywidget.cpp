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
#include "csppsyncaudacitywidget.h"
#include "qseposition.h"
#include "qseselection.h"
#include "qsespppositionplot.h"
#include "qsesppselectionplot.h"
#include "qsesppsyncsignallinearplot.h"
#include "qsesppaxiscoverplot.h"
#include "qsesppaudacitycontroller.h"
#include "csppsyncpeakdatasource.h"
#include "csppsyncaudacitylimiter.h"


CSppSyncAudacityWidget::CSppSyncAudacityWidget(QWidget *parent,
        Qt::WindowFlags f) : QseSppWidget(parent, f)
{
    m_dataSource = new CSppSyncPeakDataSource(this);
    connect(m_dataSource, SIGNAL(dataChanged()),
            this, SLOT(dataSource_dataChanged()));

    m_limiter = new CSppSyncAudacityLimiter(m_dataSource, this);

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
    m_signalPlot = new QseSppSyncSignalLinearPlot(this);
    m_signalPlot->setDataSource(m_dataSource);

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

void CSppSyncAudacityWidget::dataSource_dataChanged()
{
    QseRange avaibleRange(0, m_dataSource->count()-1);
    m_playPosition->setAvailableRange(avaibleRange);
    m_cursorPosition->setAvailableRange(avaibleRange);
    m_selection->setAvailableRange(avaibleRange);
}
