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

#include "qseabstractsppsyncpeakdatasource.h"


class CSppSyncPeakDataSource : public QseAbstractSppSyncPeakDataSource
{
    Q_OBJECT
public:
    CSppSyncPeakDataSource(QObject *parent = 0);

    virtual qint64 count() const;
    virtual qint64 minIndex() const;
    virtual qint64 maxIndex() const;

    inline const QVector<double> &samples() const;
    inline double sampleRate() const;
    virtual QsePeakArray read(qint64 x, qint64 spp, int width);
public slots:
    void setSamples(const QVector<double> &samples, double sampleRate);
private:
    QsePeakArray readAsLines(qint64 first, qint64 pps, int width);
    QsePeakArray readAsPeaks(qint64 first, qint64 spp, int width);
private:
    QVector<double> m_samples;
    double m_sampleRate;
};

const QVector<double> &CSppSyncPeakDataSource::samples() const
{
    return m_samples;
}

double CSppSyncPeakDataSource::sampleRate() const
{
    return m_sampleRate;
}


#endif // CSPPSYNCDATAPEAKSOURCE_H
