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
#include "qseabstractspwcontroller.h"


QseAbstractSpwController::QseAbstractSpwController(QObject *parent) :
    QseAbstractController(parent)
{
}

void QseAbstractSpwController::mouseMoveEvent(QMouseEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}

void QseAbstractSpwController::mousePressEvent(QMouseEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}

void QseAbstractSpwController::mouseReleaseEvent(QMouseEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}

void QseAbstractSpwController::wheelEvent(QWheelEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}

void QseAbstractSpwController::keyPressEvent(QKeyEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}

void QseAbstractSpwController::keyReleaseEvent(QKeyEvent *event,
        const QRect &rect, const QseSpwGeometry &geometry)
{
    Q_UNUSED(event);
    Q_UNUSED(rect);
    Q_UNUSED(geometry);
}
