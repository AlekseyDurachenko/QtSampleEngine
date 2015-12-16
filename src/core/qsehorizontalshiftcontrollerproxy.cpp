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
#include "qsehorizontalshiftcontrollerproxy.h"
#include <QWheelEvent>
#include <QMouseEvent>


QseHorizontalShiftControllerProxy::QseHorizontalShiftControllerProxy(QObject *parent)
    : QseAbstractControllerProxy(parent)
{
    m_shift = 0;
}

void QseHorizontalShiftControllerProxy::setShift(int value)
{
    if (m_shift != value) {
        m_shift = value;
        emit shiftChanged(m_shift);
    }
}

void QseHorizontalShiftControllerProxy::mouseMoveEvent(QMouseEvent *event,
                                                       const QRect &rect,
                                                       const QseGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QMouseEvent *e = new QMouseEvent(event->type(),
                                     pos,
                                     event->button(),
                                     event->buttons(),
                                     event->modifiers());

    QseAbstractControllerProxy::mouseMoveEvent(e, rect, geometry);

    delete e;
}

void QseHorizontalShiftControllerProxy::mousePressEvent(QMouseEvent *event,
                                                        const QRect &rect,
                                                        const QseGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QMouseEvent *e = new QMouseEvent(event->type(),
                                     pos,
                                     event->button(),
                                     event->buttons(),
                                     event->modifiers());

    QseAbstractControllerProxy::mousePressEvent(e, rect, geometry);

    delete e;
}

void QseHorizontalShiftControllerProxy::mouseReleaseEvent(QMouseEvent *event,
                                                          const QRect &rect,
                                                          const QseGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());

    QMouseEvent *e = new QMouseEvent(event->type(),
                                     pos,
                                     event->button(),
                                     event->buttons(),
                                     event->modifiers());

    QseAbstractControllerProxy::mouseReleaseEvent(e, rect, geometry);

    delete e;
}

void QseHorizontalShiftControllerProxy::wheelEvent(QWheelEvent *event,
                                                   const QRect &rect,
                                                   const QseGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QWheelEvent *e = new QWheelEvent(pos,
                                     event->delta(),
                                     event->buttons(),
                                     event->modifiers(),
                                     event->orientation());

    QseAbstractControllerProxy::wheelEvent(e, rect, geometry);

    delete e;
}
