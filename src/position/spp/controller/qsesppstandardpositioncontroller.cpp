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
#include "qsesppstandardpositioncontroller.h"
#include <QMouseEvent>
#include "qsesppgeometry.h"
#include "qseposition.h"


QseSppStandardPositionController::QseSppStandardPositionController(
        QObject *parent) : QseAbstractSppStandardController(parent)
{
    m_position = 0;
}

void QseSppStandardPositionController::setPosition(QsePosition *position)
{
    if (m_position == position)
        return;

    if (m_position)
        disconnect(m_position, 0, this, 0);

    m_position = position;
    if (m_position)
    {
        connect(m_position, SIGNAL(destroyed()),
                this, SLOT(position_destroyed()));
    }
}

void QseSppStandardPositionController::mouseMoveEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_position
            && event->buttons() == Qt::LeftButton
            && event->modifiers() == Qt::ControlModifier)
    {
        m_position->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }

    updateCursor(event->modifiers());
}

void QseSppStandardPositionController::mousePressEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_position
            && event->button() == mouseButtons()
            && event->modifiers() == keyboardModifiers())
    {
        m_position->setIndex(QseSppGeometry::calcSampleIndex(geometry, event->x()));
    }

    updateCursor(event->modifiers());
}

void QseSppStandardPositionController::keyPressEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    updateCursor(event->modifiers());
}

void QseSppStandardPositionController::keyReleaseEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &/*geometry*/)
{
    updateCursor(event->modifiers());
}

void QseSppStandardPositionController::position_destroyed()
{
    m_position = 0;
}

void QseSppStandardPositionController::updateCursor(Qt::KeyboardModifiers km)
{
    if (m_position && km == keyboardModifiers())
    {
        emit cursorChanged(QCursor(Qt::IBeamCursor));
    }
    else
    {
        emit cursorChanged(defaultCursor());
    }
}
