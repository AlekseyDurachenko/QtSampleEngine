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
#include "qsesppsyncsignalplot.h"
#include <QPainter>
#include "qseabstractsppsyncpeakdatasource.h"
#include "qseabstractsppsignalplotdelegate.h"
#include <QDebug>


QseSppSyncSignalPlot::QseSppSyncSignalPlot(QObject *parent) :
    QseAbstractSppSignalPlot(parent)
{
    m_plotDelegate = 0;
    m_dataSource = 0;
    m_hasDataChanges = false;
    setZeroPoint(Middle);
}

void QseSppSyncSignalPlot::setDataSource(
        QseAbstractSppSyncPeakDataSource *dataSource)
{
    if (m_dataSource == dataSource)
        return;

    if (m_dataSource)
        disconnect(m_dataSource, 0, this, 0);

    m_dataSource = dataSource;
    if (m_dataSource)
    {
        connect(m_dataSource, SIGNAL(dataChanged()),
                this, SLOT(dataSource_dataChanged()));
        connect(m_dataSource, SIGNAL(dataChanged(qint64,qint64)),
                this, SLOT(dataSource_dataChanged(qint64,qint64)));
        connect(m_dataSource, SIGNAL(destroyed()),
                this, SLOT(dataSource_destroyed()));
    }

    m_hasDataChanges = true;
    setUpdateOnce(true);
}

void QseSppSyncSignalPlot::setPlotDelegate(
        QseAbstractSppSignalPlotDelegate *plotDelegate)
{
    if (m_plotDelegate == plotDelegate)
        return;

    if (m_plotDelegate)
        disconnect(m_plotDelegate, 0, this, 0);

    m_plotDelegate = plotDelegate;
    if (m_dataSource)
    {
        connect(m_plotDelegate, SIGNAL(changed()),
                this, SLOT(plotDelegate_changed()));
        connect(m_plotDelegate, SIGNAL(destroyed()),
                this, SLOT(plotDelegate_destroyed()));
    }

    setUpdateOnce(true);
}

bool QseSppSyncSignalPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

bool QseSppSyncSignalPlot::isVisible(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (!m_plotDelegate
            || rect.width() == 0
            || !m_dataSource || m_dataSource->count() == 0)
        return false;

    const qint64 sampleFirst = 0;
    const qint64 sampleLast = m_dataSource->count()-1;

    const qint64 visibleFirst = geometry.x();
    const qint64 visibleLast = visibleFirst
            + QseSppGeometry::samplesFromWidth(geometry, rect.width()) - 1;

    return ((visibleFirst <= sampleLast) && (sampleFirst <= visibleLast));
}

void QseSppSyncSignalPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        QsePeakArray peaks = readPeaks(rect, geometry);
        if (!peaks.isEmpty())
        {
            int offset = 0;
            if (geometry.x() < 0)
                offset = geometry.x();

            double dy = calcDy(rect);

            painter->save();
            painter->setPen(pen());
            painter->setOpacity(opacity());
            if (peaks.hasMaximums())
                m_plotDelegate->drawAsPeaks(painter, rect, geometry,
                        peaks, offset, 0, dy);
            else
                m_plotDelegate->drawAsLines(painter, rect, geometry,
                        peaks, offset, 0, dy);
            painter->restore();
        }
    }

    QseAbstractSppSignalPlot::draw(painter, rect, geometry);
}

void QseSppSyncSignalPlot::dataSource_dataChanged()
{
    m_hasDataChanges = true;
    setUpdateOnce(true);
}

void QseSppSyncSignalPlot::dataSource_dataChanged(qint64 first,
        qint64 last)
{
    Q_UNUSED(first);
    Q_UNUSED(last);

    dataSource_dataChanged();
}

void QseSppSyncSignalPlot::dataSource_destroyed()
{
    m_dataSource = 0;
}

void QseSppSyncSignalPlot::plotDelegate_changed()
{
    setUpdateOnce(true);
}

