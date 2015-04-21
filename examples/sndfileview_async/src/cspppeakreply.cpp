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
#include "cspppeakreply.h"
#include "qseabstractspppeakreply.h"


CSppPeakReply::CSppPeakReply(const QVector<double> &samples,
        const QseSppPeakRequest &request, QObject *parent) :
    QseAbstractSppPeakReply(request, parent)
{
    m_samples = samples;
}

void CSppPeakReply::doAlgorithm()
{
    if (!isAborted())
        setPeaks(readPeaks(request()));
}

QsePeakArray CSppPeakReply::readPeaks(const QseSppPeakRequest &req)
{
    if (req.spp() > 0)
        return readAsPeaks(req.x(), req.spp(), req.width(), req.rightAlign());
    else
        return readAsLines(req.x(), -req.spp(), req.width());
}

QsePeakArray CSppPeakReply::readAsLines(qint64 first, qint64 pps,
        int width)
{
    if (first >= m_samples.count())
        return QsePeakArray();

    qint64 last = first + width/pps + ((width%pps) ? (1) : (0));
    if (last >= m_samples.count())
        last = m_samples.count() - 1;

    if (last < 0)
        return QsePeakArray();

    QVector<double> points(last-first+1);
    for (qint64 i = first; i <= last; ++i)
        points[i-first] = m_samples[i];

    return QsePeakArray(points);
}

QsePeakArray CSppPeakReply::readAsPeaks(qint64 first, qint64 spp,
        int width, bool rightAlign)
{
    if (first >= m_samples.count())
        return QsePeakArray();

    qint64 last = first + width*spp - 1;
    if (last >= m_samples.count())
        last = m_samples.count() - 1;

    if (last < 0)
        return QsePeakArray();

    const qint64 count = (last-first+1)/spp + (((last-first+1)%spp) ? (1) : (0));
    QVector<double> minimums(count);
    QVector<double> maximums(count);
    for (qint64 arrIndex = 0; arrIndex < count; ++arrIndex)
    {
        if (isAborted())
            return QsePeakArray();

        qint64 sampleFirstIndex = first;
        qint64 sampleLastIndex = last;
        if (rightAlign)
        {
            sampleLastIndex = last - (count-arrIndex)*spp - 1;
            sampleFirstIndex = sampleLastIndex - spp + 1;
            if (sampleFirstIndex < first)
                sampleFirstIndex = first;
        }
        else
        {
            sampleFirstIndex = first + arrIndex*spp;
            sampleLastIndex = sampleFirstIndex + spp - 1;
            if (sampleLastIndex >= m_samples.count())
                sampleLastIndex = m_samples.count() - 1;
        }

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
