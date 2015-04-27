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
    setOptions(DontUseCacheOptimization);

    m_samples = 0;
    m_count = 0;
    m_sampleRate = 0.0;
}

qint64 CSppSyncPeakDataSource::count() const
{
    return m_count;
}

qint64 CSppSyncPeakDataSource::minIndex() const
{
    return 0;
}

qint64 CSppSyncPeakDataSource::maxIndex() const
{
    return m_count;
}

void CSppSyncPeakDataSource::setSamples(float *samples,
        qint64 count, double sampleRate)
{
    clean();

    m_samples = samples;
    m_count = count;
    m_sampleRate = sampleRate;

    qint64 spp = 2;
    while (m_count / spp > 0)
    {
        qint64 count = m_count / spp + ((m_count%spp)?(1):(0));
        float *maximums = new float[count];
        float *minimums = new float[count];

        for (qint64 arrIndex = 0; arrIndex < count; ++arrIndex)
        {
            qint64 sampleFirstIndex = arrIndex*spp;
            qint64 sampleLastIndex = sampleFirstIndex + spp - 1;
            if (sampleLastIndex >= m_count)
                sampleLastIndex = m_count - 1;

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

        m_peakMaximums[spp] = maximums;
        m_peakMinimums[spp] = minimums;
        m_peakCount[spp] = count;

        spp *= 2;
    }


    emit dataChanged();
}

void CSppSyncPeakDataSource::clean()
{
    if (m_samples)
        delete []m_samples;

    foreach (qint64 key, m_peakMinimums.keys())
        delete []m_peakMinimums[key];

    foreach (qint64 key, m_peakMaximums.keys())
        delete []m_peakMaximums[key];

    m_peakMinimums.clear();
    m_peakMaximums.clear();
    m_peakCount.clear();


    m_samples = 0;
    m_count = 0;
    m_sampleRate = 0.0;
}

QsePeakArray CSppSyncPeakDataSource::read(const QseSppPeakRequest &req)
{
    if (!m_samples)
        return QsePeakArray();

    if (req.samplePerPixel() > 0)
        return readAsPeaks(req.x(), req.samplePerPixel(), req.width(),
                           req.rightAlign());
    else
        return readAsLines(req.x(), -req.samplePerPixel(), req.width());
}

QsePeakArray CSppSyncPeakDataSource::readAsLines(qint64 first, qint64 pps,
        int width)
{
    if (first >= m_count)
        return QsePeakArray();

    qint64 last = first + width/pps + ((width%pps) ? (1) : (0));
    if (last >= m_count)
        last = m_count - 1;

    if (last < 0)
        return QsePeakArray();

    QVector<double> points(last-first+1);
    for (qint64 i = first; i <= last; ++i)
        points[i-first] = m_samples[i];

    return QsePeakArray(points);
}

QsePeakArray CSppSyncPeakDataSource::readAsPeaks(qint64 first, qint64 spp,
        int width, bool /*rightAligh*/)
{
    if (!m_peakCount.contains(spp))
        return QsePeakArray();

    if (first % spp)
        return QsePeakArray();

    float *minimums = m_peakMinimums.value(spp);
    float *maximums = m_peakMaximums.value(spp);
    qint64 count = m_peakCount.value(spp);

    qint64 firstIndex = first/spp;
    qint64 lastIndex = firstIndex + width;
    if (lastIndex >= count)
        lastIndex = count - 1;

    QVector<double> arrMax(lastIndex-firstIndex+1);
    QVector<double> arrMin(lastIndex-firstIndex+1);
    for (int i = firstIndex; i <= lastIndex; ++i)
    {
        arrMin[i-firstIndex] = minimums[i];
        arrMax[i-firstIndex] = maximums[i];
    }

    return QsePeakArray(arrMin, arrMax);
}
