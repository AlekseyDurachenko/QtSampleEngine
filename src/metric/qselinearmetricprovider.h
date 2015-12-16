// Copyright 2014-2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSELINEMETRICPROVIDER_H
#define QSELINEMETRICPROVIDER_H


#include "qseabstractmetricprovider.h"
class QseMetricMapper;


class QseLinearMetricProvider : public QseAbstractMetricProvider
{
    Q_OBJECT
    Q_ENUMS(Orientation)
public:
    enum Orientation {
        Horizontal  = 0x1,
        Vertical    = 0x2
    };

    explicit QseLinearMetricProvider(Orientation orientation, QObject *parent = 0);
    virtual ~QseLinearMetricProvider();

    inline double factor() const;
    void setFactor(double factor);

    inline Orientation orientation() const;
    void setOrientation(Orientation orientation);

    virtual int maximumTextLenght() const;
    virtual QList<QseMetricItem> create(const QseGeometry &geometry, int size) const;

private:
    QseMetricMapper *m_mapper;
    Orientation m_orientation;
    double m_factor;
};

double QseLinearMetricProvider::factor() const
{
    return m_factor;
}

QseLinearMetricProvider::Orientation QseLinearMetricProvider::orientation() const
{
    return m_orientation;
}


#endif // QSELINEMETRICPROVIDER_H
