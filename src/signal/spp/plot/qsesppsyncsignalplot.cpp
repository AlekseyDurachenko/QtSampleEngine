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
    setZeroLine(Middle);
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
    if (rect.width() == 0
            || !m_plotDelegate
            || !m_dataSource || m_dataSource->count() == 0)
        return false;

    const qint64 sampleFirst = m_dataSource->minIndex();
    const qint64 sampleLast = m_dataSource->maxIndex();

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
        if (hasChanges(rect, geometry))
            calcPeaks(rect, geometry);

        if (m_peaks.isEmpty())
            return;

        // first index of visible part of peaks
        qint64 firstIndex = 0;
        if (m_peaksFirstIndex < geometry.x())
            firstIndex = geometry.x() - m_peaksFirstIndex;
        if (geometry.samplesPerPixel() > 0)
            firstIndex /= geometry.samplesPerPixel();
        // all peaks are invisible
        if (firstIndex >= m_peaks.count())
            return;

        // free space in pixels between left bound and first peaks
        int space = 0;
        if (m_peaksFirstIndex > geometry.x())
            space = QseSppGeometry::widthFromSamples(
                        geometry, m_peaksFirstIndex - geometry.x());

        // this value will be added to the y coordiante of the each peaks
        double dy = calcDy(rect);

        // draw the peaks
        if (m_peaks.hasMaximums())
            m_plotDelegate->drawAsPeaks(painter, rect, geometry,
                    m_peaks, firstIndex, space, 0, dy);
        else
            m_plotDelegate->drawAsLines(painter, rect, geometry,
                    m_peaks, firstIndex, space, 0, dy);
    }

    QseAbstractSppSignalPlot::draw(painter, rect, geometry);
}

void QseSppSyncSignalPlot::dataSource_dataChanged()
{
    // peaks should be recalculated on update
    m_peaks = QsePeakArray();
    setUpdateOnce(true);
}

void QseSppSyncSignalPlot::dataSource_dataChanged(qint64 /*first*/,
        qint64 /*last*/)
{
    // TODO: update only if changes is visible
    // * if changes inside the cached peaks, replase changed peaks
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

void QseSppSyncSignalPlot::calcPeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_peaks.isEmpty()
            || !checkOptimizationPossibility(lastGeometry(), geometry))
    {
        recalcPeaks(rect, geometry);
    }
    else
    {
        compressPeaks(lastGeometry(), geometry);
        pushFrontPeaks(geometry);
        pushBackPeaks(geometry, rect.width());
    }
}

void QseSppSyncSignalPlot::recalcPeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    qint64 x = geometry.x();
    if (x < m_dataSource->minIndex())
        x = m_dataSource->minIndex();
    const qint64 &spp = geometry.samplesPerPixel();

    m_peaks = m_dataSource->read(x, spp, rect.width());
    m_peaksFirstIndex = x;
}

bool QseSppSyncSignalPlot::checkOptimizationPossibility(
        const QseSppGeometry &oldGeometry, const QseSppGeometry &newGeometry)
{
    // does not make sense to optimize what quickly read (4 is empiric)
    if (newGeometry.samplesPerPixel() < 4)
        return false;
    // can't optimize if sign of samplePerPixel is different
    if (oldGeometry.samplesPerPixel() < 0)
        return false;

    // zoom in: can't optimize
    if (oldGeometry.samplesPerPixel() > newGeometry.samplesPerPixel())
        return false;

    // zoom out: we can't recalculate the peaks if (newValue % oldValue != 0)
    if (oldGeometry.samplesPerPixel() < newGeometry.samplesPerPixel())
        if (newGeometry.samplesPerPixel() % oldGeometry.samplesPerPixel() != 0)
            return false;

    // scroll x: we can't recalculate the peaks if (value % spp != 0)
    if (newGeometry.x() % newGeometry.samplesPerPixel() != 0)
        return false;

    return true;
}

void QseSppSyncSignalPlot::compressPeaks(const QseSppGeometry &oldGeometry,
        const QseSppGeometry &newGeometry)
{
    if (oldGeometry.samplesPerPixel() == newGeometry.samplesPerPixel())
        return;

    const qint64 &oldSpp = oldGeometry.samplesPerPixel();
    const qint64 &newSpp = newGeometry.samplesPerPixel();
    const qint64 newCount = (m_peaks.count() * oldSpp) / newSpp;
    const qint64 compressLevel = newSpp / oldSpp;
    const QVector<double> &oldMinimums = m_peaks.minimums();
    const QVector<double> &oldMaximums = m_peaks.maximums();
    QVector<double> newMinimums = QVector<double>(newCount);
    QVector<double> newMaximums = QVector<double>(newCount);

    for (qint64 newIndex = 0; newIndex < newCount; ++newIndex)
    {
        double minimum = oldMinimums[newIndex*compressLevel];
        double maximum = oldMaximums[newIndex*compressLevel];

        for (qint64 c = 0; c < compressLevel; ++c)
        {
            const double curmin = oldMinimums[newIndex*compressLevel+c];
            const double curmax = oldMaximums[newIndex*compressLevel+c];
            if (curmin < minimum)
                minimum = curmin;
            if (curmax > maximum)
                maximum = curmax;
        }

        newMinimums[newIndex] = minimum;
        newMaximums[newIndex] = maximum;
    }

    m_peaks = QsePeakArray(newMinimums, newMaximums);
}

void QseSppSyncSignalPlot::pushFrontPeaks(const QseSppGeometry &geometry)
{
    if (geometry.x() >= m_peaksFirstIndex)
        return;

    if (m_peaksFirstIndex <= m_dataSource->minIndex())
        return;

    qint64 firstIndex = 0;
    if (geometry.x() < m_dataSource->minIndex())
        firstIndex = m_dataSource->minIndex();
    else
        firstIndex = geometry.x();

    const qint64 &spp = geometry.samplesPerPixel();
    const qint64 sampleCount = m_peaksFirstIndex - firstIndex;
    const qint64 peakCount = sampleCount/spp + ((sampleCount%spp) ? (1) : (0));

    m_peaks = m_dataSource->read(firstIndex, spp, peakCount, true) + m_peaks;
    m_peaksFirstIndex = firstIndex;
}

void QseSppSyncSignalPlot::pushBackPeaks(const QseSppGeometry &geometry,
        int width)
{
    const qint64 &spp = geometry.samplesPerPixel();
    const qint64 lastIndex = m_peaksFirstIndex + m_peaks.count()*spp - 1;

    if (lastIndex >= m_dataSource->maxIndex())
        return;

    int alreadyVisibleWidth = 0;
    if (geometry.x() >= m_peaksFirstIndex)
        alreadyVisibleWidth =
                m_peaks.count() - (geometry.x() - m_peaksFirstIndex)/spp;
    else
        alreadyVisibleWidth =
                m_peaks.count() + (m_peaksFirstIndex - geometry.x())/spp;

    const int neededWidth = width - alreadyVisibleWidth;
    if (neededWidth <= 0)
        return;

    m_peaks = m_peaks + m_dataSource->read(lastIndex+1, spp, neededWidth);
}
