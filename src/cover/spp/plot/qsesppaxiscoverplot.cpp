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
#include "qsesppaxiscoverplot.h"
#include "qseabstractsppmetricprovider.h"
#include <QPainter>


QseSppAxisCoverPlot::QseSppAxisCoverPlot(QObject *parent) :
    QseAbstractSppPlot(parent)
{
    m_horizontalProvider = 0;
    m_verticalProvider = 0;

    m_clPen.setColor(Qt::blue);
    m_lPen.setColor(Qt::gray);
    m_lPen.setStyle(Qt::DashLine);
    m_clOpacity = 0.9;
    m_lOpacity = 0.5;
    m_backgroundColor = qRgb(230, 230, 230);
}

void QseSppAxisCoverPlot::setCenterLinePen(const QPen &pen)
{
    if (m_clPen != pen)
    {
        m_clPen = pen;
        setUpdateOnce(true);
    }
}

void QseSppAxisCoverPlot::setCenterLineOpacity(qreal opacity)
{
    if (m_clOpacity != opacity)
    {
        m_clOpacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSppAxisCoverPlot::setLinePen(const QPen &pen)
{
    if (m_lPen != pen)
    {
        m_lPen = pen;
        setUpdateOnce(true);
    }
}

void QseSppAxisCoverPlot::setLineOpacity(qreal opacity)
{
    if (m_lOpacity != opacity)
    {
        m_lOpacity = opacity;
        setUpdateOnce(true);
    }
}


void QseSppAxisCoverPlot::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color)
    {
        m_backgroundColor = color;
        setUpdateOnce(true);
    }
}

void QseSppAxisCoverPlot::setVerticalMetricProvider(
        QseAbstractSppMetricProvider *provider)
{
    if (m_verticalProvider == provider)
        return;

    if (m_verticalProvider)
        disconnect(m_verticalProvider, 0, this, 0);

    m_verticalProvider = provider;
    if (m_verticalProvider)
    {
        connect(m_verticalProvider, SIGNAL(changed()),
                this, SLOT(setUpdateOnce()));
        connect(m_verticalProvider, SIGNAL(destroyed()),
                this, SLOT(verticalProvider_destroyed()));
    }

    setUpdateOnce(true);
}

void QseSppAxisCoverPlot::setHorizontalMetricProvider(
        QseAbstractSppMetricProvider *provider)
{
    if (m_horizontalProvider == provider)
        return;

    if (m_horizontalProvider)
        disconnect(m_horizontalProvider, 0, this, 0);

    m_horizontalProvider = provider;
    if (m_horizontalProvider)
    {
        connect(m_horizontalProvider, SIGNAL(changed()),
                this, SLOT(setUpdateOnce()));
        connect(m_horizontalProvider, SIGNAL(destroyed()),
                this, SLOT(horizontalProvider_destroyed()));
    }

    setUpdateOnce(true);
}

bool QseSppAxisCoverPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    return (isUpdateOnce() || rect != m_lastRect || geometry != m_lastGeometry);
}

void QseSppAxisCoverPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        painter->fillRect(rect, m_backgroundColor);

        // fetch metric list
        QList<QseMetricItem> vMetricList;
        if (m_verticalProvider)
            vMetricList = m_verticalProvider->create(geometry, rect.height());
        QList<QseMetricItem> hMetricList;
        if (m_horizontalProvider)
            hMetricList = m_horizontalProvider->create(geometry, rect.width());

        // draw center lines (with level 0)
        painter->setPen(m_clPen);
        painter->setOpacity(m_clOpacity);
        foreach (const QseMetricItem &metric, vMetricList)
            if (metric.level() == 0)
                painter->drawLine(0, metric.offset(), rect.width(), metric.offset());
        foreach (const QseMetricItem &metric, hMetricList)
            if (metric.level() == 0)
                painter->drawLine(metric.offset(), 0, metric.offset(), rect.height());
        // draw main lines (with level 1)
        painter->setPen(m_lPen);
        painter->setOpacity(m_lOpacity);
        foreach (const QseMetricItem &metric, vMetricList)
            if (metric.level() == 1)
                painter->drawLine(0, metric.offset(), rect.width(), metric.offset());
        foreach (const QseMetricItem &metric, hMetricList)
            if (metric.level() == 1)
                painter->drawLine(metric.offset(), 0, metric.offset(), rect.height());
    }

    QseAbstractSppPlot::draw(painter, rect, geometry);
}

void QseSppAxisCoverPlot::verticalProvider_destroyed()
{
    m_verticalProvider = 0;
}

void QseSppAxisCoverPlot::horizontalProvider_destroyed()
{
    m_horizontalProvider = 0;
}
