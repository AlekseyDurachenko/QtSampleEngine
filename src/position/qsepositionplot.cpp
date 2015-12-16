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
#include "qsepositionplot.h"
#include <QPainter>
#include "qseposition.h"


QsePositionPlot::QsePositionPlot(QObject *parent)
    : QseAbstractPlot(parent)
{
    m_position = 0;
    m_opacity = 1.0;
    m_pen = QPen(QColor(Qt::black));
}

void QsePositionPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity) {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QsePositionPlot::setPosition(QsePosition *position)
{
    if (!isEnabled()) {
        return;
    }

    if (m_position == position) {
        return;
    }

    if (m_position) {
        disconnect(m_position, 0, this, 0);
    }

    m_position = position;
    if (m_position) {
        connect(m_position, SIGNAL(indexChanged()),
                this, SLOT(setUpdateOnce()));
        connect(m_position, SIGNAL(destroyed(QObject *)),
                this, SLOT(position_destroyed()));
    }

    setUpdateOnce(true);
}

bool QsePositionPlot::hasChanges(const QRect &rect,
                                 const QseGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

void QsePositionPlot::setPen(const QPen &pen)
{
    if (m_pen != pen) {
        m_pen = pen;
        setUpdateOnce(true);
    }
}


bool QsePositionPlot::isVisible(const QRect &rect,
                                const QseGeometry &geometry)
{
    if (m_position == 0) {
        return false;
    }

    if (m_position->isNull()) {
        return false;
    }

    return QseGeometry::isSampleVisible(geometry,
                                        m_position->index(),
                                        rect.width());
}

void QsePositionPlot::draw(QPainter *painter,
                           const QRect &rect,
                           const QseGeometry &geometry)
{
    if (isVisible(rect, geometry)) {
        int pos = QseGeometry::calcOffset(geometry, m_position->index());
        painter->save();
        painter->setPen(m_pen);
        painter->setOpacity(m_opacity);
        painter->drawLine(pos, 0, pos, rect.height());
        painter->restore();
    }

    QseAbstractPlot::draw(painter, rect, geometry);
}

void QsePositionPlot::position_destroyed()
{
    m_position = 0;
}
