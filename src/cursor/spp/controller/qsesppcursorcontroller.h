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
#ifndef QSESPPCURSORCONTROLLER_H
#define QSESPPCURSORCONTROLLER_H

#include "qseabstractsppcontroller.h"
class QseCursor;


class QseSppCursorController : public QseAbstractSppController
{
    Q_OBJECT
public:
    explicit QseSppCursorController(QObject *parent = 0);

    inline QseCursor *cursor() const;
    void setCursor(QseCursor *cursor);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect,
                        const QseSppGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect,
                         const QseSppGeometry &geometry);
    virtual void keyPressEvent(QKeyEvent *event, const QRect &rect,
                               const QseSppGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect,
                                 const QseSppGeometry &geometry);
private:
    QseCursor *m_cursor;
};

QseCursor *QseSppCursorController::cursor() const
{
    return m_cursor;
}


#endif // QSESPPCURSORCONTROLLER_H
