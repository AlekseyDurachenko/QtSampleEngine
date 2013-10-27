// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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


QseAbstractWidget::QseAbstractWidget(QWidget *parent)
    : QWidget(parent)
{
    m_controller = 0;
    m_updateOnce = true;
}

void QseAbstractWidget::setGeometry(const QseGeometry &geometry)
{
    if (geometry != m_geometry)
    {
        m_geometry = geometry;
        setUpdateOnce(true);
    }
}

void QseAbstractWidget::setCurrentCursor(const QCursor &cursor)
{
    setCursor(cursor);
}

void QseAbstractWidget::setController(QseAbstractController *controller)
{
    if (m_controller)
        disconnect(m_controller, SIGNAL(cursorChanged(QCursor)), this, 0);

    m_controller = controller;
    if (m_controller)
    {
        connect(m_controller, SIGNAL(cursorChanged(QCursor)), this, SLOT(setCurrentCursor(QCursor)));
        setCurrentCursor(m_controller->defaultCursor());
    }
}

void QseAbstractWidget::setUpdateOnce(bool need)
{
    m_updateOnce = need;
    if (m_updateOnce)
        update();
}

void QseAbstractWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseMoveEvent(event, rect(), geometry());
}

void QseAbstractWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mousePressEvent(event, rect(), geometry());
}

void QseAbstractWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_controller)
        m_controller->mouseReleaseEvent(event, rect(), geometry());
}

void QseAbstractWidget::wheelEvent(QWheelEvent *event)
{
    if (m_controller)
        m_controller->wheelEvent(event, rect(), geometry());
}

void QseAbstractWidget::keyPressEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyPressEvent(event, rect(), geometry());
}

void QseAbstractWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (m_controller)
        m_controller->keyReleaseEvent(event, rect(), geometry());
}
