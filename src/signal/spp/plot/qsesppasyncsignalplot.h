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
#ifndef QSESPPASYNCSIGNALPLOT_H
#define QSESPPASYNCSIGNALPLOT_H

#include "qseabstractsppsignalplot.h"
#include "qsespppeakrequest.h"
#include "qsesppsignalplotpeakreplyitemlist.h"
class QseAbstractSppAsyncPeakDataSource;


class QseSppAsyncSignalPlot : public QseAbstractSppSignalPlot
{
    Q_OBJECT
public:
    explicit QseSppAsyncSignalPlot(QObject *parent = 0);
    virtual ~QseSppAsyncSignalPlot();

    inline QseAbstractSppAsyncPeakDataSource *dataSource() const;
    void setDataSource(QseAbstractSppAsyncPeakDataSource *dataSource);

    virtual void draw(QPainter *painter, const QRect &rect,
                      const QseSppGeometry &geometry);
private slots:
    void dataSource_dataChanged();
    void dataSource_dataChanged(qint64 first, qint64 last);
    void dataSource_destroyed();
    void reply_aborted(const QseSppPeakRequest &request);
    void reply_finished(const QsePeakArray &peaks,
                        const QseSppPeakRequest &request);
    void queryTimer_timeout();
private:
    void queryUnavaiblePeaks(const QRect &rect,
                             const QseSppGeometry &geometry);
    void drawAvaiblePeaks(QPainter *painter, const QRect &rect,
                          const QseSppGeometry &geometry);
    void calcPeaks(const QRect &rect, const QseSppGeometry &geometry);
    bool checkOptimizationPossibility(const QseSppGeometry &oldGeometry,
                                      const QseSppGeometry &newGeometry);
    void compressPeaks(const QseSppGeometry &oldGeometry,
                       const QseSppGeometry &newGeometry,
                       QsePeakArray *peaks);
    void abortAllReplies();
    QseAbstractSppPeakReply *createReply(const QseSppPeakRequest &request) const;
    void queryReplaceAll();
    void queryPushFront();
    void queryPushBack();
private:
    virtual QseAbstractPeakDataSource *usedDataSource() const;
private:
    QseAbstractSppAsyncPeakDataSource *m_dataSource;
    QsePeakArray m_peaks;
    qint64 m_peaksFirstIndex;
//    QseAbstractSppPeakReply *m_reply;
//    QList<QseAbstractSppPeakReply *> m_replies;
//    QList<QseSppSignalPlotPeakReplyItem> m_replyItems;
//    QseSppPeakRequest m_lastRequst;
    QseSppSignalPlotPeakReplyItemList m_replies;
    QTimer *m_queryTimer;
    QRect m_lastQueryTimerRect;
    QseSppGeometry m_lastQueryTimerGeometry;

};

QseAbstractSppAsyncPeakDataSource *QseSppAsyncSignalPlot::dataSource() const
{
    return m_dataSource;
}


#endif // QSESPPASYNCSIGNALPLOT_H
