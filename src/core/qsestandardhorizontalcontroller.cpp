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
#include "qsestandardhorizontalcontroller.h"
#include <QMouseEvent>
#include <QDebug>


QseStandardHorizontalController::QseStandardHorizontalController(QObject *parent)
    : QseAbstractStandardController(parent)
{
    m_dragAction = false;
    setDefaultCursor(Qt::OpenHandCursor);
}

void QseStandardHorizontalController::mouseMoveEvent(QMouseEvent *event,
                                                     const QRect &/*rect*/,
                                                     const QseGeometry &geometry)
{
    if (m_dragAction) {
        const int diff = m_dragPrevPos.x() - event->x();
        const qint64 value = static_cast<qint64>(geometry.toRealSpp() * diff);
        if (value != 0) {
            m_dragPrevPos = event->pos();
            emit geometryChanged(geometry.addX(value));
        }
    }
}

void QseStandardHorizontalController::mousePressEvent(QMouseEvent *event,
                                                      const QRect &/*rect*/,
                                                      const QseGeometry &/*geometry*/)
{
    if (event->buttons() == mouseButtons()
            && event->modifiers() == keyboardModifiers()) {
        m_dragAction = true;
        m_dragPrevPos = event->pos();
        emit cursorChanged(QCursor(Qt::ClosedHandCursor));
    }
}

void QseStandardHorizontalController::mouseReleaseEvent(QMouseEvent *event,
                                                        const QRect &/*rect*/,
                                                        const QseGeometry &/*geometry*/)
{
    if (event->buttons() != mouseButtons()) {
        m_dragAction = false;
        emit cursorChanged(defaultCursor());
    }
}

void QseStandardHorizontalController::keyReleaseEvent(QKeyEvent *event,
                                                      const QRect &/*rect*/,
                                                      const QseGeometry &/*geometry*/)
{
    if (event->modifiers() != keyboardModifiers()) {
        m_dragAction = false;
        emit cursorChanged(defaultCursor());
    }
}
