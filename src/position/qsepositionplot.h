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
#ifndef QSEPOSITIONPLOT_H
#define QSEPOSITIONPLOT_H


#include "qsegeometry.h"
#include "qseabstractplot.h"
#include <QPen>
class QsePosition;


class QsePositionPlot : public QseAbstractPlot
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit QsePositionPlot(QObject *parent = 0);

    inline const QPen &pen() const;
    void setPen(const QPen &pen);

    inline qreal opacity() const;
    void setOpacity(qreal opacity);

    inline QsePosition *position() const;
    void setPosition(QsePosition *position);

    virtual bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);

private slots:
    void position_destroyed();

private:
    QsePosition *m_position;
    qreal m_opacity;
    QPen m_pen;
};

const QPen &QsePositionPlot::pen() const
{
    return m_pen;
}

qreal QsePositionPlot::opacity() const
{
    return m_opacity;
}


#endif // QSEPOSITIONPLOT_H
