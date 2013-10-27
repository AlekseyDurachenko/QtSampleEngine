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
#include "qsecursorplot.h"
#include "qsefunc.h"


QseCursorPlot::QseCursorPlot(QObject *parent) :
    QseAbstractPlot(parent)
{
    m_pen.setColor(Qt::black);
    m_opacity = 1.0;
    m_cursor = 0;
}

void QseCursorPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        emit changed();
    }
}

void QseCursorPlot::setCursor(QseCursor *cursor)
{
    if (m_cursor)
        disconnect(m_cursor, 0, this, 0);

    if (cursor)
    {
        connect(cursor, SIGNAL(changed()), this, SIGNAL(changed()));
        connect(cursor, SIGNAL(destroyed(QObject*)), this, SLOT(cursorDestroyed(QObject*)));
    }

    m_cursor = cursor;
}

void QseCursorPlot::setPen(const QPen &pen)
{
    if (m_pen != pen)
    {
        m_pen = pen;
        emit changed();
    }
}


bool QseCursorPlot::isVisible(const QRect &rect, const QseGeometry &geometry)
{
    if (m_cursor)
        return (!m_cursor->isNull() &&
                QseFunc::isSampleVisible(m_cursor->index(), geometry.x(), geometry.samplePerPixel(), rect.width()));
    else
        return false;
}

void QseCursorPlot::draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry)
{
    if (m_cursor && !m_cursor->isNull() &&
            QseFunc::isSampleVisible(m_cursor->index(), geometry.x(), geometry.samplePerPixel(), rect.width()))
    {
        int wpos = QseFunc::mapSampleToWidget(m_cursor->index(), geometry.x(), geometry.samplePerPixel());

        painter->setPen(m_pen);
        painter->setOpacity(m_opacity);
        painter->drawLine(wpos, 0, wpos, rect.height());
    }
}


void QseCursorPlot::cursorDestroyed(QObject *obj)
{
    if (obj == m_cursor)
        m_cursor = 0;
}
