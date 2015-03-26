// Copyright 2013-2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "qsesppsyncsignallinearplot.h"
#include <QPainter>
#include "qseabstractsppsyncpeakdatasource.h"
#include "qsehelper.h"


QseSppSyncSignalLinearPlot::QseSppSyncSignalLinearPlot(QObject *parent) :
    QseAbstractSppSyncSignalPlot(parent)
{
    setZeroPoint(Middle);
}

void QseSppSyncSignalLinearPlot::draw(QPainter *painter, const QRect &rect,
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

            painter->save();
            painter->setPen(pen());
            painter->setOpacity(opacity());
            if (peaks.hasMaximums())
                drawAsPeaks(painter, peaks, rect, geometry, offset);
            else
                drawAsLines(painter, peaks, rect, geometry, offset);
            painter->restore();
        }
    }

    QseAbstractSppSyncSignalPlot::draw(painter, rect, geometry);
}

void QseSppSyncSignalLinearPlot::drawAsLines(QPainter *painter,
        const QsePeakArray &peaks, const QRect &rect,
        const QseSppGeometry &geometry, int offset)
{
    const qint64 pps = -geometry.samplesPerPixel();
    const QVector<double> &points = peaks.minimums();

    double zero = 0;
    switch (zeroPoint())
    {
    case Top:
        zero = 0;
        break;
    case Middle:
        zero = rect.height()/2.0;
        break;
    case Bottom:
        zero = rect.height();
        break;
    }

    int space = 0; // skip pixel from left bound
    int first = 0; // index of first visible points
    if (offset < 0)
        space = pps * -offset;
    else
        first = offset;

    for (int i = first+1; i < points.count(); ++i)
    {
        double x1 = space + (i-1-first)*pps;
        double x2 = x1 + pps;
        double y1 = zero-(geometry.y()+points[i-1])*rect.height()/geometry.height();
        double y2 = zero-(geometry.y()+points[i])*rect.height()/geometry.height();

        if (x1 >= rect.width())
            break;

        if ((y1 < 0 && y2 < 0) || (y1 >= rect.height() && y2 >= rect.height()))
            continue;

        double yy1 = y1;
        double yy2 = y2;
        double xx1 = x1;
        double xx2 = x2;

        if (y1 >= rect.height())
            Qse::calcIntersection(x1, y1, x2, y2, x1, rect.height()-1, x2, rect.height()-1, xx1, yy1);
        if (y2 >= rect.height())
            Qse::calcIntersection(x1, y1, x2, y2, x1, rect.height()-1, x2, rect.height()-1, xx2, yy2);
        if (y1 < 0)
            Qse::calcIntersection(x1, y1, x2, y2, x1, 0, x2, 0, xx1, yy1);
        if (y2 < 0)
            Qse::calcIntersection(x1, y1, x2, y2, x1, 0, x2, 0, xx2, yy2);

        painter->drawLine(QPointF(xx1, yy1), QPointF(xx2, yy2));
    }
}

void QseSppSyncSignalLinearPlot::drawAsPeaks(QPainter *painter,
        const QsePeakArray &peaks, const QRect &rect,
        const QseSppGeometry &geometry, int offset)
{
    const QVector<double> &minimums = peaks.minimums();
    const QVector<double> &maximums = peaks.maximums();

    double zero = 0;
    switch (zeroPoint())
    {
    case Top:
        zero = 0;
        break;
    case Middle:
        zero = rect.height()/2.0;
        break;
    case Bottom:
        zero = rect.height();
        break;
    }

    int space = 0; // skip pixel from left bound
    int first = 0; // index of first visible minimum(maximum)
    if (offset < 0)
        space = -offset / geometry.samplesPerPixel();
    else
        first = offset;

    if (first >= maximums.count())
        return;

    double prevMin = zero-(geometry.y()+minimums[first])*rect.height()/geometry.height();
    double prevMax = zero-(geometry.y()+maximums[first])*rect.height()/geometry.height();
    double x1 = space;
    double x2 = space;
    if (x1 >= rect.width())
        return;
    if (prevMin < 0.0) prevMin = 0.0;
    if (prevMax < 0.0) prevMax = 0.0;
    if (prevMin >= rect.height()) prevMin = rect.height()-1;
    if (prevMax >= rect.height()) prevMax = rect.height()-1;
    if (prevMin == prevMax)
        painter->drawPoint(QPointF(x1, prevMin));
    else
        painter->drawLine(QPointF(x1, prevMin), QPointF(x2, prevMax));

    for (int i = first+1; i < minimums.count(); ++i)
    {
        x1 = space + i - first;
        x2 = space + i - first;
        if (x1 >= rect.width())
            break;
        double curMin = zero-(geometry.y()+minimums[i])*rect.height()/geometry.height();
        double curMax = zero-(geometry.y()+maximums[i])*rect.height()/geometry.height();
        if (! ((curMin < 0.0 && curMax < 0.0)
              || (curMin >= rect.height() && curMax >= rect.height())))
        {
            if (curMin < 0.0) curMin = 0.0;
            if (curMax < 0.0) curMax = 0.0;
            if (curMin >= rect.height()) curMin = rect.height()-1;
            if (curMax >= rect.height()) curMax = rect.height()-1;

            // fill the gap between the two lines, if exists
            if (curMin < prevMax) curMin = prevMax-1;
            if (curMax > prevMin) curMax = prevMin+1;

            //
            prevMin = curMin;
            prevMax = curMax;

            if (curMin == curMax)
                painter->drawPoint(QPointF(x1, curMin));
            else
                painter->drawLine(QPointF(x1, curMin), QPointF(x2, curMax));
        }
    }
}

QsePeakArray QseSppSyncSignalLinearPlot::readPeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (geometry.samplesPerPixel() < 2)
    {
        QsePeakArray peaks = dataSource()->read(geometry, rect.width());
        m_lastPeaks = peaks;
        resetDataChanges();

        return peaks;
    }

    if (!isPeaksMayChanged(rect, geometry))
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

bool QseSppSyncSignalLinearPlot::isPeaksMayChanged(const QRect &rect,
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
