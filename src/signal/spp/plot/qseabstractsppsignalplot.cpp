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
#include "qseabstractsppsignalplot.h"
#include "qseabstractsppsignalplotdelegate.h"
#include "qseabstractpeakdatasource.h"
#include <QPainter>


QseAbstractSppSignalPlot::QseAbstractSppSignalPlot(QObject *parent) :
    QseAbstractSppPlot(parent)
{
    m_canvasVisible = true;
    m_opacity = 0.1;
    m_brush = Qt::black;

    m_plotDelegate = 0;
    setZeroLine(Middle);
}

void QseAbstractSppSignalPlot::setCanvasOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseAbstractSppSignalPlot::setCanvasBrush(const QBrush &brush)
{
    if (m_brush != brush)
    {
        m_brush = brush;
        setUpdateOnce(true);
    }
}

void QseAbstractSppSignalPlot::setCanvasVisible(bool visible)
{
    if (m_canvasVisible != visible)
    {
        m_canvasVisible = visible;
        setUpdateOnce(true);
    }
}

void QseAbstractSppSignalPlot::setPlotDelegate(
        QseAbstractSppSignalPlotDelegate *plotDelegate)
{
    if (m_plotDelegate == plotDelegate)
        return;

    if (m_plotDelegate)
        disconnect(m_plotDelegate, 0, this, 0);

    m_plotDelegate = plotDelegate;
    if (m_plotDelegate)
    {
        connect(m_plotDelegate, SIGNAL(changed()),
                this, SLOT(plotDelegate_changed()));
        connect(m_plotDelegate, SIGNAL(destroyed()),
                this, SLOT(plotDelegate_destroyed()));
    }

    setUpdateOnce(true);
}

void QseAbstractSppSignalPlot::setZeroLine(
        QseAbstractSppSignalPlot::ZeroLine zeroPoint)
{
    if (m_zeroLine != zeroPoint)
    {
        m_zeroLine = zeroPoint;
        setUpdateOnce(true);
    }
}

bool QseAbstractSppSignalPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

bool QseAbstractSppSignalPlot::isVisible(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (rect.width() == 0
            || !plotDelegate()
            || !usedDataSource() || usedDataSource()->count() == 0)
        return false;

    const qint64 sampleFirst = usedDataSource()->minIndex();
    const qint64 sampleLast = usedDataSource()->maxIndex();

    const qint64 visibleFirst = geometry.x();
    const qint64 visibleLast = visibleFirst
            + QseSppGeometry::samplesFromWidth(geometry, rect.width()) - 1;

    return ((visibleFirst <= sampleLast) && (sampleFirst <= visibleLast));
}

void QseAbstractSppSignalPlot::plotDelegate_changed()
{
    setUpdateOnce(true);
}

void QseAbstractSppSignalPlot::plotDelegate_destroyed()
{
    m_plotDelegate = 0;
}

void QseAbstractSppSignalPlot::drawCanavs(QPainter *painter,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (!isCanvasVisible())
        return;

    const qint64 firstVisibleSample = geometry.x();
    const qint64 lastVisibleSample =
            QseSppGeometry::calcSampleIndex(geometry, rect.width());

    int sl = 0;
    if (usedDataSource()->minIndex() > firstVisibleSample)
        sl = QseSppGeometry::calcOffset(geometry, usedDataSource()->minIndex());

    int sr = rect.width()-1;
    if (usedDataSource()->maxIndex() <= lastVisibleSample)
        sr = QseSppGeometry::calcOffset(geometry, usedDataSource()->maxIndex());

    painter->save();
    painter->setOpacity(m_opacity);
    painter->fillRect(sl, 0, sr-sl+1, rect.height(), m_brush);
    painter->restore();
}
