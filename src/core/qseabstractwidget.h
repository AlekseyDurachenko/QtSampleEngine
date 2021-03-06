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
#ifndef QSEABSTRACTWIDGET_H
#define QSEABSTRACTWIDGET_H


#include "qsegeometry.h"
#include <QWidget>
class QseAbstractController;
class QseAbstractLimiter;


class QseAbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QseAbstractWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline bool isUpdateOnce() const;

    inline QseAbstractController *controller() const;
    void setController(QseAbstractController *controller);

    inline QseAbstractLimiter *limiter() const;
    void setLimiter(QseAbstractLimiter *limiter);

    inline const QseGeometry &geometry() const;

signals:
    void geometryChanged(const QseGeometry &geometry);

public slots:
    void setUpdateOnce(bool need = true);
    void setGeometry(const QseGeometry &geometry);

protected slots:
    void setCurrentCursor(const QCursor &cursor);

private slots:
    void controller_destroyed();
    void limiter_changed();
    void limiter_destroyed();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QseAbstractController *m_controller;
    QseAbstractLimiter *m_limiter;
    QseGeometry m_geometry;
    bool m_updateOnce;
};

bool QseAbstractWidget::isUpdateOnce() const
{
    return m_updateOnce;
}

QseAbstractController *QseAbstractWidget::controller() const
{
    return m_controller;
}

QseAbstractLimiter *QseAbstractWidget::limiter() const
{
    return m_limiter;
}

const QseGeometry &QseAbstractWidget::geometry() const
{
    return m_geometry;
}


#endif // QSEABSTRACTWIDGET_H
