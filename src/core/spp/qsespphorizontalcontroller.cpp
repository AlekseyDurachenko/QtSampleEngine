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
#include "qsespphorizontalcontroller.h"
#include <QMouseEvent>


QseSppHorizontalController::QseSppHorizontalController(QObject *parent) :
    QseAbstractSppController(parent)
{
    m_dragAction = false;
    setDefaultCursor(Qt::OpenHandCursor);
}

void QseSppHorizontalController::mouseMoveEvent(QMouseEvent *event,
        const QRect &, const QseSppGeometry &geometry)
{
    // if left button is pressed, we shuld move the Y axis of the plotter
    if (m_dragAction)
    {
        qint64 value = m_dragPrevPos.x() - event->x();

        if (geometry.samplesPerPixel() < 0)
            value /= -geometry.samplesPerPixel();
        else
            value *= geometry.samplesPerPixel();

        if (value != 0)
        {
            m_dragPrevPos = event->pos();
            emit geometryChanged(geometry.addX(value));
        }
    }
}

void QseSppHorizontalController::mousePressEvent(QMouseEvent *event,
        const QRect &, const QseSppGeometry &)
{
    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::NoModifier)
    {
        m_dragAction = true;
        m_dragPrevPos = event->pos();
        emit cursorChanged(QCursor(Qt::ClosedHandCursor));
    }
}

void QseSppHorizontalController::mouseReleaseEvent(QMouseEvent *event,
        const QRect &, const QseSppGeometry &)
{
    // after left button of the mouse will be release
    // we should finished the moving
    if (!(event->buttons() & Qt::LeftButton))
    {
        m_dragAction = false;
        emit cursorChanged(defaultCursor());
    }
}
