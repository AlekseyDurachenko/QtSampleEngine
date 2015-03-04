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
#include "qsesinglesignallinearplot.h"
#include "qsehelper.h"

QseSingleSignalLinearPlot::QseSingleSignalLinearPlot(QObject *parent) :
    QseSingleSignalAbstractPlot(parent)
{
}

void QseSingleSignalLinearPlot::drawAsLine(QPainter *painter, const QList<float> &points, const QRect &rect,
    const QseGeometry &geometry, int offset)
{
    int space = 0; // skip pixel from left bound
    int first = 0; // index of first visible points
    if (offset < 0)
        space = qAbs(geometry.samplePerPixel() * offset);
    else
        first = offset;

    for (int i = first+1; i < points.count(); ++i)
    {
        double x1 = space + (i - 1 - first) * qAbs(geometry.samplePerPixel());
        double x2 = space + (i - first) * qAbs(geometry.samplePerPixel());
        double y1 = rect.height()/2 - (geometry.y() + points[i-1]) * rect.height() / geometry.height();
        double y2 = rect.height()/2 - (geometry.y() + points[i]) * rect.height() / geometry.height();

        if (x1 >= rect.width())
            break;

        if ((y1 < 0 && y2 < 0) || (y1 >= rect.height() && y2 >= rect.height()))
            continue;

        double yy1 = y1;
        double yy2 = y2;
        double xx1 = x1;
        double xx2 = x2;

        if (y1 >= rect.height())
            Qse::calcIntersection(x1, y1, x2, y2, x1, rect.height()-1, x2, rect.height()-1, xx1, yy1);
        if (y2 >= rect.height())
            Qse::calcIntersection(x1, y1, x2, y2, x1, rect.height()-1, x2, rect.height()-1, xx2, yy2);
        if (y1 < 0)
            Qse::calcIntersection(x1, y1, x2, y2, x1, 0, x2, 0, xx1, yy1);
        if (y2 < 0)
            Qse::calcIntersection(x1, y1, x2, y2, x1, 0, x2, 0, xx2, yy2);

        painter->drawLine(QPointF(xx1, yy1), QPointF(xx2, yy2));
    }
}

void QseSingleSignalLinearPlot::drawAsPeak(QPainter *painter, const QList<float> &minimums,
    const QList<float> &maximums, const QRect &rect, const QseGeometry &geometry, int offset)
{    
    int space = 0; // skip pixel from left bound
    int first = 0; // index of first visible minimum(maximum)
    if (offset < 0)
        space = -offset;
    else
        first = offset;

    if (first >= maximums.count())
        return;

    double prevMin = rect.height()/2-(geometry.y()+minimums[first])*rect.height()/geometry.height();
    double prevMax = rect.height()/2-(geometry.y()+maximums[first])*rect.height()/geometry.height();
    double x1 = space;
    double x2 = space;
    if (x1 >= rect.width())
        return;
    if (prevMin < 0.0) prevMin = 0.0;
    if (prevMax < 0.0) prevMax = 0.0;
    if (prevMin >= rect.height()) prevMin = rect.height()-1;
    if (prevMax >= rect.height()) prevMax = rect.height()-1;
    if (prevMin == prevMax)
        painter->drawPoint(QPointF(x1, prevMin));
    else
        painter->drawLine(QPointF(x1, prevMin), QPointF(x2, prevMax));

    for (int i = first+1; i < minimums.count(); ++i)
    {
        x1 = space + i - first;
        x2 = space + i - first;
        if (x1 >= rect.width())
            break;
        double curMin = rect.height()/2-(geometry.y()+minimums[i])*rect.height()/geometry.height();
        double curMax = rect.height()/2-(geometry.y()+maximums[i])*rect.height()/geometry.height();
        if (! ((curMin < 0.0 && curMax < 0.0) || (curMin >= rect.height() && curMax >= rect.height())))
        {
            if (curMin < 0.0) curMin = 0.0;
            if (curMax < 0.0) curMax = 0.0;
            if (curMin >= rect.height()) curMin = rect.height()-1;
            if (curMax >= rect.height()) curMax = rect.height()-1;

            // fill the gap between the two lines, if exists
            if (curMin < prevMax) curMin = prevMax-1;
            if (curMax > prevMin) curMax = prevMin+1;

            //
            prevMin = curMin;
            prevMax = curMax;

            if (curMin == curMax)
                painter->drawPoint(QPointF(x1, curMin));
            else
                painter->drawLine(QPointF(x1, curMin), QPointF(x2, curMax));
        }
    }
}
