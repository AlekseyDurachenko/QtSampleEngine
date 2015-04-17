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
#include "qsesppasyncsignalplot.h"
#include <QPainter>
#include "qseabstractsppasyncpeakdatasource.h"
#include "qseabstractsppsignalplotdelegate.h"
#include "qseabstractspppeakreply.h"
#include <QDebug>


QseSppAsyncSignalPlot::QseSppAsyncSignalPlot(QObject *parent) :
    QseAbstractSppSignalPlot(parent)
{
    m_dataSource = 0;
    m_reply = 0;
}

void QseSppAsyncSignalPlot::setDataSource(
        QseAbstractSppAsyncPeakDataSource *dataSource)
{
    if (m_dataSource == dataSource)
        return;

    if (m_dataSource)
        disconnect(m_dataSource, 0, this, 0);

    m_dataSource = dataSource;
    if (m_dataSource)
    {
        connect(m_dataSource, SIGNAL(dataChanged()),
                this, SLOT(dataSource_dataChanged()));
        connect(m_dataSource, SIGNAL(dataChanged(qint64,qint64)),
                this, SLOT(dataSource_dataChanged(qint64,qint64)));
        connect(m_dataSource, SIGNAL(destroyed()),
                this, SLOT(dataSource_destroyed()));
    }

    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        QseSppGeometry g = geometry;
        if (g.x() < m_dataSource->minIndex())
            g.setX(m_dataSource->minIndex());
        QseSppPeakRequest request(g, rect);
        if (/*hasChanges(rect, geometry) ||*/ m_lastRequst != request)
        {
            if (m_reply)
            {
                disconnect(m_reply, 0, this, 0);
                m_reply->abort();
                m_reply->deleteLater();
            }

            m_reply = m_dataSource->read(request);
            connect(m_reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
                    this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
                    Qt::QueuedConnection);
            connect(m_reply, SIGNAL(aborted(QseSppPeakRequest)),
                    this, SLOT(reply_aborted(QseSppPeakRequest)),
                    Qt::QueuedConnection);

            if (m_lastRequst.spp() != request.spp())
                m_peaks.clear();
        }

        drawAvaiblePeaks(painter, rect, geometry);
    }

    QseAbstractSppSignalPlot::draw(painter, rect, geometry);
}

void QseSppAsyncSignalPlot::dataSource_dataChanged()
{
    m_peaks.clear();
    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::dataSource_dataChanged(qint64 /*first*/,
        qint64 /*last*/)
{
    dataSource_dataChanged();
}

void QseSppAsyncSignalPlot::dataSource_destroyed()
{
    m_dataSource = 0;
}

void QseSppAsyncSignalPlot::reply_aborted(const QseSppPeakRequest &/*request*/)
{
    m_reply->deleteLater();
    m_reply = 0;
}

void QseSppAsyncSignalPlot::reply_finished(const QsePeakArray &peaks,
        const QseSppPeakRequest &request)
{
    m_peaks = peaks;
    m_lastRequst = request;
    m_peaksFirstIndex = m_lastRequst.x();
    m_reply->deleteLater();
    m_reply = 0;
    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::drawAvaiblePeaks(QPainter *painter,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (m_peaks.isEmpty())
        return;

    // first index of visible part of peaks
    qint64 firstIndex = 0;
    if (m_peaksFirstIndex < geometry.x())
        firstIndex = geometry.x() - m_peaksFirstIndex;
    if (geometry.samplesPerPixel() > 0)
        firstIndex /= geometry.samplesPerPixel();
    // all peaks are invisible
    if (firstIndex >= m_peaks.count())
        return;

    // free space in pixels between left bound and first peaks
    int space = 0;
    if (m_peaksFirstIndex > geometry.x())
        space = QseSppGeometry::widthFromSamples(
                    geometry, m_peaksFirstIndex - geometry.x());

    // this value will be added to the y coordiante of the each peaks
    const double dy = calcDy(rect);

    // draw the peaks
    if (m_peaks.hasMaximums())
        plotDelegate()->drawAsPeaks(painter, rect, geometry,
                m_peaks, firstIndex, space, 0, dy);
    else
        plotDelegate()->drawAsLines(painter, rect, geometry,
                m_peaks, firstIndex, space, 0, dy);
}

QseAbstractPeakDataSource *QseSppAsyncSignalPlot::usedDataSource() const
{
    return qobject_cast<QseAbstractPeakDataSource *>(m_dataSource);
}
