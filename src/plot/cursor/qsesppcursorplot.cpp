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
#include "qsesppcursorplot.h"
#include <QPainter>
#include "qsecursor.h"


QseSppCursorPlot::QseSppCursorPlot(QObject *parent) :
    QseAbstractSppPlot(parent)
{
    m_cursor = 0;
    m_opacity = 1.0;
    m_pen = QPen(QColor(Qt::black));
}

void QseSppCursorPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSppCursorPlot::setCursor(QseCursor *cursor)
{
    if (m_cursor)
        disconnect(m_cursor, 0, this, 0);

    m_cursor = cursor;
    if (m_cursor)
    {
        connect(m_cursor, SIGNAL(indexChanged()), this, SLOT(setUpdateOnce()));
        connect(m_cursor, SIGNAL(destroyed(QObject*)),
                this, SLOT(cursor_destroyed(QObject*)));
    }

    setUpdateOnce(true);
}

bool QseSppCursorPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    Q_UNUSED(rect);
    Q_UNUSED(geometry);

    // TODO: check full state
    return true;
}

void QseSppCursorPlot::setPen(const QPen &pen)
{
    if (m_pen != pen)
    {
        m_pen = pen;
        setUpdateOnce(true);
    }
}


bool QseSppCursorPlot::isVisible(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_cursor == 0)
        return false;

    if (m_cursor->isNull())
        return false;

    return QseSppGeometry::checkSampleIndexVisibility(
                geometry, m_cursor->index(), rect.width());
}

void QseSppCursorPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        int pos = QseSppGeometry::calcOffset(geometry, m_cursor->index());
        painter->setPen(m_pen);
        painter->setOpacity(m_opacity);
        painter->drawLine(pos, 0, pos, rect.height());
    }

    QseAbstractSppPlot::draw(painter, rect, geometry);
}

void QseSppCursorPlot::cursor_destroyed(QObject *obj)
{
    if (obj == m_cursor)
        m_cursor = 0;
}
