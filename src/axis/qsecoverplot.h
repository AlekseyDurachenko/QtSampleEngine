// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSECOVERPLOT_H
#define QSECOVERPLOT_H

#include <QPen>
#include <QColor>
#include "qseabstractplot.h"
#include "qseabstractmetricprovider.h"


class QseCoverPlot : public QseAbstractPlot
{
    Q_OBJECT
public:
    explicit QseCoverPlot(QObject *parent = 0);

    inline const QPen &centerLinePen() const;
    inline qreal centerLineOpacity() const;
    inline const QPen &linePen() const;
    inline qreal lineOpacity() const;
    inline const QColor &backgroundColor() const;

    void setCenterLinePen(const QPen &pen);
    void setCenterLineOpacity(qreal opacity);
    void setLinePen(const QPen &pen);
    void setLineOpacity(qreal opacity);
    void setBackgroundColor(const QColor &color);

    void setVerticalMetricProvider(QseAbstractMetricProvider *vMetricProvider);
    void setHorizontalMetricProvider(QseAbstractMetricProvider *hMetricProvider);

    void reset();
    bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    void draw(QPainter *painter, const QRect &rect, const QseSppGeometry &geometry);
private slots:
    void verticalMetricProviderDestroyed();
    void horizontalMetricProviderDestroyed();
private:
    QseAbstractMetricProvider *m_verticalProvider;
    QseAbstractMetricProvider *m_horizontalProvider;

    QPen m_clPen, m_lPen;
    qreal m_clOpacity, m_lOpacity;
    QColor m_backgroundColor;

    QRect m_lastRect;
    QseSppGeometry m_lastGeometry;
};


const QPen &QseCoverPlot::centerLinePen() const
{
    return m_clPen;
}

qreal QseCoverPlot::centerLineOpacity() const
{
    return m_clOpacity;
}

const QPen &QseCoverPlot::linePen() const
{
    return m_lPen;
}

qreal QseCoverPlot::lineOpacity() const
{
    return m_lOpacity;
}

const QColor &QseCoverPlot::backgroundColor() const
{
    return m_backgroundColor;
}


#endif // QSECOVERPLOT_H
