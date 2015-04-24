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
#include <QTimer>
#include "qseabstractsppasyncpeakdatasource.h"
#include "qseabstractsppsignalplotdelegate.h"
#include "qseabstractspppeakreply.h"
#include <QDebug>


QseSppAsyncSignalPlot::QseSppAsyncSignalPlot(QObject *parent) :
    QseAbstractSppSignalPlot(parent)
{
    m_dataSource = 0;
    m_dataSourceChanged = false;
    m_queryTimer = new QTimer(this);
    m_queryTimer->setInterval(200);
    m_queryTimer->setSingleShot(true);
    connect(m_queryTimer, SIGNAL(timeout()), this, SLOT(queryTimer_timeout()));
}

QseSppAsyncSignalPlot::~QseSppAsyncSignalPlot()
{
    abortAllReplies();
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

    m_dataSourceChanged = true;
    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        if (hasChanges(rect, geometry) || m_dataSourceChanged)
        {
            calcPeaks(rect, geometry);
            queryUnavaiblePeaks(rect, geometry);
        }

        drawAvaiblePeaks(painter, rect, geometry);
    }

    QseAbstractSppSignalPlot::draw(painter, rect, geometry);
}

void QseSppAsyncSignalPlot::dataSource_dataChanged()
{
    m_peaks.clear();
    m_dataSourceChanged = true;

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
    QseAbstractSppPeakReply *reply = qobject_cast<QseAbstractSppPeakReply *>(sender());

    // HACK: it can be unusable code
    if (!m_replies.contains(reply))
        return;

    int index = m_replies.indexOf(reply);
    QMetaObject::invokeMethod(reply, "deleteLater", Qt::QueuedConnection);
    m_replies.removeAt(index);
}

void QseSppAsyncSignalPlot::reply_finished(const QsePeakArray &peaks,
        const QseSppPeakRequest &request)
{
    QseAbstractSppPeakReply *reply = qobject_cast<QseAbstractSppPeakReply *>(sender());

    // HACK: it can be unusable code
    if (!m_replies.contains(reply))
        return;

    int index = m_replies.indexOf(reply);
    const QseSppSignalPlotPeakReplyItem &item = m_replies.at(index);

    switch (item.pushType())
    {
    case QseSppSignalPlotPeakReplyItem::ReplaceAll:
        m_peaks = peaks;
        m_peaksFirstIndex = request.x();
        break;
    case QseSppSignalPlotPeakReplyItem::PushFront:
        m_peaks.push_front(peaks);
        m_peaksFirstIndex = request.x();
        break;
    case QseSppSignalPlotPeakReplyItem::PushBack:
        m_peaks.push_back(peaks);
        break;
    }

    QMetaObject::invokeMethod(reply, "deleteLater", Qt::QueuedConnection);
    m_replies.removeAt(index);

    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::queryTimer_timeout()
{
    abortAllReplies();

    if (m_peaks.isEmpty()
            || lastGeometry().samplesPerPixel() < 0
            || m_dataSource->options() & QseAbstractPeakDataSource::DontUseCacheOptimization)
    {
        queryReplaceAll();
    }
    else
    {
        queryPushFront();
        queryPushBack();
    }

    m_lastQueryTimerGeometry = lastGeometry();
    m_lastQueryTimerRect = lastRect();
    m_dataSourceChanged = false;
}

void QseSppAsyncSignalPlot::queryUnavaiblePeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_lastQueryTimerGeometry.samplesPerPixel() != geometry.samplesPerPixel()
            || m_lastQueryTimerGeometry.x() != geometry.x()
            || m_lastQueryTimerRect.width() != rect.width()
            || m_dataSourceChanged)
        m_queryTimer->start();
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
        firstIndex = firstIndex/geometry.samplesPerPixel();
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

