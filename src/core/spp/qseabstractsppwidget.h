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
#ifndef QSEABSTRACTSPPWIDGET_H
#define QSEABSTRACTSPPWIDGET_H

#include "qseabstractwidget.h"
#include "qsesppgeometry.h"
class QseAbstractSppController;


class QseAbstractSppWidget : public QseAbstractWidget
{
    Q_OBJECT
public:
    explicit QseAbstractSppWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline const QseAbstractSppController *controller() const;
    void setController(QseAbstractSppController *controller);

    inline const QseSppGeometry &geometry() const;
public slots:
    void setGeometry(const QseSppGeometry& geometry);
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
    QseAbstractSppController *m_controller;
    QseSppGeometry m_geometry;
    bool m_updateOnce;
};

const QseAbstractSppController *QseAbstractSppWidget::controller() const
{
    return m_controller;
}

const QseSppGeometry &QseAbstractSppWidget::geometry() const
{
    return m_geometry;
}


#endif // QSEABSTRACTSPPWIDGET_H
