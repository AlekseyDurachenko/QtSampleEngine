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
#ifndef QSESIGNALCANVASPLOT_H
#define QSESIGNALCANVASPLOT_H


#include "qsegeometry.h"
#include "qseabstractplot.h"
#include <QBrush>
class QseAbstractSignalDataSource;


class QseSignalCanvasPlot : public QseAbstractPlot
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    explicit QseSignalCanvasPlot(QObject *parent = 0);

    inline const QBrush &brush() const;
    void setBrush(const QBrush &brush);

    inline qreal opacity() const;
    void setOpacity(qreal opacity);

    inline QseAbstractSignalDataSource *dataSource() const;
    void setDataSource(QseAbstractSignalDataSource *dataSource);

    virtual bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);

private slots:
    void dataSource_destroyed(QObject *obj);
    void dataSource_dataChanged();

private:
    QseAbstractSignalDataSource *m_dataSource;
    QBrush m_brush;
    qreal m_opacity;
};

const QBrush &QseSignalCanvasPlot::brush() const
{
    return m_brush;
}

qreal QseSignalCanvasPlot::opacity() const
{
    return m_opacity;
}


#endif // QSESIGNALCANVASPLOT_H
