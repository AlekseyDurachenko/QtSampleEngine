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
#include "qsesppcompositorcontroller.h"


QseSppCompositorController::QseSppCompositorController(QObject *parent) :
    QseAbstractSppController(parent)
{
}

void QseSppCompositorController::setControllers(
        const QList<QseAbstractSppController *> &controllers)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        disconnect(controller, 0, this, 0);

    m_controllers = controllers;
    foreach (QseAbstractSppController *controller, m_controllers)
    {
        connect(controller, SIGNAL(cursorChanged(QCursor)),
                this, SLOT(controller_cursorChanged(QCursor)));
        connect(controller, SIGNAL(geometryChanged(QseSppGeometry)),
                this, SLOT(controller_geometryChanged(QseSppGeometry)));
        connect(controller, SIGNAL(destroyed(QObject*)),
                this, SLOT(controller_destroyed(QObject*)));
    }
}

void QseSppCompositorController::controller_geometryChanged(
        const QseSppGeometry &geometry)
{
    emit geometryChanged(geometry);
}

void QseSppCompositorController::controller_cursorChanged(const QCursor &cursor)
{
    QseAbstractSppController *controller =
            qobject_cast<QseAbstractSppController *>(sender());

    // TODO: it doen't working for Bitmap default cursor
    if (controller->defaultCursor().shape() == cursor.shape()
            && cursor.shape() != Qt::BitmapCursor)
        emit cursorChanged(defaultCursor());
    else
        emit cursorChanged(cursor);
}

void QseSppCompositorController::controller_destroyed(QObject *obj)
{
    m_controllers.removeAll(qobject_cast<QseAbstractSppController *>(obj));
}

void QseSppCompositorController::mouseMoveEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->mouseMoveEvent(event, rect, geometry);
}

void QseSppCompositorController::mousePressEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->mousePressEvent(event, rect, geometry);
}

void QseSppCompositorController::mouseReleaseEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->mouseReleaseEvent(event, rect, geometry);
}

void QseSppCompositorController::wheelEvent(QWheelEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->wheelEvent(event, rect, geometry);
}

void QseSppCompositorController::keyPressEvent(QKeyEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->keyPressEvent(event, rect, geometry);
}

void QseSppCompositorController::keyReleaseEvent(QKeyEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    foreach (QseAbstractSppController *controller, m_controllers)
        controller->keyReleaseEvent(event, rect, geometry);
}