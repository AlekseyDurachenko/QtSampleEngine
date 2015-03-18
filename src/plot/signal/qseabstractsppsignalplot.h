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
#ifndef QSEABSTRACTSPPSIGNALPLOT_H
#define QSEABSTRACTSPPSIGNALPLOT_H

#include <QPen>
#include "qsesppgeometry.h"
#include "qseabstractsppplot.h"


class QseAbstractSppSignalPlot : public QseAbstractSppPlot
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit QseAbstractSppSignalPlot(QObject *parent = 0);

    inline const QPen &pen() const;
    void setPen(const QPen &pen);

    inline qreal opacity() const;
    void setOpacity(qreal opacity);
private:
    qreal m_opacity;
    QPen m_pen;
};

const QPen &QseAbstractSppSignalPlot::pen() const
{
    return m_pen;
}

qreal QseAbstractSppSignalPlot::opacity() const
{
    return m_opacity;
}


#endif // QSEABSTRACTSPPSIGNALPLOT_H
