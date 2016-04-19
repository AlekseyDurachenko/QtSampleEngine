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
#include "qsecompositcontroller.h"


QseCompositController::QseCompositController(QObject *parent)
    : QseAbstractController(parent)
{
}

void QseCompositController::setControllers(const QList<QseAbstractController *> &controllers)
{
    if (m_controllers == controllers) {
        return;
    }

    foreach (QseAbstractController *controller, m_controllers) {
        disconnect(controller, 0, this, 0);
    }

    m_controllers = controllers;
    foreach (QseAbstractController *controller, m_controllers) {
        connect(controller, SIGNAL(cursorChanged(QCursor)),
                this, SLOT(controller_cursorChanged(QCursor)));
        connect(controller, SIGNAL(geometryChanged(QseGeometry)),
                this, SLOT(controller_geometryChanged(QseGeometry)));
        connect(controller, SIGNAL(destroyed(QObject *)),
                this, SLOT(controller_destroyed(QObject *)));
    }
}

void QseCompositController::controller_geometryChanged(const QseGeometry &geometry)
{
    emit geometryChanged(geometry);
}

void QseCompositController::controller_cursorChanged(const QCursor &cursor)
{
    const QseAbstractController *controller =
        qobject_cast<QseAbstractController *>(sender());

    // NOTE: it doen't working for Bitmap default cursor
    if (controller->defaultCursor().shape() == cursor.shape()
            && cursor.shape() != Qt::BitmapCursor) {
        emit cursorChanged(defaultCursor());
    }
    else {
        emit cursorChanged(cursor);
    }
}

void QseCompositController::controller_destroyed(QObject *obj)
{
    m_controllers.removeAll(qobject_cast<QseAbstractController *>(obj));
}

void QseCompositController::mouseMoveEvent(QMouseEvent *event,
                                           const QRect &rect,
                                           const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->mouseMoveEvent(event, rect, geometry);
        }
    }
}

void QseCompositController::mousePressEvent(QMouseEvent *event,
                                            const QRect &rect,
                                            const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->mousePressEvent(event, rect, geometry);
        }
    }
}

void QseCompositController::mouseReleaseEvent(QMouseEvent *event,
                                              const QRect &rect,
                                              const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->mouseReleaseEvent(event, rect, geometry);
        }
    }
}

void QseCompositController::wheelEvent(QWheelEvent *event,
                                       const QRect &rect,
                                       const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->wheelEvent(event, rect, geometry);
        }
    }
}

void QseCompositController::keyPressEvent(QKeyEvent *event,
                                          const QRect &rect,
                                          const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->keyPressEvent(event, rect, geometry);
        }
    }
}

void QseCompositController::keyReleaseEvent(QKeyEvent *event,
                                            const QRect &rect,
                                            const QseGeometry &geometry)
{
    foreach (QseAbstractController *controller, m_controllers) {
        if (controller->isEnabled()) {
            controller->keyReleaseEvent(event, rect, geometry);
        }
    }
}
