// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSEMONOCOLORCOVERPLOT_H
#define QSEMONOCOLORCOVERPLOT_H

#include <QPen>
#include <QColor>
#include "qseabstractsppplot.h"


class QseMonocolorSppCoverPlot : public QseAbstractSppPlot
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit QseMonocolorSppCoverPlot(QObject *parent = 0);

    inline const QColor &color() const;
    void setColor(const QColor &color);

    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect,
              const QseSppGeometry &geometry);
private:
    QColor m_color;
};

const QColor &QseMonocolorSppCoverPlot::color() const
{
    return m_color;
}


#endif // QSEMONOCOLORCOVERPLOT_H
