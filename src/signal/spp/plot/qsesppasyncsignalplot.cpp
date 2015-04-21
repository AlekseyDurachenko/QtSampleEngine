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
    //m_reply = 0;
    m_queryTimer = new QTimer(this);
    m_queryTimer->setInterval(200);
    m_queryTimer->setSingleShot(true);
    connect(m_queryTimer, SIGNAL(timeout()), this, SLOT(queryTimer_timeout()));
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
        if (hasChanges(rect, geometry))
        {
            calcPeaks(rect, geometry);
            queryUnavaiblePeaks(rect, geometry);
        }

        //if (m_lastRequst.spp() != geometry.samplesPerPixel())
        //    m_peaks.clear();
qDebug() << "draw" << m_peaks.count();
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
//    qDebug() << "abort";
    //m_reply->deleteLater();
    qDebug() << "reply_aborted (!!!!!!!!!)";
}

void QseSppAsyncSignalPlot::reply_finished(const QsePeakArray &peaks,
        const QseSppPeakRequest &request)
{
    QseAbstractSppPeakReply *reply = qobject_cast<QseAbstractSppPeakReply *>(sender());

    // TODO: it can be unusable code
    //if (!m_replies.contains(reply))
    //    return;
    bool found = false;
    foreach (const QseSppAsyncSignalPlotReplyItem &item, m_replyItems)
    {
        if (item.reply() == reply)
        {
            found = true;
            break;
        }
    }
    if (!found)
        return;

    int index = -1;
    for (int i = 0; i < m_replyItems.count(); ++i)
    {
        if (m_replyItems[i].reply() == reply)
        {
            index = i;
            break;
        }
    }


    if (m_peaks.isEmpty())
    {
        m_peaks = peaks;
        m_peaksFirstIndex = request.x();
    }
    else if (request.rightAlign())
    {
        pushFrontPeaks(m_replyItems[index].geometry(), peaks);
    }
    else
    {
        pushBackPeaks(m_replyItems[index].geometry(), m_replyItems[index].rect().width(), peaks);
    }
    setUpdateOnce(true);

    //m_replies.removeAll(reply);
    if (index != -1)
        m_replyItems.removeAt(index);

    QMetaObject::invokeMethod(reply, "deleteLater", Qt::QueuedConnection);


    qDebug() << "finished:" << peaks.count();
//    return;
////    qDebug() << "finished";
//    m_peaks = peaks;
//    m_lastRequst = request;
//    m_peaksFirstIndex = m_lastRequst.x();
//    //m_reply->deleteLater();
//    QMetaObject::invokeMethod(m_reply, "deleteLater", Qt::QueuedConnection);
//    m_reply = 0;
//    //calcPeaks(rect, geometry);
//    setUpdateOnce(true);
}

