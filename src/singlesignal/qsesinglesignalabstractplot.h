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
#ifndef QSESINGLESIGNALABSTRACTPLOT_H
#define QSESINGLESIGNALABSTRACTPLOT_H

#include "qseabstractplot.h"
#include "qsesinglesignalabstractpeakreader.h"

class QseSingleSignalAbstractPlot : public QseAbstractPlot
{
    Q_OBJECT
public:
    explicit QseSingleSignalAbstractPlot(QObject *parent = 0);

    inline QPen pen() const;
    inline qreal opacity() const;
    void setPen(const QPen &pen);
    void setOpacity(qreal opacity);

    inline QseSingleSignalAbstractPeakReader *peakReader();
    void setPeakReader(QseSingleSignalAbstractPeakReader *peakReader);

    bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);

public slots:
    void reset();

private slots:
    void slot_peakReaded(int id, const QseGeometry &geometry, QList<float> minimums, QList<float> maximums);

private:
    virtual void drawAsLine(QPainter *painter, const QList<float> &points, const QRect &rect,
            const QseGeometry &geometry, int offset = 0) = 0;
    virtual void drawAsPeak(QPainter *painter, const QList<float> &minimums, const QList<float> &maximums,
            const QRect &rect, const QseGeometry &geometry, int offset = 0) = 0;

private:
    QseSingleSignalAbstractPeakReader *m_peakReader;
    QList<float> m_minimums, m_maximums;
    QPen m_pen;
    qreal m_opacity;
    QseGeometry m_lastGeometry;
    QseGeometry m_cacheGeometry;
    QRect m_lastRect;
    int m_id;
    int m_lastId;
    bool m_readNeeded;

};

QPen QseSingleSignalAbstractPlot::pen() const
{
    return m_pen;
}

qreal QseSingleSignalAbstractPlot::opacity() const
{
    return m_opacity;
}

QseSingleSignalAbstractPeakReader *QseSingleSignalAbstractPlot::peakReader()
{
    return m_peakReader;
}

#endif // QSESINGLESIGNALABSTRACTPLOT_H
