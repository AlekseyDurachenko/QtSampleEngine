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
#include "qsesppstandardhorizontalzoomcontroller.h"
#include <QWheelEvent>


QseSppStandardHorizontalZoomController::QseSppStandardHorizontalZoomController(
        QObject *parent) : QseAbstractSppStandardController(parent)
{
}


void QseSppStandardHorizontalZoomController::wheelEvent(QWheelEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (event->modifiers() == keyboardModifiers())
    {
        // calculate zoom
        const int xpos = event->x() - zeroPos().x();
        int degree = event->delta() / 60;
        qint64 spp = geometry.samplesPerPixel();
        // zoom in
        if (degree > 0)
        {
            if (spp > 0)
                spp /= qAbs(degree);
            else
                spp *= qAbs(degree);
            if (spp == 0 || spp == 1)
                spp = -1;
        }
        // zoom out
        else if (degree < 0)
        {
            if (spp > 0)
                spp *= qAbs(degree);
            else
                spp /= qAbs(degree);
            if (spp == 0 || spp == 1)
                spp = 2;
        }

        QseSppGeometry result = geometry.replaceSamplesPerPixel(spp);
        qint64 sampleA = QseSppGeometry::calcSampleIndex(geometry, xpos);
        qint64 sampleB = QseSppGeometry::calcSampleIndex(result, xpos);
        qint64 x = geometry.x() + (sampleA - sampleB);

        emit geometryChanged(result.replaceX(x));
    }
}
