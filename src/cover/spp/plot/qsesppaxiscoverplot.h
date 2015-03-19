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
#ifndef QSESPPAXISCOVERPLOT_H
#define QSESPPAXISCOVERPLOT_H

#include "qseabstractsppplot.h"
#include <QPen>
#include <QColor>
class QseAbstractSppMetricProvider;


class QseSppAxisCoverPlot : public QseAbstractSppPlot
{
    Q_OBJECT
    Q_PROPERTY(QPen centerLinePen READ centerLinePen
               WRITE setCenterLinePen)
    Q_PROPERTY(qreal centerLineOpacity READ centerLineOpacity
               WRITE setCenterLineOpacity)
    Q_PROPERTY(QPen linePen READ linePen WRITE setLinePen)
    Q_PROPERTY(qreal lineOpacity READ lineOpacity WRITE setLineOpacity)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor
               WRITE setBackgroundColor)
public:
    explicit QseSppAxisCoverPlot(QObject *parent = 0);

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

    void setVerticalMetricProvider(QseAbstractSppMetricProvider *vertical);
    void setHorizontalMetricProvider(QseAbstractSppMetricProvider *horizontal);

    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect,
                      const QseSppGeometry &geometry);
private slots:
    void verticalProvider_destroyed();
    void horizontalProvider_destroyed();
private:
    QseAbstractSppMetricProvider *m_verticalProvider;
    QseAbstractSppMetricProvider *m_horizontalProvider;

    QPen m_clPen;
    QPen m_lPen;
    qreal m_clOpacity;
    qreal m_lOpacity;
    QColor m_backgroundColor;
};


const QPen &QseSppAxisCoverPlot::centerLinePen() const
{
    return m_clPen;
}

qreal QseSppAxisCoverPlot::centerLineOpacity() const
{
    return m_clOpacity;
}

const QPen &QseSppAxisCoverPlot::linePen() const
{
    return m_lPen;
}

qreal QseSppAxisCoverPlot::lineOpacity() const
{
    return m_lOpacity;
}

const QColor &QseSppAxisCoverPlot::backgroundColor() const
{
    return m_backgroundColor;
}


#endif // QSESPPAXISCOVERPLOT_H