void QseSppAsyncSignalPlot::queryTimer_timeout()
{
    foreach (const QseSppAsyncSignalPlotReplyItem &item, m_replyItems)
    {
        item.reply()->disconnect(this);
        item.reply()->abort();
        QMetaObject::invokeMethod(item.reply(), "deleteLater", Qt::QueuedConnection);
    }
    m_replyItems.clear();

qDebug() << "query";
    if (m_peaks.isEmpty())
    {
        QseSppGeometry geometry = lastGeometry();
        if (geometry.x() < m_dataSource->minIndex())
            geometry.setX(m_dataSource->minIndex());

        QseSppPeakRequest request(geometry, lastRect());

        QseAbstractSppPeakReply *reply = m_dataSource->read(request);
        connect(reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
                this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
                Qt::QueuedConnection);
        connect(reply, SIGNAL(aborted(QseSppPeakRequest)),
                this, SLOT(reply_aborted(QseSppPeakRequest)),
                Qt::QueuedConnection);

        //m_replies.push_back(reply);
        m_replyItems.push_back(QseSppAsyncSignalPlotReplyItem(reply, geometry, lastRect()));
    }
    else
    {

        try
        {
            QseSppGeometry geometry = lastGeometry();

            if (geometry.x() >= m_peaksFirstIndex)
                throw "";

            if (m_peaksFirstIndex <= m_dataSource->minIndex())
                throw "";

            qint64 firstIndex = 0;
            if (geometry.x() < m_dataSource->minIndex())
                firstIndex = m_dataSource->minIndex();
            else
                firstIndex = geometry.x();

            const qint64 sampleCount = m_peaksFirstIndex - firstIndex;
            const qint64 spp = geometry.samplesPerPixel();
            const qint64 peakCount = sampleCount/spp + ((sampleCount%spp) ? (1) : (0));

            QseSppPeakRequest request(firstIndex, spp, peakCount, true);

            QseAbstractSppPeakReply *reply = m_dataSource->read(request);
            connect(reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
                    this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
                    Qt::QueuedConnection);
            connect(reply, SIGNAL(aborted(QseSppPeakRequest)),
                    this, SLOT(reply_aborted(QseSppPeakRequest)),
                    Qt::QueuedConnection);
            //m_replies.push_back(reply);
            m_replyItems.push_back(QseSppAsyncSignalPlotReplyItem(reply, geometry, lastRect()));
        }
        catch (...) {}

        try
        {
            QseSppGeometry geometry = lastGeometry();

            const qint64 &spp = geometry.samplesPerPixel();
            const qint64 lastIndex = m_peaksFirstIndex + m_peaks.count()*spp - 1;

            if (lastIndex >= m_dataSource->maxIndex())
                throw "";

            int alreadyVisibleWidth = 0;
            if (geometry.x() >= m_peaksFirstIndex)
                alreadyVisibleWidth =
                        m_peaks.count() - (geometry.x() - m_peaksFirstIndex)/spp;
            else
                alreadyVisibleWidth =
                        m_peaks.count() + (m_peaksFirstIndex - geometry.x())/spp;

            const int neededWidth = lastRect().width() - alreadyVisibleWidth;
            if (neededWidth <= 0)
                throw "";


            QseAbstractSppPeakReply *reply = m_dataSource->read(QseSppPeakRequest(lastIndex+1, spp, neededWidth));
            connect(reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
                    this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
                    Qt::QueuedConnection);
            connect(reply, SIGNAL(aborted(QseSppPeakRequest)),
                    this, SLOT(reply_aborted(QseSppPeakRequest)),
                    Qt::QueuedConnection);
            //m_replies.push_back(reply);
            m_replyItems.push_back(QseSppAsyncSignalPlotReplyItem(reply, geometry, lastRect()));
        }
        catch (...) {}

    }


    m_lastQueryTimerGeometry = lastGeometry();
    m_lastQueryTimerRect = lastRect();

//    return;
//    {
//    QseSppGeometry geometry = lastGeometry();
//    QRect rect = lastRect();

//    QseSppGeometry g = geometry;
//    if (g.x() < m_dataSource->minIndex())
//        g.setX(m_dataSource->minIndex());

//    QseSppPeakRequest request(g, rect);
//    if (/*hasChanges(rect, geometry) ||*/ m_lastRequst != request)
//    {
//        if (m_reply)
//        {
//            disconnect(m_reply, 0, this, 0);
//            m_reply->abort();
//            QMetaObject::invokeMethod(m_reply, "deleteLater", Qt::QueuedConnection);
//            //m_reply->deleteLater();
//        }

//        m_reply = m_dataSource->read(request);
//        connect(m_reply, SIGNAL(finished(QsePeakArray,QseSppPeakRequest)),
//                this, SLOT(reply_finished(QsePeakArray,QseSppPeakRequest)),
//                Qt::QueuedConnection);
//        connect(m_reply, SIGNAL(aborted(QseSppPeakRequest)),
//                this, SLOT(reply_aborted(QseSppPeakRequest)),
//                Qt::QueuedConnection);
//    }

//    m_lastQueryTimerGeometry = lastGeometry();
//    m_lastQueryTimerRect = lastRect();
//    }

    qDebug() << "done";
}

void QseSppAsyncSignalPlot::queryUnavaiblePeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_lastQueryTimerGeometry.samplesPerPixel() != geometry.samplesPerPixel()
            || m_lastQueryTimerGeometry.x() != geometry.x()
            || m_lastQueryTimerRect.width() != rect.width())
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
    qDebug() << "f:" << firstIndex;
    if (geometry.samplesPerPixel() > 0)
        firstIndex = firstIndex/geometry.samplesPerPixel();
    qDebug() << "f:" << firstIndex;
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
qDebug() << "params: " << firstIndex << space << geometry << m_peaksFirstIndex << m_peaksFirstIndex - geometry.x();
    // draw the peaks
    if (m_peaks.hasMaximums())
        plotDelegate()->drawAsPeaks(painter, rect, geometry,
                m_peaks, firstIndex, space, 0, dy);
    else
        plotDelegate()->drawAsLines(painter, rect, geometry,
                                    m_peaks, firstIndex, space, 0, dy);
}

