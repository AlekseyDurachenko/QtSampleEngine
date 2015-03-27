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
#ifndef QSESPPSYNCSIGNALPLOT_H
#define QSESPPSYNCSIGNALPLOT_H

#include "qseabstractsppsignalplot.h"
#include "qsepeakarray.h"
class QseAbstractSppSyncPeakDataSource;
class QseAbstractSppSignalPlotDelegate;

class QseSppSyncSignalPlot : public QseAbstractSppSignalPlot
{
    Q_OBJECT
public:
    explicit QseSppSyncSignalPlot(QObject *parent = 0);

    inline QseAbstractSppSyncPeakDataSource *dataSource() const;
    void setDataSource(QseAbstractSppSyncPeakDataSource *dataSource);

    inline QseAbstractSppSignalPlotDelegate *plotDelegate() const;
    void setPlotDelegate(QseAbstractSppSignalPlotDelegate *plotDelegate);

    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseSppGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect,
              const QseSppGeometry &geometry);
private slots:
    void dataSource_destroyed(QObject *obj);
    void dataSource_dataChanged();
    void dataSource_dataChanged(qint64 first, qint64 last);
    void plotDelegate_destroyed();
    void plotDelegate_changed();
protected:
    bool hasDataChanges() const;
    qint64 firstChangedSample() const;
    qint64 lastChangedSample() const;
    void resetDataChanges();
private:
    QseAbstractSppSyncPeakDataSource *m_dataSource;
    QseAbstractSppSignalPlotDelegate *m_plotDelegate;
    qint64 m_hasDataChanges;
    qint64 m_firstChangedSample;
    qint64 m_lastChangedSample;
private:
    QsePeakArray readPeaks(const QRect &rect, const QseSppGeometry &geometry);
    bool isPeaksMayChanged(const QRect &rect, const QseSppGeometry &geometry);
private:
    QsePeakArray m_lastPeaks;
};

QseAbstractSppSyncPeakDataSource *QseSppSyncSignalPlot::dataSource() const
{
    return m_dataSource;
}

QseAbstractSppSignalPlotDelegate *QseSppSyncSignalPlot::plotDelegate() const
{
    return m_plotDelegate;
}


#endif // QSESPPSYNCSIGNALPLOT_H
