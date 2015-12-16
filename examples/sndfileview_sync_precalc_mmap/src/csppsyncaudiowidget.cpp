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
#include "qsepositionplot.h"
#include "qseselectionplot.h"
#include "qsesignalcanvasplot.h"
#include "qsesignalplot.h"
#include "qseaxiscanvasplot.h"
#include "qseaudacitycontroller.h"
#include "qsesignallinearplotdelegate.h"
#include "csppsyncpeakdatasource.h"
#include "csppsyncaudiolimiter.h"


CSppSyncAudioWidget::CSppSyncAudioWidget(QWidget *parent, Qt::WindowFlags f)
    : QseWidget(parent, f)
{
    m_dataSource = new CSppSyncPeakDataSource(this);
    connect(m_dataSource, SIGNAL(dataChanged()),
            this, SLOT(dataSource_dataChanged()));

    m_limiter = new CSppSyncAudioLimiter(m_dataSource, this);

    m_playPosition = new QsePosition(this);
    m_playPositionPlot = new QsePositionPlot(this);
    m_playPositionPlot->setPosition(m_playPosition);

    m_cursorPosition = new QsePosition(this);
    m_cursorPositionPlot = new QsePositionPlot(this);
    m_cursorPositionPlot->setPosition(m_cursorPosition);

    m_selection = new QseSelection(this);
    m_selectionPlot = new QseSelectionPlot(this);
    m_selectionPlot->setSelection(m_selection);

    m_controller = new QseAudacityController(this);
    m_controller->setPosition(m_cursorPosition);
    m_controller->setSelection(m_selection);
    setController(m_controller);

    m_canvasPlot = new QseAxisCanvasPlot(this);
    m_signalCanvasPlot = new QseSignalCanvasPlot(this);
    m_signalCanvasPlot->setDataSource(m_dataSource);
    m_signalPlot = new QseSignalPlot(this);
    m_signalPlot->setDataSource(m_dataSource);
    m_plotDelegate = new QseSignalLinearPlotDelegate(this);
    m_signalPlot->setPlotDelegate(m_plotDelegate);

    QList<QseAbstractPlot *> cachedPlots;
    cachedPlots << m_canvasPlot;
    cachedPlots << m_signalCanvasPlot;
    cachedPlots << m_signalPlot;

    QList<QseAbstractPlot *> postUncachedPlots;
    postUncachedPlots << m_selectionPlot;
    postUncachedPlots << m_playPositionPlot;
    postUncachedPlots << m_cursorPositionPlot;

    setCachedPlots(cachedPlots);
    setPostUncachedPlots(postUncachedPlots);
    setLimiter(m_limiter);
}

void CSppSyncAudioWidget::dataSource_dataChanged()
{
    QseRange avaibleRange(m_dataSource->minIndex(), m_dataSource->maxIndex());
    m_playPosition->setAvailableRange(avaibleRange);
    m_cursorPosition->setAvailableRange(avaibleRange);
    m_selection->setAvailableRange(avaibleRange);
}
