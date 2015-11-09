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
#ifndef QSESPPSTANDARDPOSITIONCONTROLLER_H
#define QSESPPSTANDARDPOSITIONCONTROLLER_H

#include "qseabstractsppstandardcontroller.h"
class QsePosition;


class QseSppStandardPositionController : public QseAbstractSppStandardController
{
    Q_OBJECT
public:
    explicit QseSppStandardPositionController(QObject *parent = 0);

    inline QsePosition *position() const;
    void setPosition(QsePosition *position);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect, const QseSppGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect, const QseSppGeometry &geometry);
    virtual void keyPressEvent(QKeyEvent *event, const QRect &rect, const QseSppGeometry &geometry);
    virtual void keyReleaseEvent(QKeyEvent *event, const QRect &rect, const QseSppGeometry &geometry);

private slots:
    void position_destroyed();

private:
    void updateCursor(Qt::KeyboardModifiers km);

private:
    QsePosition *m_position;
};

QsePosition *QseSppStandardPositionController::position() const
{
    return m_position;
}


#endif // QSESPPSTANDARDPOSITIONCONTROLLER_H
