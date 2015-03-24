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
#ifndef CSPPSYNCDATASOURCE_H
#define CSPPSYNCDATASOURCE_H

#include "qseabstractsppsyncdatasource.h"


class CSppSyncDataSource : public QseAbstractSppSyncDataSource
{
    Q_OBJECT
public:
    CSppSyncDataSource(const QVector<double> &samples, QObject *parent = 0);
    virtual qint64 count() const;
    virtual double maximum() const;
    virtual double minimum() const;
    inline const QVector<double> &samples() const;
    virtual QsePeakArray read(const QseSppGeometry &geometry, int width);
public slots:
    void setSamples(const QVector<double> &samples);
private:
    QsePeakArray readAsLines(qint64 first, qint64 pps, int width);
    QsePeakArray readAsPeaks(qint64 first, qint64 spp, int width);
private:
    QVector<double> m_samples;
};

const QVector<double> &CSppSyncDataSource::samples() const
{
    return m_samples;
}


#endif // CSPPSYNCDATASOURCE_H
