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
#include "qseabstractspwwidget.h"
#include "qseabstractspwcontroller.h"


QseAbstractSpwWidget::QseAbstractSpwWidget(QWidget *parent,
        Qt::WindowFlags f) : QseAbstractWidget(parent, f)
{
    m_controller = 0;
}

void QseAbstractSpwWidget::setGeometry(const QseSpwGeometry &geometry)
{
    if (m_geometry != geometry)
    {
        m_geometry = geometry;
        setUpdateOnce(true);
    }
}

void QseAbstractSpwWidget::setController(QseAbstractSpwController *controller)
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

void QseAbstractSpwWidget::controller_destroyed()
{
    m_controller = 0;
}

void QseAbstractSpwWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseMoveEvent(event, rect(), geometry());
}

void QseAbstractSpwWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mousePressEvent(event, rect(), geometry());
}

void QseAbstractSpwWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseReleaseEvent(event, rect(), geometry());
}

void QseAbstractSpwWidget::wheelEvent(QWheelEvent *event)
{
    if (m_controller)
        m_controller->wheelEvent(event, rect(), geometry());
}

void QseAbstractSpwWidget::keyPressEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyPressEvent(event, rect(), geometry());
}

void QseAbstractSpwWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyReleaseEvent(event, rect(), geometry());
}
