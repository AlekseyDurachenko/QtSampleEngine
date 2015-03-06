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
#ifndef QSEABSTRACTCONTROLLER_H
#define QSEABSTRACTCONTROLLER_H

#include <QObject>
#include <QCursor>
#include "qsesppgeometry.h"
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class QseAbstractWidget;


class QseAbstractController : public QObject
{
    Q_OBJECT
    friend class QseAbstractWidget;
public:
    explicit QseAbstractController(QObject *parent = 0);

    virtual QCursor defaultCursor() const;
private:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect,
                                const QseSppGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect,
                                 const QseSppGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect,
                                   const QseSppGeometry &geometry);
    virtual void wheelEvent(QWheelEvent *event, const QRect &rect,
                            const QseSppGeometry &geometry);
    virtual void keyPressEvent(QKeyEvent *event, const QRect &rect,
                               const QseSppGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect,
                                 const QseSppGeometry &geometry);
signals:
    void geometryChanged(const QseSppGeometry &geometry);
    void cursorChanged(const QCursor &cursor);
};


#endif // QSEABSTRACTCONTROLLER_H
