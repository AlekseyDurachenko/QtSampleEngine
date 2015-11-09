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
#ifndef CSPPSYNCDATAPEAKSOURCE_H
#define CSPPSYNCDATAPEAKSOURCE_H

#include <QHash>
#include "qseabstractsppsyncpeakdatasource.h"


class CSppSyncPeakDataSource : public QseAbstractSppSyncPeakDataSource
{
    Q_OBJECT
public:
    CSppSyncPeakDataSource(QObject *parent = 0);

    virtual qint64 count() const;
    virtual qint64 minIndex() const;
    virtual qint64 maxIndex() const;

    inline float *samples() const;
    inline double sampleRate() const;
    virtual QsePeakArray read(const QseSppPeakRequest &request);

public slots:
    void setSamples(float *samples, qint64 count, double sampleRate);

private:
    void clean();
    QsePeakArray readAsLines(qint64 first, qint64 pps, int width);
    QsePeakArray readAsPeaks(qint64 first, qint64 spp, int width, bool rightAligh = false);

private:
    QHash<qint64, float*> m_peakMinimums;
    QHash<qint64, float*> m_peakMaximums;
    QHash<qint64, qint64> m_peakCount;
    float *m_samples;
    qint64 m_count;
    double m_sampleRate;
};

float *CSppSyncPeakDataSource::samples() const
{
    return m_samples;
}

double CSppSyncPeakDataSource::sampleRate() const
{
    return m_sampleRate;
}


#endif // CSPPSYNCDATAPEAKSOURCE_H