void QseSppAsyncSignalPlot::calcPeaks(const QRect &/*rect*/,
        const QseSppGeometry &geometry)
{
    if (!checkOptimizationPossibility(lastGeometry(), geometry))
    {
        m_peaks.clear();
    }
    else
    {
        compressLinesToPeaks(lastGeometry(), geometry, &m_peaks);
        compressPeaksToPeaks(lastGeometry(), geometry, &m_peaks);
    }
}

bool QseSppAsyncSignalPlot::checkOptimizationPossibility(
        const QseSppGeometry &oldGeometry, const QseSppGeometry &newGeometry)
{
    // zoom in is acceptable if sample per pixel less then zero
    if (oldGeometry.samplesPerPixel() < 0 && newGeometry.samplesPerPixel() < 0)
        return true;

    // zoom in: can't optimize
    if (oldGeometry.samplesPerPixel() > newGeometry.samplesPerPixel())
        return false;

    // when oldGeometry less then 0, we can use optimization
    // first, we can do nothing, or recalculate points to peaks
    if (oldGeometry.samplesPerPixel() > 0)
    {
        // zoom out: we can't recalculate the peaks if (newValue % oldValue != 0)
        if (oldGeometry.samplesPerPixel() < newGeometry.samplesPerPixel()
                && newGeometry.samplesPerPixel() % oldGeometry.samplesPerPixel() != 0)
            return false;

        // scroll x: we can't recalculate the peaks if (value % spp != 0)
        if (newGeometry.x() % newGeometry.samplesPerPixel() != 0)
            return false;
    }

    return true;
}

void QseSppAsyncSignalPlot::compressLinesToPeaks(
        const QseSppGeometry &oldGeometry,
        const QseSppGeometry &newGeometry,
        QsePeakArray *peaks)
{
    if (oldGeometry.samplesPerPixel() >= newGeometry.samplesPerPixel())
        return;

    if (!(oldGeometry.samplesPerPixel() < 0
          && newGeometry.samplesPerPixel() > 0))
        return;

    const qint64 spp = newGeometry.samplesPerPixel();
    const qint64 peakCount = peaks->count() / spp;
    const QVector<double> &values = peaks->minimums();
    QVector<double> newMinimums = QVector<double>(peakCount);
    QVector<double> newMaximums = QVector<double>(peakCount);

    for (qint64 index = 0; index < peakCount; ++index)
    {
        double minimum = values[index*spp];
        double maximum = values[index*spp];

        for (qint64 n = 1; n < spp; ++n)
        {
            const double value = values[index*spp+n];
            if (value < minimum)
                minimum = value;
            if (value > maximum)
                maximum = value;
        }

        newMinimums[index] = minimum;
        newMaximums[index] = maximum;
    }

    *peaks = QsePeakArray(newMinimums, newMaximums);
}

void QseSppAsyncSignalPlot::compressPeaksToPeaks(
        const QseSppGeometry &oldGeometry,
        const QseSppGeometry &newGeometry,
        QsePeakArray *peaks)
{
    if (oldGeometry.samplesPerPixel() >= newGeometry.samplesPerPixel())
        return;

    if (oldGeometry.samplesPerPixel() < 0
          || newGeometry.samplesPerPixel() < 0)
        return;

    const qint64 &oldSpp = oldGeometry.samplesPerPixel();
    const qint64 &newSpp = newGeometry.samplesPerPixel();
    const qint64 newCount = (peaks->count() * oldSpp) / newSpp;
    const qint64 compressLevel = newSpp / oldSpp;
    const QVector<double> &oldMinimums = peaks->minimums();
    const QVector<double> &oldMaximums = peaks->maximums();
    QVector<double> newMinimums = QVector<double>(newCount);
    QVector<double> newMaximums = QVector<double>(newCount);

    for (qint64 newIndex = 0; newIndex < newCount; ++newIndex)
    {
        double minimum = oldMinimums[newIndex*compressLevel];
        double maximum = oldMaximums[newIndex*compressLevel];

        for (qint64 c = 0; c < compressLevel; ++c)
        {
            const double curmin = oldMinimums[newIndex*compressLevel+c];
            const double curmax = oldMaximums[newIndex*compressLevel+c];
            if (curmin < minimum)
                minimum = curmin;
            if (curmax > maximum)
                maximum = curmax;
        }

        newMinimums[newIndex] = minimum;
        newMaximums[newIndex] = maximum;
    }

    *peaks = QsePeakArray(newMinimums, newMaximums);
}

