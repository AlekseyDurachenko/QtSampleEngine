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
#ifndef QSESIGNALLINEARPLOTDELEGATE_H
#define QSESIGNALLINEARPLOTDELEGATE_H


#include "qseabstractsignalplotdelegate.h"


class QseSignalLinearPlotDelegate : public QseAbstractSignalPlotDelegate
{
    Q_OBJECT
public:
    explicit QseSignalLinearPlotDelegate(QObject *parent = 0);

    virtual void drawAsPoints(QPainter *painter,
                              const QRect &rect,
                              const QseGeometry &geometry,
                              const double *points,
                              qint64 count,
                              qint64 space,
                              double dy);

    virtual void drawAsPeaks(QPainter *painter,
                             const QRect &rect,
                             const QseGeometry &geometry,
                             const double *minimums,
                             const double *maximums,
                             qint64 count,
                             qint64 space,
                             double dy);
};


#endif // QSESIGNALLINEARPLOTDELEGATE_H
