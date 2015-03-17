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
#ifndef QSEABSTRACTSPPPLOT_H
#define QSEABSTRACTSPPPLOT_H

#include <QRect>
#include "qseabstractplot.h"
#include "qsesppgeometry.h"
class QPainter;


class QseAbstractSppPlot : public QseAbstractPlot
{
    Q_OBJECT
public:
    explicit QseAbstractSppPlot(QObject *parent = 0);

    inline const QRect &lastRect() const;
    inline const QseSppGeometry &lastGeometry() const;

    virtual bool isVisible(const QRect &rect, const QseSppGeometry &geometry);
    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect,
                      const QseSppGeometry &geometry);
protected:
    QRect m_lastRect;
    QseSppGeometry m_lastGeometry;
};

const QRect &QseAbstractSppPlot::lastRect() const
{
    return m_lastRect;
}

const QseSppGeometry &QseAbstractSppPlot::lastGeometry() const
{
    return m_lastGeometry;
}


#endif // QSEABSTRACTSPPPLOT_H
