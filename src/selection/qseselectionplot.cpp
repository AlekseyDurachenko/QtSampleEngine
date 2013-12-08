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
#include "qseselectionplot.h"
#include "qsefunc.h"


QseSelectionPlot::QseSelectionPlot(QObject *parent)
    : QseAbstractPlot(parent)
{
    m_brush = Qt::blue;
    m_opacity = 0.5;
    m_selection = 0;
}

void QseSelectionPlot::setBrush(const QBrush &brush)
{
    if (m_brush != brush)
    {
        m_brush = brush;
        emit changed();
    }
}

void QseSelectionPlot::setOpacity(qreal opacity)
{
    if (m_opacity != opacity)
    {
        m_opacity = opacity;
        emit changed();
    }
}

void QseSelectionPlot::setSelection(QseSelection *selection)
{
    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    if (selection)
    {
        connect(selection, SIGNAL(changed()), this, SIGNAL(changed()));
        connect(selection, SIGNAL(destroyed(QObject*)), this, SLOT(selectionDestroyed(QObject*)));
    }

    m_selection = selection;
}

bool QseSelectionPlot::isVisible(const QRect &rect, const QseGeometry &geometry)
{
    if (m_selection == 0)
        return false;

    if (m_selection->isNull())
        return false;

    qint64 sl = QseFunc::mapSampleToWidget(m_selection->left(), geometry.x(), geometry.samplePerPixel());
    qint64 sr = QseFunc::mapSampleToWidget(m_selection->right(), geometry.x(), geometry.samplePerPixel());

    if ((sl < 0 && sr < 0) || (sl >= rect.width() && sr >= rect.width()))
        return false;

    return true;
}

void QseSelectionPlot::draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry)
{
    if (m_selection && !m_selection->isNull())
    {
        qint64 sl = QseFunc::mapSampleToWidget(m_selection->left(), geometry.x(), geometry.samplePerPixel());
        qint64 sr = QseFunc::mapSampleToWidget(m_selection->right(), geometry.x(), geometry.samplePerPixel());

        if ((sl < 0 && sr < 0) || (sl >= rect.width() && sr >= rect.width()))
            return;

        if (sl < 0)
            sl = 0;
        if (sr > rect.width())
            sr = rect.width();

        painter->setOpacity(opacity());
        painter->fillRect(sl, 0, sr-sl+1, rect.height(), brush());
    }
}


void QseSelectionPlot::selectionDestroyed(QObject *obj)
{
    if (obj == m_selection)
        m_selection = 0;
}
