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
#include "qseabstractwidget.h"
#include "qseabstractcontroller.h"
#include "qseabstractlimiter.h"


QseAbstractWidget::QseAbstractWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    m_controller = 0;
    m_limiter = 0;
    m_updateOnce = true;
}

/*! This method set flag isUpdateOnce() to true,
 *  and call the update() method.
 */
void QseAbstractWidget::setUpdateOnce(bool need)
{
    //if (m_updateOnce != need) {
    m_updateOnce = need;
    if (m_updateOnce) {
        update();
    }
    //}
}

void QseAbstractWidget::setCurrentCursor(const QCursor &cursor)
{
    setCursor(cursor);
}

void QseAbstractWidget::setGeometry(const QseGeometry &geometry)
{
    QseGeometry limitedGeometry = geometry;
    if (m_limiter) {
        limitedGeometry = m_limiter->limit(limitedGeometry);
    }

    if (m_geometry != limitedGeometry) {
        m_geometry = limitedGeometry;
        setUpdateOnce(true);
        emit geometryChanged(m_geometry);
    }
}

void QseAbstractWidget::setController(QseAbstractController *controller)
{
    if (m_controller == controller) {
        return;
    }

    if (m_controller) {
        disconnect(m_controller, 0, this, 0);
    }

    m_controller = controller;
    if (m_controller) {
        connect(m_controller, SIGNAL(cursorChanged(QCursor)),
                this, SLOT(setCurrentCursor(QCursor)));
        connect(m_controller, SIGNAL(geometryChanged(QseGeometry)),
                this, SLOT(setGeometry(QseGeometry)));
        connect(m_controller, SIGNAL(destroyed()),
                this, SLOT(controller_destroyed()));

        setCurrentCursor(m_controller->defaultCursor());
    }
}

void QseAbstractWidget::setLimiter(QseAbstractLimiter *limiter)
{
    if (m_limiter == limiter) {
        return;
    }

    if (m_limiter) {
        disconnect(m_limiter, 0, this, 0);
    }

    m_limiter = limiter;
    if (m_limiter) {
        connect(m_limiter, SIGNAL(changed()),
                this, SLOT(limiter_changed()));
        connect(m_limiter, SIGNAL(destroyed()),
                this, SLOT(limiter_destroyed()));
    }

    setGeometry(geometry());
}

void QseAbstractWidget::controller_destroyed()
{
    m_controller = 0;
}

void QseAbstractWidget::limiter_changed()
{
    setGeometry(geometry());
}

void QseAbstractWidget::limiter_destroyed()
{
    m_limiter = 0;
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
