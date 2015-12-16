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
#include "qsestandardhorizontalzoomcontroller.h"
#include <QWheelEvent>
#include <QDebug>


QseStandardHorizontalZoomController::QseStandardHorizontalZoomController(QObject *parent)
    : QseAbstractStandardController(parent)
{
}


void QseStandardHorizontalZoomController::wheelEvent(QWheelEvent *event,
                                                     const QRect &/*rect*/,
                                                     const QseGeometry &geometry)
{
    if (event->modifiers() == keyboardModifiers()) {
        // calculate zoom
        const int xpos = event->x();
        const int degree = event->delta() / 60;
        qint64 spp = geometry.spp();
        // zoom in
        if (degree > 0) {
            if (spp > 0)
                spp /= qAbs(degree);
            else
                spp *= qAbs(degree);

            if (spp == 0 || spp == 1)
                spp = -1;
        }
        // zoom out
        else if (degree < 0) {
            if (spp > 0)
                spp *= qAbs(degree);
            else
                spp /= qAbs(degree);

            if (spp == 0 || spp == 1)
                spp = 2;
        }

        const QseGeometry result = geometry.replaceSpp(spp);
        const qint64 sampleA = QseGeometry::calcSampleIndex(geometry, xpos);
        const qint64 sampleB = QseGeometry::calcSampleIndex(result, xpos);
        qint64 x = geometry.x() + (sampleA - sampleB);

        // optimization: for exclude recalculation the peaks for zoom out
        if (result.spp() > 0)
            if (x % result.spp() != 0)
                x -= x % result.spp();

        emit geometryChanged(result.replaceX(x));
    }
}
