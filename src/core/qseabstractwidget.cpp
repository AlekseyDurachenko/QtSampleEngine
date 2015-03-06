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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#include "qseabstractwidget.h"
#include "qseabstractcontroller.h"


template<class Geometry>
QseAbstractWidget<Geometry>::QseAbstractWidget(QWidget *parent)
    : QWidget(parent)
{
    m_controller = 0;
    m_updateOnce = true;
}

template<class Geometry>
void QseAbstractWidget<Geometry>::setGeometry(const Geometry &geometry)
{
    if (m_geometry == geometry)
        return;

    m_geometry = geometry;
    setUpdateOnce(true);
}

template<class Geometry>
void QseAbstractWidget<Geometry>::setController(QseAbstractController<Geometry> *controller)
{
    if (m_controller)
        disconnect(m_controller, 0, this, 0);

    m_controller = controller;
    if (m_controller)
    {
        connect(m_controller, SIGNAL(cursorChanged(QCursor)),
                this, SLOT(setCurrentCursor(QCursor)));
        connect(m_controller, SIGNAL(destroyed()),
                this, SLOT(controller_destroyed()));
        setCurrentCursor(m_controller->defaultCursor());
    }
}

/*! This method set flag isUpdateOnce() to true,
 *  and call the update() method.
 */
template<class Geometry>
void QseAbstractWidget<Geometry>::setUpdateOnce(bool need)
{
    if (m_updateOnce)
        return;

    m_updateOnce = need;
    if (m_updateOnce)
        update();
}

template<class Geometry>
void QseAbstractWidget<Geometry>::setCurrentCursor(const QCursor &cursor)
{
    setCursor(cursor);
}

template<class Geometry>
void QseAbstractWidget<Geometry>::controller_destroyed()
{
    m_controller = 0;
}

template<class Geometry>
void QseAbstractWidget<Geometry>::mouseMoveEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseMoveEvent(event, rect(), geometry());
}

template<class Geometry>
void QseAbstractWidget<Geometry>::mousePressEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mousePressEvent(event, rect(), geometry());
}

template<class Geometry>
void QseAbstractWidget<Geometry>::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseReleaseEvent(event, rect(), geometry());
}

template<class Geometry>
void QseAbstractWidget<Geometry>::wheelEvent(QWheelEvent *event)
{
    if (m_controller)
        m_controller->wheelEvent(event, rect(), geometry());
}

template<class Geometry>
void QseAbstractWidget<Geometry>::keyPressEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyPressEvent(event, rect(), geometry());
}

template<class Geometry>
void QseAbstractWidget<Geometry>::keyReleaseEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyReleaseEvent(event, rect(), geometry());
}
