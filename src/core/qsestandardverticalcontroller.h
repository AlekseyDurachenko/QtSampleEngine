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
#ifndef QSESTANDARDVERTICALCONTROLLER_H
#define QSESTANDARDVERTICALCONTROLLER_H


#include "qseabstractstandardcontroller.h"


class QseStandardVerticalController : public QseAbstractStandardController
{
    Q_OBJECT
public:
    explicit QseStandardVerticalController(QObject *parent = 0);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect, const QseGeometry &geometry);

private:
    // true  -- ready to move
    // false -- not ready to move
    bool m_dragAction;
    // store the previouse position of the cursor, when we drag the Y axis
    QPoint m_dragPrevPos;
};


#endif // QSESTANDARDVERTICALCONTROLLER_H