void QseSppAsyncSignalPlot::abortAllReplies()
{
    for (int i = 0; i < m_replies.count(); ++i)
    {
        QseAbstractPeakReply *reply = m_replies.at(i).reply();
        reply->disconnect(this);
        reply->abort();
        QMetaObject::invokeMethod(reply, "deleteLater", Qt::QueuedConnection);
    }
    m_replies.clear();
}

QseAbstractSppPeakReply *QseSppAsyncSignalPlot::createReply(
        const QseSppPeakRequest &request) const
{
    QseAbstractSppPeakReply *reply = m_dataSource->read(request);
    connect(reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
            this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
            Qt::QueuedConnection);
    connect(reply, SIGNAL(aborted(QseSppPeakRequest)),
            this, SLOT(reply_aborted(QseSppPeakRequest)),
            Qt::QueuedConnection);
    return reply;
}

void QseSppAsyncSignalPlot::queryReplaceAll()
{
    QseSppGeometry geometry = lastGeometry();
    if (geometry.x() < m_dataSource->minIndex())
        geometry.setX(m_dataSource->minIndex());

    const QseSppPeakRequest request(geometry, lastRect());
    QseAbstractSppPeakReply *reply = createReply(request);
    m_replies.insert(QseSppSignalPlotPeakReplyItem(
                         QseSppSignalPlotPeakReplyItem::ReplaceAll, reply,
                         geometry, lastRect()));
}

void QseSppAsyncSignalPlot::queryPushFront()
{
    if (lastGeometry().x() >= m_peaksFirstIndex)
        return;

    QseSppGeometry geometry = lastGeometry();
    if (geometry.x() < m_dataSource->minIndex())
        geometry.setX(m_dataSource->minIndex());

    const qint64 sampleCount = m_peaksFirstIndex - geometry.x();
    const qint64 width = QseSppGeometry::widthFromSamples(geometry, sampleCount);

    const QseSppPeakRequest request(geometry, width, true);
    QseAbstractSppPeakReply *reply = createReply(request);
    m_replies.insert(QseSppSignalPlotPeakReplyItem(
                         QseSppSignalPlotPeakReplyItem::PushFront, reply,
                         geometry, lastRect()));
}

void QseSppAsyncSignalPlot::queryPushBack()
{
    const qint64 spp = lastGeometry().samplesPerPixel();
    const qint64 lastAvaibleIndex = m_peaksFirstIndex + m_peaks.count()*spp - 1;
    if (lastAvaibleIndex >= m_dataSource->maxIndex())
        return;

    int alreadyVisibleWidth = 0;
    if (lastGeometry().x() >= m_peaksFirstIndex)
        alreadyVisibleWidth =
                m_peaks.count() - (lastGeometry().x() - m_peaksFirstIndex)/spp;
    else
        alreadyVisibleWidth =
                m_peaks.count() + (m_peaksFirstIndex - lastGeometry().x())/spp;

    const int neededWidth = lastRect().width() - alreadyVisibleWidth;
    if (neededWidth <= 0)
        return;

    QseSppPeakRequest request(lastAvaibleIndex+1, spp, neededWidth);
    QseAbstractSppPeakReply *reply = createReply(request);
    m_replies.insert(QseSppSignalPlotPeakReplyItem(
                         QseSppSignalPlotPeakReplyItem::PushBack, reply,
                         lastGeometry(), lastRect()));
}

QseAbstractPeakDataSource *QseSppAsyncSignalPlot::usedDataSource() const
{
    return qobject_cast<QseAbstractPeakDataSource *>(m_dataSource);
}
