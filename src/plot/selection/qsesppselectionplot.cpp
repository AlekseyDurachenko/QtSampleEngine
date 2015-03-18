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
#include "qsesppselectionplot.h"
#include <QPainter>
#include "qseselection.h"


QseSppSelectionPlot::QseSppSelectionPlot(QObject *parent)
    : QseAbstractSppPlot(parent)
{
    m_brush = Qt::blue;
    m_opacity = 0.5;
    m_selection = 0;
}

void QseSppSelectionPlot::setBrush(const QBrush &brush)
{
    if (m_brush != brush)
    {
        m_brush = brush;
        setUpdateOnce(true);
    }
}

void QseSppSelectionPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        setUpdateOnce(true);
    }
}

void QseSppSelectionPlot::setSelection(QseSelection *selection)
{
    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    m_selection = selection;
    if (m_selection)
    {
        connect(m_selection, SIGNAL(selectionChanged()),
                this, SLOT(setUpdateOnce()));
        connect(m_selection, SIGNAL(destroyed(QObject*)),
                this, SLOT(selection_destroyed(QObject*)));
    }

    setUpdateOnce(true);
}

bool QseSppSelectionPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    return (isUpdateOnce() || rect != lastRect() || geometry != lastGeometry());
}

bool QseSppSelectionPlot::isVisible(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_selection == 0)
        return false;

    if (m_selection->isNull())
        return false;

    // TODO: fix algorithm, because it can cause the overflow
    int sl = QseSppGeometry::calcOffset(geometry,
                m_selection->selectedRange().first());
    int sr = QseSppGeometry::calcOffset(geometry,
                m_selection->selectedRange().last());

    if ((sl < 0 && sr < 0) || (sl >= rect.width() && sr >= rect.width()))
        return false;

    return true;
}

void QseSppSelectionPlot::draw(QPainter *painter, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (isVisible(rect, geometry))
    {
        // TODO: fix algorithm, because it can cause the overflow
        int sl = QseSppGeometry::calcOffset(geometry,
                    m_selection->selectedRange().first());
        int sr = QseSppGeometry::calcOffset(geometry,
                    m_selection->selectedRange().last());

        if (sl < 0)
            sl = 0;
        if (sr >= rect.width())
            sr = rect.width()-1;

        painter->save();
        painter->setOpacity(m_opacity);
        painter->fillRect(sl, 0, sr-sl+1, rect.height(), m_brush);
        painter->restore();
    }

    QseAbstractSppPlot::draw(painter, rect, geometry);
}

void QseSppSelectionPlot::selection_destroyed(QObject *obj)
{
    if (obj == m_selection)
        m_selection = 0;
}
