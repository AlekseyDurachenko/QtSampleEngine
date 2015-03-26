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
#ifndef QSESPPSYNCSIGNALLINEARPLOT_H
#define QSESPPSYNCSIGNALLINEARPLOT_H

#include "qseabstractsppsyncsignalplot.h"
#include "qsepeakarray.h"


class QseSppSyncSignalLinearPlot : public QseAbstractSppSyncSignalPlot
{
    Q_OBJECT
public:
    explicit QseSppSyncSignalLinearPlot(QObject *parent = 0);

    virtual void draw(QPainter *painter, const QRect &rect,
              const QseSppGeometry &geometry);
protected:
    void drawAsLines(QPainter *painter, const QsePeakArray &peaks,
                     const QRect &rect, const QseSppGeometry &geometry,
                     int offset = 0);
    void drawAsPeaks(QPainter *painter, const QsePeakArray &peaks,
                     const QRect &rect, const QseSppGeometry &geometry,
                     int offset = 0);
private:
    QsePeakArray readPeaks(const QRect &rect, const QseSppGeometry &geometry);
    bool isPeaksMayChanged(const QRect &rect, const QseSppGeometry &geometry);
private:
    QsePeakArray m_lastPeaks;
};

#endif // QSESPPSYNCSIGNALLINEARPLOT_H
