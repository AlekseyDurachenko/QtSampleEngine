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
#include "qsesignallinearplotdelegate.h"
#include "qsehelper.h"
#include <QPainter>


QseSignalLinearPlotDelegate::QseSignalLinearPlotDelegate(QObject *parent)
    : QseAbstractSignalPlotDelegate(parent)
{
}

void QseSignalLinearPlotDelegate::drawAsPoints(QPainter *painter,
                                               const QRect &rect,
                                               const QseGeometry &geometry,
                                               const double *points,
                                               qint64 count,
                                               qint64 space,
                                               double dy)
{
    painter->save();
    painter->setPen(pen());
    painter->setOpacity(opacity());

    const qint64 pps = -geometry.spp();
    const double k = rect.height() / geometry.height();
    for (qint64 i = 1; i < count; ++i) {
        const double x1 = space + (i - 1) * pps;
        const double x2 = x1 + pps;
        const double y1 = dy - k * (geometry.y() + points[i - 1]);
        const double y2 = dy - k * (geometry.y() + points[i]);

        if (x1 >= rect.width())
            break;

        if ((y1 < 0 && y2 < 0) || (y1 >= rect.height() && y2 >= rect.height()))
            continue;

        double yy1 = y1;
        double yy2 = y2;
        double xx1 = x1;
        double xx2 = x2;

        if (y1 >= rect.height()) {
            Qse::calcIntersection(x1, y1,
                                  x2, y2,
                                  x1, rect.height() - 1,
                                  x2, rect.height() - 1,
                                  xx1, yy1);
        }
        if (y2 >= rect.height()) {
            Qse::calcIntersection(x1, y1,
                                  x2, y2,
                                  x1, rect.height() - 1,
                                  x2, rect.height() - 1,
                                  xx2, yy2);
        }
        if (y1 < 0) {
            Qse::calcIntersection(x1, y1,
                                  x2, y2,
                                  x1, 0,
                                  x2, 0,
                                  xx1, yy1);
        }
        if (y2 < 0) {
            Qse::calcIntersection(x1, y1,
                                  x2, y2,
                                  x1, 0,
                                  x2, 0,
                                  xx2, yy2);
        }

        painter->drawLine(QLineF(xx1, yy1, xx2, yy2));
    }

    painter->restore();
}

void QseSignalLinearPlotDelegate::drawAsPeaks(QPainter *painter,
                                              const QRect &rect,
                                              const QseGeometry &geometry,
                                              const double *minimums,
                                              const double *maximums,
                                              qint64 count,
                                              qint64 space,
                                              double dy)
{
    const double k = rect.height() / geometry.height();

    // first iteration: i == 0
    double prevMin = dy - k * (geometry.y() + minimums[0]);
    double prevMax = dy - k * (geometry.y() + maximums[0]);

    int x1 = space;
    int x2 = space;
    if (x1 >= rect.width())
        return;

    if (prevMin < 0.0) prevMin = 0.0;
    if (prevMax < 0.0) prevMax = 0.0;
    if (prevMin >= rect.height()) prevMin = rect.height() - 1;
    if (prevMax >= rect.height()) prevMax = rect.height() - 1;

    painter->save();
    painter->setPen(pen());
    painter->setOpacity(opacity());

    if (prevMin == prevMax)
        painter->drawPoint(QPointF(x1, prevMin));
    else
        painter->drawLine(QLineF(x1, prevMin, x2, prevMax));

    // other iteration: i >= 1
    for (qint64 i = 1; i < count; ++i) {
        x1 = space + i;
        x2 = space + i;
        if (x1 >= rect.width()) {
            break;
        }

        double curMin = dy - k * (geometry.y() + minimums[i]);
        double curMax = dy - k * (geometry.y() + maximums[i]);
        if (curMin < 0.0 && curMax < 0.0) {
            prevMin = prevMax = 0.0;
            continue;
        }

        if (curMin >= rect.height() && curMax >= rect.height()) {
            prevMin = prevMax = rect.height();
            continue;
        }

        if (curMin < 0.0) curMin = 0.0;
        if (curMax < 0.0) curMax = 0.0;
        if (curMin >= rect.height()) curMin = rect.height() - 1;
        if (curMax >= rect.height()) curMax = rect.height() - 1;

        // fill the gap between the two lines, if exists
        if (curMin < prevMax) curMin = prevMax - 1;
        if (curMax > prevMin) curMax = prevMin + 1;

        prevMin = curMin;
        prevMax = curMax;

        if (curMin == curMax)
            painter->drawPoint(QPointF(x1, curMin));
        else
            painter->drawLine(QLineF(x1, curMin, x2, curMax));
    }

    painter->restore();
}
