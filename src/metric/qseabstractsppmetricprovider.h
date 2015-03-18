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
#ifndef QSEABSTRACTSPPMETRICPROVIDER_H
#define QSEABSTRACTSPPMETRICPROVIDER_H

#include <QList>
#include "qseabstractmetricprovider.h"
#include "qsemetricitem.h"
#include "qsesppgeometry.h"


class QseAbstractSppMetricProvider : public QseAbstractMetricProvider
{
    Q_OBJECT
public:
    QseAbstractSppMetricProvider(QObject *parent = 0);

    virtual QList<QseMetricItem> create(const QseSppGeometry &geometry,
                                        int size) const = 0;
};


#endif // QSEABSTRACTSPPMETRICPROVIDER_H
