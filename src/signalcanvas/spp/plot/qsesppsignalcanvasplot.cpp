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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#include "qsesppsignalcanvasplot.h"
#include <QPainter>
#include "qseabstractpeakdatasource.h"


QseSppSignalCanvasPlot::QseSppSignalCanvasPlot(QObject *parent)
    : QseAbstractSppPlot(parent)
{
    m_brush = Qt::black;
    m_opacity = 0.1;
    m_dataSource = 0;
}

void QseSppSignalCanvasPlot::setBrush(const QBrush &brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        setUpdateOnce(true);
    }
}

void QseSppSignalCanvasPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity) {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSppSignalCanvasPlot::setDataSource(
    QseAbstractPeakDataSource *dataSource)
{
    if (!isEnabled())
        return;

    if (m_dataSource == dataSource)
        return;

    if (m_dataSource)
        disconnect(m_dataSource, 0, this, 0);

    m_dataSource = dataSource;
    if (m_dataSource) {
        connect(m_dataSource, SIGNAL(destroyed(QObject *)),
                this, SLOT(dataSource_destroyed(QObject *)));
        connect(m_dataSource, SIGNAL(dataChanged()),
                this, SLOT(dataSource_dataChanged()));
    }

    setUpdateOnce(true);
}

bool QseSppSignalCanvasPlot::hasChanges(const QRect &rect,
                                        const QseSppGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

bool QseSppSignalCanvasPlot::isVisible(const QRect &rect,
                                       const QseSppGeometry &geometry)
{
    if (m_dataSource == 0)
        return false;

    if (m_dataSource->count() == 0)
        return false;

    const qint64 firstVisibleSample = geometry.x();
    const qint64 lastVisibleSample = firstVisibleSample + QseSppGeometry::samplesFromWidth(geometry, rect.width());

    if (m_dataSource->minIndex() >= lastVisibleSample)
        return false;

    if (m_dataSource->maxIndex() <= firstVisibleSample)
        return false;

    return true;
}

void QseSppSignalCanvasPlot::draw(QPainter *painter,
                                  const QRect &rect,
                                  const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry)) {
        const qint64 firstVisibleSample = geometry.x();
        const qint64 lastVisibleSample =
            QseSppGeometry::calcSampleIndex(geometry, rect.width());

        int sl = 0;
        if (m_dataSource->minIndex() > firstVisibleSample)
            sl = QseSppGeometry::calcOffset(geometry, m_dataSource->minIndex());

        int sr = rect.width() - 1;
        if (m_dataSource->maxIndex() <= lastVisibleSample)
            sr = QseSppGeometry::calcOffset(geometry, m_dataSource->maxIndex());

        painter->save();
        painter->setOpacity(m_opacity);
        painter->fillRect(sl, 0, sr - sl + 1, rect.height(), m_brush);
        painter->restore();
    }

    QseAbstractSppPlot::draw(painter, rect, geometry);
}

void QseSppSignalCanvasPlot::dataSource_dataChanged()
{
    setUpdateOnce(true);
}

void QseSppSignalCanvasPlot::dataSource_destroyed(QObject *obj)
{
    if (obj == m_dataSource)
        m_dataSource = 0;

    setUpdateOnce(true);
}
