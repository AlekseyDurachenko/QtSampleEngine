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
#include "csppsyncpeakdatasource.h"
#include <QDebug>

CSppSyncPeakDataSource::CSppSyncPeakDataSource(QObject *parent) :
    QseAbstractSppSyncPeakDataSource(parent)
{
}

qint64 CSppSyncPeakDataSource::count() const
{
    return m_samples.count();
}

qint64 CSppSyncPeakDataSource::minIndex() const
{
    return 0;
}

qint64 CSppSyncPeakDataSource::maxIndex() const
{
    return m_samples.count()-1;
}

void CSppSyncPeakDataSource::setSamples(const QVector<double> &samples,
        double sampleRate)
{
    m_samples = samples;
    m_sampleRate = sampleRate;

    emit dataChanged();
}

QsePeakArray CSppSyncPeakDataSource::read(const QseSppGeometry &geometry,
        int width)
{
    const qint64 spp = geometry.samplesPerPixel();
    const qint64 x = geometry.x();

    if (spp > 0)
        return readAsPeaks(x, spp, width);
    else
        return readAsLines(x, -spp, width);
}

QsePeakArray CSppSyncPeakDataSource::readAsLines(qint64 first, qint64 pps,
        int width)
{
    if (first >= m_samples.count())
        return QsePeakArray();

    qint64 last = first + width/pps + ((width%pps) ? (1) : (0));
    if (last >= m_samples.count())
        last = m_samples.count() - 1;

    if (last < 0)
        return QsePeakArray();

    if (first < 0)
        first = 0;

    QVector<double> points(last-first+1);
    for (qint64 i = first; i <= last; ++i)
        points[i-first] = m_samples[i];

    return QsePeakArray(points);
}

QsePeakArray CSppSyncPeakDataSource::readAsPeaks(qint64 first, qint64 spp,
        int width)
{
    if (first >= m_samples.count())
        return QsePeakArray();

    qint64 last = first + width*spp - 1;
    if (last >= m_samples.count())
        last = m_samples.count() - 1;

    if (last < 0)
        return QsePeakArray();

    if (first < 0)
        first = 0;

    const qint64 count = (last-first+1)/spp + (((last-first+1)%spp) ? (1) : (0));
    QVector<double> minimums(count);
    QVector<double> maximums(count);
    for (qint64 arrIndex = 0; arrIndex < count; ++arrIndex)
    {
        const qint64 sampleFirstIndex = first + arrIndex*spp;
        qint64 sampleLastIndex = sampleFirstIndex + spp - 1;
        if (sampleLastIndex >= m_samples.count())
            sampleLastIndex = m_samples.count() - 1;

        double min;
        double max;
        min = max = m_samples[sampleFirstIndex];
        for (int i = sampleFirstIndex+1; i <= sampleLastIndex; ++i)
        {
            if (m_samples[i] < min)
                min = m_samples[i];
            else if (m_samples[i] > max)
                max = m_samples[i];
        }

        minimums[arrIndex] = min;
        maximums[arrIndex] = max;
    }

    return QsePeakArray(minimums, maximums);
}
