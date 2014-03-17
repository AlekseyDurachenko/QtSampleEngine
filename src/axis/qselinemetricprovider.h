// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef QSELINEMETRICPROVIDER_H
#define QSELINEMETRICPROVIDER_H

#include "qseabstractmetricprovider.h"
#include "qsemetricmapper.h"


class QseLineMetricProvider : public QseAbstractMetricProvider
{
    Q_OBJECT
public:
    enum Orientation {Horizontal = 0, Vertical};
    explicit QseLineMetricProvider(Orientation orientation, QObject *parent = 0);
    virtual ~QseLineMetricProvider();
    virtual int maximumTextLenght() const;
    inline Orientation orientation() const;
    QList<QseMetricItem> create(const QseGeometry &geometry, int size) const;
public slots:
    void setCoeff(double coeff);
private:
    QseMetricMapper *m_mapper;
    Orientation m_orientation;
    double m_coeff;
};

QseLineMetricProvider::Orientation QseLineMetricProvider::orientation() const
{
    return m_orientation;
}


#endif // QSELINEMETRICPROVIDER_H
