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
#include "qseselectionplot.h"
#include <QPainter>
#include "qseselection.h"


QseSelectionPlot::QseSelectionPlot(QObject *parent)
    : QseAbstractPlot(parent)
{
    m_brush = Qt::blue;
    m_opacity = 0.5;
    m_selection = 0;
}

void QseSelectionPlot::setBrush(const QBrush &brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        setUpdateOnce(true);
    }
}

void QseSelectionPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity) {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSelectionPlot::setSelection(QseSelection *selection)
{
    if (m_selection == selection)
        return;

    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    m_selection = selection;
    if (m_selection) {
        connect(m_selection, SIGNAL(selectionChanged()),
                this, SLOT(setUpdateOnce()));
        connect(m_selection, SIGNAL(destroyed(QObject *)),
                this, SLOT(selection_destroyed(QObject *)));
    }

    setUpdateOnce(true);
}

bool QseSelectionPlot::hasChanges(const QRect &rect,
                                  const QseGeometry &geometry)
{
    return (isUpdateOnce()
            || rect != lastRect()
            || geometry != lastGeometry());
}

bool QseSelectionPlot::isVisible(const QRect &rect,
                                 const QseGeometry &geometry)
{
    if (!isEnabled())
        return false;

    if (m_selection == 0)
        return false;

    if (m_selection->isNull())
        return false;

    const qint64 firstVisibleSample = geometry.x();
    const qint64 lastVisibleSample = firstVisibleSample + QseGeometry::samplesFromWidth(geometry, rect.width());

    if (m_selection->selectedRange().first() >= lastVisibleSample)
        return false;

    if (m_selection->selectedRange().last() <= firstVisibleSample)
        return false;

    return true;
}

void QseSelectionPlot::draw(QPainter *painter,
                            const QRect &rect,
                            const QseGeometry &geometry)
{
    if (isVisible(rect, geometry)) {
        const qint64 firstVisibleSample = geometry.x();
        const qint64 lastVisibleSample = QseGeometry::calcSampleIndex(geometry, rect.width());

        int sl = 0;
        if (m_selection->selectedRange().first() > firstVisibleSample)
            sl = QseGeometry::calcOffset(geometry, m_selection->selectedRange().first());

        int sr = rect.width() - 1;
        if (m_selection->selectedRange().last() <= lastVisibleSample)
            sr = QseGeometry::calcOffset(geometry, m_selection->selectedRange().last());

        painter->save();
        painter->setOpacity(m_opacity);
        painter->fillRect(sl, 0, sr - sl + 1, rect.height(), m_brush);
        painter->restore();
    }

    QseAbstractPlot::draw(painter, rect, geometry);
}

void QseSelectionPlot::selection_destroyed(QObject *obj)
{
    if (obj == m_selection)
        m_selection = 0;
}
