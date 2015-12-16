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
#include <QTemporaryFile>
#include <QDebug>

CSppSyncPeakDataSource::CSppSyncPeakDataSource(QObject *parent)
    : QseAbstractSignalDataSource(parent)
{
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
                                        qint64 count,
                                        double sampleRate)
{
    clean();

    m_samples = samples;
    m_count = count;
    m_sampleRate = sampleRate;

    qint64 spp = 2;
    while (m_count / spp > 0) {
        qint64 count = m_count / spp + ((m_count % spp) ? (1) : (0));
        float *maximums;// = new float[count];
        float *minimums;// = new float[count];

        {
            QTemporaryFile *file = new QTemporaryFile();
            if (!file->open())
                return ;
            file->resize(count * sizeof(float));
            maximums = (float *)(file->map(0, count * sizeof(float)));
        }
        {
            QTemporaryFile *file = new QTemporaryFile();
            if (!file->open())
                return ;
            file->resize(count * sizeof(float));
            minimums = (float *)(file->map(0, count * sizeof(float)));
        }

        for (qint64 arrIndex = 0; arrIndex < count; ++arrIndex) {
            qint64 sampleFirstIndex = arrIndex * spp;
            qint64 sampleLastIndex = sampleFirstIndex + spp - 1;
            if (sampleLastIndex >= m_count)
                sampleLastIndex = m_count - 1;

            double min;
            double max;
            min = max = m_samples[sampleFirstIndex];
            for (int i = sampleFirstIndex + 1; i <= sampleLastIndex; ++i) {
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
//    if (m_samples)
//        delete []m_samples;

//    foreach (qint64 key, m_peakMinimums.keys())
//        delete []m_peakMinimums[key];

//    foreach (qint64 key, m_peakMaximums.keys())
//        delete []m_peakMaximums[key];

    m_peakMinimums.clear();
    m_peakMaximums.clear();
    m_peakCount.clear();


    m_samples = 0;
    m_count = 0;
    m_sampleRate = 0.0;
}

qint64 CSppSyncPeakDataSource::readAsPoints(double *points,
                                            qint64 index,
                                            qint64 count)
{
    if (index >= m_count) {
        return 0;
    }

    if (index + count > m_count) {
        count = m_count - index;
    }

    for (qint64 i = 0; i < count; ++i) {
        points[i] = m_samples[index + i];
    }

    return count;
}

qint64 CSppSyncPeakDataSource::readAsPeaks(double *minimums,
                                           double *maximums,
                                           qint64 index,
                                           qint64 spp,
                                           qint64 count)
{
    const qint64 sppPeakCount = m_peakCount.value(spp);
    const qint64 sppPeakIndex = index / spp;
    if (sppPeakIndex >= sppPeakCount) {
        return 0;
    }

    if (sppPeakIndex + count > sppPeakCount) {
        count = sppPeakCount - sppPeakIndex;
    }

    const float *sppPeakMinimums = m_peakMinimums.value(spp);
    const float *sppPeakMaximums = m_peakMaximums.value(spp);

    for (qint64 i = 0; i < count; ++i) {
        minimums[i] = sppPeakMinimums[sppPeakIndex + i];
        maximums[i] = sppPeakMaximums[sppPeakIndex + i];
    }

    return count;
}
