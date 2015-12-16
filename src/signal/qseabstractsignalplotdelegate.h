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
#ifndef QSEABSTRACTSIGNALPLOTDELEGATE_H
#define QSEABSTRACTSIGNALPLOTDELEGATE_H


#include "qsegeometry.h"
#include <QObject>
#include <QPen>


class QseAbstractSignalPlotDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit QseAbstractSignalPlotDelegate(QObject *parent = 0);

    inline const QPen &pen() const;
    void setPen(const QPen &pen);

    inline qreal opacity() const;
    void setOpacity(qreal opacity);

    virtual void drawAsPoints(QPainter *painter,
                              const QRect &rect,
                              const QseGeometry &geometry,
                              const double *values,
                              qint64 count,
                              qint64 space,
                              double dy) = 0;

    virtual void drawAsPeaks(QPainter *painter,
                             const QRect &rect,
                             const QseGeometry &geometry,
                             const double *minimums,
                             const double *maximums,
                             qint64 count,
                             qint64 space,
                             double dy) = 0;

signals:
    void changed();

private:
    qreal m_opacity;
    QPen m_pen;
};

const QPen &QseAbstractSignalPlotDelegate::pen() const
{
    return m_pen;
}

qreal QseAbstractSignalPlotDelegate::opacity() const
{
    return m_opacity;
}


#endif // QSEABSTRACTSIGNALPLOTDELEGATE_H
