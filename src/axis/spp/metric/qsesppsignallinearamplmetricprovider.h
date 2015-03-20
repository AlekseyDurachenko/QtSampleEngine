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
#ifndef QSESPPSIGNALLINEARAMPLMETRICPROVIDER_H
#define QSESPPSIGNALLINEARAMPLMETRICPROVIDER_H

#include "qseabstractsppmetricprovider.h"
class QseMetricMapper;


class QseSppSignalLinearAmplMetricProvider : public QseAbstractSppMetricProvider
{
    Q_OBJECT
public:
    explicit QseSppSignalLinearAmplMetricProvider(QObject *parent = 0);
    virtual ~QseSppSignalLinearAmplMetricProvider();

    inline double factor() const;
    void setFactor(double factor);

    virtual int maximumTextLenght() const;
    virtual QList<QseMetricItem> create(const QseSppGeometry &geometry,
                                        int size) const;
private:
    QseMetricMapper *m_mapper;
    double m_factor;
};

double QseSppSignalLinearAmplMetricProvider::factor() const
{
    return m_factor;
}


#endif // QSESPPSIGNALLINEARAMPLMETRICPROVIDER_H