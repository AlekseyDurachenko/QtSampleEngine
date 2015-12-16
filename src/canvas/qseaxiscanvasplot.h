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
#ifndef QSEAXISCANVASPLOT_H
#define QSEAXISCANVASPLOT_H

#include "qseabstractplot.h"
#include <QPen>
#include <QColor>
class QseAbstractMetricProvider;


class QseAxisCanvasPlot : public QseAbstractPlot
{
    Q_OBJECT
    Q_PROPERTY(QPen centerLinePen READ centerLinePen WRITE setCenterLinePen)
    Q_PROPERTY(qreal centerLineOpacity READ centerLineOpacity WRITE setCenterLineOpacity)
    Q_PROPERTY(QPen linePen READ linePen WRITE setLinePen)
    Q_PROPERTY(qreal lineOpacity READ lineOpacity WRITE setLineOpacity)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
public:
    explicit QseAxisCanvasPlot(QObject *parent = 0);

    inline const QPen &centerLinePen() const;
    void setCenterLinePen(const QPen &pen);

    inline qreal centerLineOpacity() const;
    void setCenterLineOpacity(qreal opacity);

    inline const QPen &linePen() const;
    void setLinePen(const QPen &pen);

    inline qreal lineOpacity() const;
    void setLineOpacity(qreal opacity);

    inline const QColor &backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    void setVerticalMetricProvider(QseAbstractMetricProvider *vertical);
    void setHorizontalMetricProvider(QseAbstractMetricProvider *horizontal);

    virtual bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);

private slots:
    void verticalProvider_destroyed();
    void horizontalProvider_destroyed();

private:
    QseAbstractMetricProvider *m_verticalProvider;
    QseAbstractMetricProvider *m_horizontalProvider;

    QPen m_clPen;
    QPen m_lPen;
    qreal m_clOpacity;
    qreal m_lOpacity;
    QColor m_backgroundColor;
};


const QPen &QseAxisCanvasPlot::centerLinePen() const
{
    return m_clPen;
}

qreal QseAxisCanvasPlot::centerLineOpacity() const
{
    return m_clOpacity;
}

const QPen &QseAxisCanvasPlot::linePen() const
{
    return m_lPen;
}

qreal QseAxisCanvasPlot::lineOpacity() const
{
    return m_lOpacity;
}

const QColor &QseAxisCanvasPlot::backgroundColor() const
{
    return m_backgroundColor;
}


#endif // QSEAXISCANVASPLOT_H
