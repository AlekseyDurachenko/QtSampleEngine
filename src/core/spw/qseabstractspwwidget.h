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
#ifndef QSEABSTRACTSPWWIDGET_H
#define QSEABSTRACTSPWWIDGET_H

#include "qseabstractwidget.h"
#include "qsespwgeometry.h"
class QseAbstractSpwController;


class QseAbstractSpwWidget : public QseAbstractWidget
{
    Q_OBJECT
public:
    explicit QseAbstractSpwWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline const QseAbstractSpwController *controller() const;
    void setController(QseAbstractSpwController *controller);

    inline const QseSpwGeometry &geometry() const;
public slots:
    void setGeometry(const QseSpwGeometry& geometry);
private slots:
    void controller_destroyed();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QseAbstractSpwController *m_controller;
    QseSpwGeometry m_geometry;
    bool m_updateOnce;
};

const QseAbstractSpwController *QseAbstractSpwWidget::controller() const
{
    return m_controller;
}

const QseSpwGeometry &QseAbstractSpwWidget::geometry() const
{
    return m_geometry;
}


#endif // QSEABSTRACTSPWWIDGET_H
