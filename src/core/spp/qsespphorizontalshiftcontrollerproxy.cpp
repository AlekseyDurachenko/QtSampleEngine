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
#include "qsespphorizontalshiftcontrollerproxy.h"
#include <QWheelEvent>
#include <QMouseEvent>


QseSppHorizontalShiftControllerProxy::QseSppHorizontalShiftControllerProxy(
        QObject *parent) : QseAbstractSppControllerProxy(parent)
{
    m_shift = 0;
}

void QseSppHorizontalShiftControllerProxy::setShift(int value)
{
    if (m_shift != value)
    {
        m_shift = value;
        emit shiftChanged(m_shift);
    }
}

void QseSppHorizontalShiftControllerProxy::mouseMoveEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QMouseEvent *e = new QMouseEvent(event->type(), pos, event->button(),
            event->buttons(), event->modifiers());
    QseAbstractSppControllerProxy::mouseMoveEvent(e, rect, geometry);
    delete e;
}

void QseSppHorizontalShiftControllerProxy::mousePressEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QMouseEvent *e = new QMouseEvent(event->type(), pos, event->button(),
            event->buttons(), event->modifiers());
    QseAbstractSppControllerProxy::mousePressEvent(e, rect, geometry);
    delete e;
}

void QseSppHorizontalShiftControllerProxy::mouseReleaseEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QMouseEvent *e = new QMouseEvent(event->type(), pos, event->button(),
            event->buttons(), event->modifiers());
    QseAbstractSppControllerProxy::mouseReleaseEvent(e, rect, geometry);
    delete e;
}

void QseSppHorizontalShiftControllerProxy::wheelEvent(QWheelEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    const QPoint pos = QPoint(event->pos().x() - m_shift, event->pos().y());
    QWheelEvent *e = new QWheelEvent(pos, event->delta(), event->buttons(),
            event->modifiers(), event->orientation());
    QseAbstractSppControllerProxy::wheelEvent(e, rect, geometry);
    delete e;
}
