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
#include "qseabstractcontrollerproxy.h"


QseAbstractControllerProxy::QseAbstractControllerProxy(QObject *parent)
    : QseAbstractController(parent)
{
    m_controller = 0;
}

void QseAbstractControllerProxy::setController(QseAbstractController *controller)
{
    if (m_controller == controller) {
        return;
    }

    if (m_controller) {
        disconnect(m_controller, 0, this, 0);
    }

    m_controller = controller;
    if (m_controller) {
        connect(m_controller, SIGNAL(cursorChanged(QCursor)),
                this, SIGNAL(cursorChanged(QCursor)));
        connect(m_controller, SIGNAL(geometryChanged(QseGeometry)),
                this, SIGNAL(geometryChanged(QseGeometry)));
        connect(m_controller, SIGNAL(destroyed()),
                this, SLOT(controller_destroyed()));
    }
}

void QseAbstractControllerProxy::controller_destroyed()
{
    m_controller = 0;
}

void QseAbstractControllerProxy::mouseMoveEvent(QMouseEvent *event,
                                                const QRect &rect,
                                                const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->mouseMoveEvent(event, rect, geometry);
}

void QseAbstractControllerProxy::mousePressEvent(QMouseEvent *event,
                                                 const QRect &rect,
                                                 const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->mousePressEvent(event, rect, geometry);
}

void QseAbstractControllerProxy::mouseReleaseEvent(QMouseEvent *event,
                                                   const QRect &rect,
                                                   const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->mouseReleaseEvent(event, rect, geometry);
}

void QseAbstractControllerProxy::wheelEvent(QWheelEvent *event,
                                            const QRect &rect,
                                            const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->wheelEvent(event, rect, geometry);
}

void QseAbstractControllerProxy::keyPressEvent(QKeyEvent *event,
                                               const QRect &rect,
                                               const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->keyPressEvent(event, rect, geometry);
}

void QseAbstractControllerProxy::keyReleaseEvent(QKeyEvent *event,
                                                 const QRect &rect,
                                                 const QseGeometry &geometry)
{
    if (m_controller && m_controller->isEnabled())
        m_controller->keyReleaseEvent(event, rect, geometry);
}
