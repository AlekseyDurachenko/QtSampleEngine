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
#include "qsesinglesignalabstractplot.h"
#include <QPainter>


QseSingleSignalAbstractPlot::QseSingleSignalAbstractPlot(QObject *parent) :
    QseAbstractPlot(parent)
{
    qRegisterMetaType<QList<float> >("QList<float>");
    m_pen.setColor(Qt::darkBlue);
    m_opacity = 0.9;
    m_peakReader = 0;
    m_readNeeded = true;
}

void QseSingleSignalAbstractPlot::setPen(const QPen &pen)
{
    if (m_pen != pen)
    {
        m_pen = pen;
        setUpdateOnce(true);
    }
}

void QseSingleSignalAbstractPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSingleSignalAbstractPlot::setPeakReader(QseSingleSignalAbstractPeakReader *peakReader)
{
    if (m_peakReader != peakReader)
    {
        if (m_peakReader)
        {
            disconnect(m_peakReader, 0, this, 0);
        }
        if (peakReader)
        {
            connect(peakReader, SIGNAL(peakReaded(int,QseGeometry,QList<float>,QList<float>)),
                    this, SLOT(slot_peakReaded(int,QseGeometry,QList<float>,QList<float>)));
        }
        m_peakReader = peakReader;
        setUpdateOnce(true);
    }
}

void QseSingleSignalAbstractPlot::reset()
{
    m_readNeeded = true;
    setUpdateOnce(true);
}

bool QseSingleSignalAbstractPlot::hasChanges(const QRect &rect, const QseGeometry &geometry)
{
    return (m_lastGeometry != geometry || rect != m_lastRect || isUpdateOnce());
}

void QseSingleSignalAbstractPlot::draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry)
{
    if (m_peakReader && (m_lastGeometry != geometry || rect != m_lastRect || m_readNeeded))
    {
        m_id = m_peakReader->start(geometry, rect.width());
        m_readNeeded = false;
    }

    if (m_id == m_lastId && !m_readNeeded)
    {
        painter->setPen(m_pen);
        painter->setOpacity(m_opacity);
        if (geometry.samplePerPixel() < 0)
        {
            drawAsLine(painter, m_minimums, rect, geometry);
        }
        else
        {
            drawAsPeak(painter, m_minimums, m_maximums, rect, geometry);
        }
    }
    else if (m_lastId != -1 && m_cacheGeometry.samplePerPixel() == geometry.samplePerPixel() && !m_readNeeded)
    {
        painter->setPen(m_pen);
        painter->setOpacity(m_opacity);
        QseGeometry gm = geometry;
        gm.setX(m_cacheGeometry.x());
        gm.setSamplePerPixel(m_cacheGeometry.samplePerPixel());
        if (gm.samplePerPixel() < 0)
        {
            drawAsLine(painter, m_minimums, rect, gm, geometry.x() - gm.x());
        }
        else
        {
            drawAsPeak(painter, m_minimums, m_maximums, rect, gm, geometry.x() - gm.x());
        }
    }

    // store last values for next iteration comparing
    m_lastGeometry = geometry;
    m_lastRect = rect;
    m_lastId = m_id;

    QseAbstractPlot::draw(painter, rect, geometry);
}

void QseSingleSignalAbstractPlot::slot_peakReaded(int id, const QseGeometry &geometry, QList<float> minimums, QList<float> maximums)
{
    m_id = id;
    m_minimums = minimums;
    m_maximums = maximums;
    m_cacheGeometry = geometry;
    setUpdateOnce(true);
}