void QseSppAsyncSignalPlot::calcPeaks(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_dataSource->options() & QseAbstractPeakDataSource::DontUseCacheOptimization
            || !checkOptimizationPossibility(lastGeometry(), geometry))
    {
        m_peaks.clear();
    }
    else
    {
//        m_peaks.clear();
        compressPeaks(lastGeometry(), geometry, &m_peaks);
//        pushFrontPeaks(geometry);
//        pushBackPeaks(geometry, rect.width());
    }
}

bool QseSppAsyncSignalPlot::checkOptimizationPossibility(
        const QseSppGeometry &oldGeometry, const QseSppGeometry &newGeometry)
{
    // does not make sense to optimize what quickly read (4 is empiric)
    if (newGeometry.samplesPerPixel() < 4)
        return false;
    // can't optimize if sign of samplePerPixel is different
    if (oldGeometry.samplesPerPixel() < 0)
        return false;

    // zoom in: can't optimize
    if (oldGeometry.samplesPerPixel() > newGeometry.samplesPerPixel())
        return false;

    // zoom out: we can't recalculate the peaks if (newValue % oldValue != 0)
    if (oldGeometry.samplesPerPixel() < newGeometry.samplesPerPixel())
        if (newGeometry.samplesPerPixel() % oldGeometry.samplesPerPixel() != 0)
            return false;

    // scroll x: we can't recalculate the peaks if (value % spp != 0)
    if (newGeometry.x() % newGeometry.samplesPerPixel() != 0)
        return false;

    return true;
}

void QseSppAsyncSignalPlot::compressPeaks(const QseSppGeometry &oldGeometry,
        const QseSppGeometry &newGeometry, QsePeakArray *peaks)
{
    if (oldGeometry.samplesPerPixel() == newGeometry.samplesPerPixel())
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

void QseSppAsyncSignalPlot::pushFrontPeaks(const QseSppGeometry &geometry, const QsePeakArray &peaks)
{
    if (geometry.x() >= m_peaksFirstIndex)
        return;

    if (m_peaksFirstIndex <= m_dataSource->minIndex())
        return;

    qint64 firstIndex = 0;
    if (geometry.x() < m_dataSource->minIndex())
        firstIndex = m_dataSource->minIndex();
    else
        firstIndex = geometry.x();

    const qint64 &spp = geometry.samplesPerPixel();
    const qint64 sampleCount = m_peaksFirstIndex - firstIndex;
    const qint64 peakCount = sampleCount/spp + ((sampleCount%spp) ? (1) : (0));
//qDebug() << "push_front" << firstIndex << m_peaksFirstIndex << sampleCount << peakCount << spp;
//qDebug() << peaks.count();

//    m_peaks.push_front(m_dataSource->read(QseSppPeakRequest(firstIndex, spp, peakCount, true)));
    m_peaks.push_front(peaks);
    m_peaksFirstIndex = firstIndex;
}

void QseSppAsyncSignalPlot::pushBackPeaks(const QseSppGeometry &geometry,
        int width, const QsePeakArray &peaks)
{
    const qint64 &spp = geometry.samplesPerPixel();
    const qint64 lastIndex = m_peaksFirstIndex + m_peaks.count()*spp - 1;

    if (lastIndex >= m_dataSource->maxIndex())
        return;

    int alreadyVisibleWidth = 0;
    if (geometry.x() >= m_peaksFirstIndex)
        alreadyVisibleWidth =
                m_peaks.count() - (geometry.x() - m_peaksFirstIndex)/spp;
    else
        alreadyVisibleWidth =
                m_peaks.count() + (m_peaksFirstIndex - geometry.x())/spp;

    const int neededWidth = width - alreadyVisibleWidth;
    if (neededWidth <= 0)
        return;

    //m_peaks.push_back(m_dataSource->read(QseSppPeakRequest(lastIndex+1, spp, neededWidth)));
    m_peaks.push_back(peaks);
}

QseAbstractPeakDataSource *QseSppAsyncSignalPlot::usedDataSource() const
{
    return qobject_cast<QseAbstractPeakDataSource *>(m_dataSource);
}
