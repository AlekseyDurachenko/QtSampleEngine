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
#ifndef QSECOMPOSITCONTROLLER_H
#define QSECOMPOSITCONTROLLER_H


#include "qseabstractcontroller.h"


class QseCompositController : public QseAbstractController
{
    Q_OBJECT
public:
    explicit QseCompositController(QObject *parent = 0);

    inline const QList<QseAbstractController *> controllers() const;
    void setControllers(const QList<QseAbstractController *> &controllers);

private slots:
    void controller_geometryChanged(const QseGeometry &geometry);
    void controller_cursorChanged(const QCursor &cursor);
    void controller_destroyed(QObject *obj);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void wheelEvent(QWheelEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void keyPressEvent(QKeyEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect, const QseGeometry &geometry);

private:
    QList<QseAbstractController *> m_controllers;
};

const QList<QseAbstractController *> QseCompositController::controllers() const
{
    return m_controllers;
}


#endif // QSECOMPOSITCONTROLLER_H
