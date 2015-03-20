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
#include "qsesppstandardcursorcontroller.h"
#include <QMouseEvent>
#include "qsesppgeometry.h"
#include "qsecursor.h"


QseSppStandardCursorController::QseSppStandardCursorController(
        QObject *parent) : QseAbstractSppStandardController(parent)
{
    m_cursor = 0;
}

void QseSppStandardCursorController::setCursor(QseCursor *cursor)
{
    m_cursor = cursor;
}

void QseSppStandardCursorController::mouseMoveEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_cursor
            && event->buttons() == Qt::LeftButton
            && event->modifiers() == Qt::ControlModifier)
    {
        m_cursor->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }

    updateCursor(event->modifiers());
}

void QseSppStandardCursorController::mousePressEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_cursor
            && event->button() == mouseButtons()
            && event->modifiers() == keyboardModifiers())
    {
        m_cursor->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }

    updateCursor(event->modifiers());
}

void QseSppStandardCursorController::keyPressEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    updateCursor(event->modifiers());
}

void QseSppStandardCursorController::keyReleaseEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    updateCursor(event->modifiers());
}

void QseSppStandardCursorController::updateCursor(Qt::KeyboardModifiers km)
{
    if (m_cursor && km == keyboardModifiers())
    {
        emit cursorChanged(QCursor(Qt::IBeamCursor));
    }
    else
    {
        emit cursorChanged(defaultCursor());
    }
}
