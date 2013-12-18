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
#ifndef QSESINGLESIGNALLINEARPLOT_H
#define QSESINGLESIGNALLINEARPLOT_H

#include "qsesinglesignalabstractplot.h"

class QseSingleSignalLinearPlot : public QseSingleSignalAbstractPlot
{
    Q_OBJECT
public:
    explicit QseSingleSignalLinearPlot(QObject *parent = 0);

protected:
    void drawAsLine(QPainter *painter, const QList<float> &points, const QRect &rect,
            const QseGeometry &geometry, int offset = 0);
    void drawAsPeak(QPainter *painter, const QList<float> &minimums, const QList<float> &maximums,
            const QRect &rect, const QseGeometry &geometry, int offset = 0);

};

#endif // QSESINGLESIGNALLINEARPLOT_H
