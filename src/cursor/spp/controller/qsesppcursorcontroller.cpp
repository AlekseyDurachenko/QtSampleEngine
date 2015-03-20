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
#include "qsesppcursorcontroller.h"
#include <QMouseEvent>
#include "qsesppgeometry.h"
#include "qsecursor.h"


QseSppCursorController::QseSppCursorController(QObject *parent) :
    QseAbstractSppController(parent)
{
    m_cursor = 0;
}

void QseSppCursorController::setCursor(QseCursor *cursor)
{
    m_cursor = cursor;
}

void QseSppCursorController::mouseMoveEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_cursor
            && event->buttons() == Qt::LeftButton
            && event->modifiers() == Qt::ControlModifier)
    {
        m_cursor->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }
    else if (m_cursor
             && event->modifiers() == Qt::ControlModifier)
    {
        emit cursorChanged(QCursor(Qt::IBeamCursor));
    }
}

void QseSppCursorController::mousePressEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_cursor
            && event->button() == Qt::LeftButton
            && event->modifiers() == Qt::ControlModifier)
    {
        m_cursor->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }
}

void QseSppCursorController::keyPressEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    if (m_cursor && event->modifiers() == Qt::ControlModifier)
    {
        emit cursorChanged(QCursor(Qt::IBeamCursor));
    }
}

void QseSppCursorController::keyReleaseEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    if (m_cursor && event->modifiers() == Qt::NoModifier)
    {
        emit cursorChanged(defaultCursor());
    }
}