void QseSppSyncSignalPlot::plotDelegate_destroyed()
{
    m_plotDelegate = 0;
}

int QseSppSyncSignalPlot::calcDy(const QRect &rect)
{
    switch (zeroPoint())
    {
    case Top:
        return 0;
    case Middle:
        return rect.height()/2.0;
    case Bottom:
        return rect.height();
    }

    return 0;
}

bool QseSppSyncSignalPlot::peaksMayChanged(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (hasDataChanges())
        return true;

    if (rect.width() != lastRect().width())
        return true;

    if (geometry.x() != lastGeometry().x())
        return true;

    if (geometry.samplesPerPixel() != lastGeometry().samplesPerPixel())
        return true;

    return false;
}

QsePeakArray QseSppSyncSignalPlot::readPeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (geometry.samplesPerPixel() < 2)
    {
        QsePeakArray peaks = dataSource()->read(geometry, rect.width());
        m_lastPeaks = peaks;
        resetDataChanges();

        return peaks;
    }

    if (!peaksMayChanged(rect, geometry))
        return m_lastPeaks;

    if (geometry.x() == lastGeometry().x()
            && geometry.samplesPerPixel() == lastGeometry().samplesPerPixel())
    {
        // visible range desrised
        if (rect.width() < lastRect().width())
            return m_lastPeaks;

        // samples already readed
        if (rect.width() < m_lastPeaks.count())
            return m_lastPeaks;

        // if all samples visible, do not try to read more samples
        qint64 lastVisibleSample = QseSppGeometry::calcSampleIndex(
                    geometry, m_lastPeaks.count());
        if (lastVisibleSample >= dataSource()->count())
            return m_lastPeaks;

        // read only new visible samples
        int unusedVisibleWidth = rect.width()-m_lastPeaks.count();
        QsePeakArray peaks = dataSource()->read(
                    geometry.replaceX(lastVisibleSample), unusedVisibleWidth);

        QsePeakArray result(m_lastPeaks.minimums() + peaks.minimums(),
                            m_lastPeaks.maximums() + peaks.maximums());

        m_lastPeaks = result;
        resetDataChanges();

        return result;
    }
    else if (geometry.x() != lastGeometry().x()
             && geometry.samplesPerPixel() == lastGeometry().samplesPerPixel()
             && rect.width() == lastRect().width())
    {
        if (geometry.x() > lastGeometry().x())
        {
            qint64 lastVisibleSample = QseSppGeometry::calcSampleIndex(geometry, m_lastPeaks.count());
            int scrollWidth = (geometry.x() - lastGeometry().x()) / geometry.samplesPerPixel();
            QsePeakArray peaks = dataSource()->read(
                        geometry.replaceX(lastVisibleSample), scrollWidth);

            QVector<double> minimums = m_lastPeaks.minimums();
            QVector<double> maximums = m_lastPeaks.maximums();
            if (scrollWidth > minimums.count())
                scrollWidth = minimums.count();
            minimums.remove(0, scrollWidth);
            maximums.remove(0, scrollWidth);

            QsePeakArray result(minimums + peaks.minimums(),
                                maximums + peaks.maximums());

            m_lastPeaks = result;
            resetDataChanges();

            return result;
        }
        else
        {
            int scrollWidth = (lastGeometry().x() - geometry.x()) / geometry.samplesPerPixel();
            QsePeakArray peaks = dataSource()->read(geometry, scrollWidth);

            QsePeakArray result(peaks.minimums() + m_lastPeaks.minimums(),
                                peaks.maximums() + m_lastPeaks.maximums());

            m_lastPeaks = result;
            resetDataChanges();

            return result;
        }
    }

    QsePeakArray peaks = dataSource()->read(geometry, rect.width());
    m_lastPeaks = peaks;
    resetDataChanges();

    return peaks;
}


bool QseSppSyncSignalPlot::hasDataChanges() const
{
    return m_hasDataChanges;
}

void QseSppSyncSignalPlot::resetDataChanges()
{
    m_hasDataChanges = false;
}
