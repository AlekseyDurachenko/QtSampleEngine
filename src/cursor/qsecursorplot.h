// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSECURSORPLOT_H
#define QSECURSORPLOT_H

#include <QObject>
#include <QPainter>
#include "qsesppgeometry.h"
#include "qseabstractplot.h"
#include "qsecursor.h"

/*! \brief The QseCursor class shows the position of a cursor
 *
 *  This class draws the vertical line
 */
class QseCursorPlot : public QseAbstractPlot
{
    Q_OBJECT
public:
    explicit QseCursorPlot(QObject *parent = 0);

    inline const QPen &pen() const;
    inline qreal opacity() const;    
    void setPen(const QPen &pen);
    void setOpacity(qreal opacity);
    void setCursor(QseCursor *cursor);

    bool isVisible(const QRect &rect, const QseSppGeometry &geometry);
    void draw(QPainter *painter, const QRect &rect, const QseSppGeometry &geometry);
signals:
    void changed();
private slots:
    void cursorDestroyed(QObject *obj);
private:
    QseCursor *m_cursor;
    qreal m_opacity;
    QPen m_pen;
};


const QPen &QseCursorPlot::pen() const
{
    return m_pen;
}

qreal QseCursorPlot::opacity() const
{
    return m_opacity;
}

#endif // QSECURSOR_H
