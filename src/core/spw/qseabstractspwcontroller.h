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
#ifndef QSEABSTRACTSPWCONTROLLER_H
#define QSEABSTRACTSPWCONTROLLER_H

#include "qseabstractcontroller.h"
#include "qsespwgeometry.h"
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;


class QseAbstractSpwController : public QseAbstractController
{
    Q_OBJECT
    friend class QseAbstractSpwWidget;
public:
    explicit QseAbstractSpwController(QObject *parent = 0);
signals:
    void geometryChanged(const QseSpwGeometry &geometry);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect,
                                const QseSpwGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect,
                                 const QseSpwGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect,
                                   const QseSpwGeometry &geometry);
    virtual void wheelEvent(QWheelEvent *event, const QRect &rect,
                            const QseSpwGeometry &geometry);
    virtual void keyPressEvent(QKeyEvent *event, const QRect &rect,
                               const QseSpwGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect,
                                 const QseSpwGeometry &geometry);
};


#endif // QSEABSTRACTSPWCONTROLLER_H
