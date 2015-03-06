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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#include "qseabstractcontroller.h"


QseAbstractController::QseAbstractController(QObject *parent) :
    QObject(parent)
{
}

/*! The default cursor for the widget, which use this controller
 */
QCursor QseAbstractController::defaultCursor() const
{
    return QCursor();
}

void QseAbstractController::mouseMoveEvent(QMouseEvent *, const QRect &,
        const QseSppGeometry &)
{
}

void QseAbstractController::mousePressEvent(QMouseEvent *, const QRect &,
        const QseSppGeometry &)
{
}

void QseAbstractController::mouseReleaseEvent(QMouseEvent *, const QRect &,
        const QseSppGeometry &)
{
}

void QseAbstractController::wheelEvent(QWheelEvent *, const QRect &,
        const QseSppGeometry &)
{
}

void QseAbstractController::keyPressEvent(QKeyEvent *, const QRect &,
        const QseSppGeometry &)
{
}

void QseAbstractController::keyReleaseEvent(QKeyEvent *, const QRect &,
        const QseSppGeometry &)
{
}
