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
#include "qsesignalplot.h"
#include "qseabstractsignaldatasource.h"
#include "qseabstractsignalplotdelegate.h"
#include <QPainter>
#include <QDebug>

QseSignalPlot::QseSignalPlot(QObject *parent)
    : QseAbstractPlot(parent)
{
    m_dataSource = 0;
    m_plotDelegate = 0;
    m_zeroLine = Middle;

    m_minimums = new double[8192];
    m_maximums = new double[8192];
}

QseSignalPlot::~QseSignalPlot()
{
    delete []m_minimums;
    delete []m_maximums;
}

void QseSignalPlot::setDataSource(QseAbstractSignalDataSource *dataSource)
{
    if (m_dataSource == dataSource) {
        return;
    }

    if (m_dataSource) {
        disconnect(m_dataSource, 0, this, 0);
    }

    m_dataSource = dataSource;
    if (m_dataSource) {
        connect(m_dataSource, SIGNAL(dataChanged()),
                this, SLOT(dataSource_dataChanged()));
        connect(m_dataSource, SIGNAL(destroyed()),
                this, SLOT(dataSource_destroyed()));
    }

    setUpdateOnce(true);
}

void QseSignalPlot::setPlotDelegate(QseAbstractSignalPlotDelegate *plotDelegate)
{
    if (m_plotDelegate == plotDelegate) {
        return;
    }

    if (m_plotDelegate) {
        disconnect(m_plotDelegate, 0, this, 0);
    }

    m_plotDelegate = plotDelegate;
    if (m_plotDelegate) {
        connect(m_plotDelegate, SIGNAL(changed()),
                this, SLOT(plotDelegate_changed()));
        connect(m_plotDelegate, SIGNAL(destroyed()),
                this, SLOT(plotDelegate_destroyed()));
    }

    setUpdateOnce(true);
}

void QseSignalPlot::setZeroLine(QseSignalPlot::ZeroLine zeroLine)
{
    if (m_zeroLine != zeroLine) {
        m_zeroLine = zeroLine;
        setUpdateOnce(true);
    }
}

bool QseSignalPlot::hasChanges(const QRect &rect, const QseGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

bool QseSignalPlot::isVisible(const QRect &rect, const QseGeometry &geometry)
{
    if (!isEnabled()
            || rect.width() == 0
            || !plotDelegate()
            || !dataSource()
            || dataSource()->count() == 0) {
        return false;
    }

    const qint64 sampleFirst = dataSource()->minIndex();
    const qint64 sampleLast = dataSource()->maxIndex();

    const qint64 visibleFirst = geometry.x();
    const qint64 visibleLast = visibleFirst + QseGeometry::samplesFromWidth(geometry, rect.width()) - 1;

    return ((visibleFirst <= sampleLast) && (sampleFirst <= visibleLast));
}

void QseSignalPlot::draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry)
{

    if (!isVisible(rect, geometry)) {
        return;
    }

    // this value will be added to the y coordiante of the each point
    double dy = 0;
    if (m_zeroLine == Middle) {
        dy = rect.height() / 2.0;
    }
    else if (m_zeroLine == Bottom) {
        dy = rect.height();
    }

    // offset from left bound
    qint64 space = 0;
    // first readed sample index
    qint64 first = geometry.x();
    if (geometry.x() < m_dataSource->minIndex()) {
        first = m_dataSource->minIndex();
        space = QseGeometry::widthFromSamples(geometry, m_dataSource->minIndex() - geometry.x());
    }

    if (geometry.spp() > 0) {
        qint64 count = rect.width() - space;
        count = m_dataSource->readAsPeaks(m_minimums, m_maximums,
                                          first, geometry.spp(), count);
        if (count) {
            plotDelegate()->drawAsPeaks(painter, rect, geometry,
                                        m_minimums, m_maximums, count,
                                        space, dy);
        }
    }
    else {
        qint64 count = QseGeometry::samplesFromWidth(geometry, rect.width() - space) + 1;
        count = m_dataSource->readAsPoints(m_minimums, first, count);
        if (count) {
            plotDelegate()->drawAsPoints(painter, rect, geometry,
                                         m_minimums, count,
                                         space, dy);
        }
    }
}

void QseSignalPlot::dataSource_dataChanged()
{
    setUpdateOnce(true);
}

void QseSignalPlot::dataSource_destroyed()
{
    m_dataSource = 0;
    setUpdateOnce(true);
}

void QseSignalPlot::plotDelegate_changed()
{
    setUpdateOnce(true);
}

void QseSignalPlot::plotDelegate_destroyed()
{
    m_plotDelegate = 0;
    setUpdateOnce(true);
}
