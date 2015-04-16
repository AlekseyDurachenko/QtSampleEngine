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
#ifndef CSPPASYNCDATAPEAKSOURCE_H
#define CSPPASYNCDATAPEAKSOURCE_H

#include "qseabstractsppasyncpeakdatasource.h"
#include <QVector>


class CSppAsyncPeakDataSource : public QseAbstractSppAsyncPeakDataSource
{
    Q_OBJECT
public:
    explicit CSppAsyncPeakDataSource(QObject *parent = 0);
    virtual ~CSppAsyncPeakDataSource();

    virtual qint64 count() const;
    virtual qint64 minIndex() const;
    virtual qint64 maxIndex() const;

    inline const QVector<double> &samples() const;
    inline double sampleRate() const;

    virtual QseAbstractSppPeakReply *read(const QseSppPeakRequest &request);
public slots:
    void setSamples(const QVector<double> &samples, double sampleRate);
private:
    QThread *m_thread;
    QVector<double> m_samples;
    double m_sampleRate;
};

const QVector<double> &CSppAsyncPeakDataSource::samples() const
{
    return m_samples;
}

double CSppAsyncPeakDataSource::sampleRate() const
{
    return m_sampleRate;
}


#endif // CSPPASYNCDATAPEAKSOURCE_H
