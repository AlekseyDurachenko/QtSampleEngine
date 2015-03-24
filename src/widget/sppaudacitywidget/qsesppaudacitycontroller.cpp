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
#include "qsesppaudacitycontroller.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include "qseselection.h"
#include "qsecursor.h"
#include "qsesppgeometry.h"


QseSppAudacityController::QseSppAudacityController(QObject *parent) :
    QseAbstractSppController(parent)
{
    m_currentPosition = 0;
    m_selection = 0;
    m_isSelectionAction = false;
    setDefaultCursor(QCursor(Qt::IBeamCursor));
}

void QseSppAudacityController::setCurrentPosition(QseCursor *cursor)
{
    if (cursor == m_currentPosition)
        return;

    if (m_currentPosition)
        disconnect(m_currentPosition, 0, this, 0);

    m_currentPosition = cursor;
    if (m_currentPosition)
    {
        connect(m_currentPosition, SIGNAL(destroyed()),
                this, SLOT(currentPosition_destroyed()));
    }
}

void QseSppAudacityController::setSelection(QseSelection *selection)
{
    if (selection == m_selection)
        return;

    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    m_selection = selection;
    if (m_selection)
    {
        connect(m_selection, SIGNAL(destroyed()),
                this, SLOT(selection_destroyed()));
    }
}

void QseSppAudacityController::mouseMoveEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (event->buttons() & Qt::LeftButton)
    {
        changeSelection(event, geometry);
    }

    updateCursor(event->x(), rect, geometry);
}

void QseSppAudacityController::mousePressEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (event->modifiers() & Qt::ShiftModifier)
    {
        extendSelection(event, geometry);
        startSelection(event, rect, geometry);
    }
    else if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            clickPlayPosition(event, geometry);
        }
    }
    else
    {
        if (event->buttons() & Qt::LeftButton)
        {
            changeCurrentPosition(event, geometry);
            startSelection(event, rect, geometry);
        }
    }

    updateCursor(event->x(), rect, geometry);
}

void QseSppAudacityController::mouseReleaseEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        endSelection();
    }

    updateCursor(event->x(), rect, geometry);
}

void QseSppAudacityController::wheelEvent(QWheelEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (event->modifiers() & Qt::ShiftModifier)
    {
        horizontalScroll(event, geometry);
    }
    else if (event->modifiers() & Qt::ControlModifier)
    {
        horizontalZoom(event, geometry);
    }

    updateCursor(event->x(), rect, geometry);
}

void QseSppAudacityController::currentPosition_destroyed()
{
    m_currentPosition = 0;
}

void QseSppAudacityController::selection_destroyed()
{
    m_selection = 0;
}

void QseSppAudacityController::startSelection(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (!m_selection)
        return;

    qint64 sample = QseSppGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    // resize selection if mouse around the selection bounds
    if (!m_selection->isNull())
    {
        QseRange range = m_selection->selectedRange();
        // left bound of selection
        if (QseSppGeometry::checkSampleIndexVisibility(geometry,
                range.first(), rect.width()))
        {
            int pos = QseSppGeometry::calcOffset(geometry, range.first());
            if (qAbs(pos - event->x()) < 5)
            {
                m_isSelectionAction = true;
                m_otherSample = range.last();
                m_selection->setSelectedRange(range.replaceFirst(sample));
            }
        }
        // right bound of selection
        if (!m_isSelectionAction
                && QseSppGeometry::checkSampleIndexVisibility(geometry,
                        range.last(), rect.width()))
        {
            int pos = QseSppGeometry::calcOffset(geometry, range.last());
            if (qAbs(pos - event->x()) < 5)
            {
                m_isSelectionAction = true;
                m_otherSample = range.first();
                m_selection->setSelectedRange(range.replaceLast(sample));
            }
        }
    }

    // start new selection if mouse away the selection bounds
    if (!m_isSelectionAction)
    {
        m_isSelectionAction = true;
        m_otherSample = sample;
        m_selection->resetSelectedRange();
        m_selection->setSelectedRange(QseRange(sample, sample));
    }
}

void QseSppAudacityController::extendSelection(QMouseEvent *event,
        const QseSppGeometry &geometry)
{
    if (!m_selection || m_selection->isNull())
        return;

    qint64 sample = QseSppGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    QseRange range = m_selection->selectedRange();
    if (sample > range.last())
        m_selection->setSelectedRange(range.replaceLast(sample));
    else if (sample < range.first())
        m_selection->setSelectedRange(range.replaceFirst(sample));
    // when we in the selection range, we set first() of right()
    // bound of the selection, wich more closely to the cursor
    else if (range.first() - sample < sample - range.last())
        m_selection->setSelectedRange(range.replaceLast(sample));
    else
        m_selection->setSelectedRange(range.replaceFirst(sample));
}

void QseSppAudacityController::changeSelection(QMouseEvent *event,
        const QseSppGeometry &geometry)
{
    if (!m_isSelectionAction)
        return;

    qint64 sample = QseSppGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    m_selection->setSelectedRange(QseRange(m_otherSample, sample));
    if (m_currentPosition && !m_selection->isNull())
        m_currentPosition->resetIndex();
}

void QseSppAudacityController::endSelection()
{
    m_isSelectionAction = false;
}

void QseSppAudacityController::changeCurrentPosition(QMouseEvent *event,
        const QseSppGeometry &geometry)
{
    if (!m_currentPosition || !m_selection->isNull())
        return;

    m_currentPosition->setIndex(
            QseSppGeometry::calcSampleIndex(geometry, event->x()));
}

void QseSppAudacityController::clickPlayPosition(QMouseEvent *event,
        const QseSppGeometry &geometry)
{
    emit playClicked(QseSppGeometry::calcSampleIndex(geometry, event->x()));
}

void QseSppAudacityController::horizontalZoom(QWheelEvent *event,
        const QseSppGeometry &geometry)
{
    // calculate zoom
    int degree = event->delta() / 60;
    qint64 spp = geometry.samplesPerPixel();
    // zoom in
    if (degree > 0)
    {
        if (spp > 0)
            spp /= qAbs(degree);
        else
            spp *= qAbs(degree);
        if (spp == 0 || spp == 1)
            spp = -1;
    }
    // zoom out
    else if (degree < 0)
    {
        if (spp > 0)
            spp *= qAbs(degree);
        else
            spp /= qAbs(degree);
        if (spp == 0 || spp == 1)
            spp = 2;
    }

    QseSppGeometry result = geometry.replaceSamplesPerPixel(spp);
    qint64 sampleA = QseSppGeometry::calcSampleIndex(geometry, event->x());
    qint64 sampleB = QseSppGeometry::calcSampleIndex(result, event->x());
    qint64 x = geometry.x() + (sampleA - sampleB);

    emit geometryChanged(result.replaceX(x));
}

void QseSppAudacityController::horizontalScroll(QWheelEvent *event,
        const QseSppGeometry &geometry)
{
    int stepWidth = event->delta() / 4;
    qint64 spp = geometry.samplesPerPixel();
    if (spp > 0)
        stepWidth *= spp;

    emit geometryChanged(geometry.addX(-stepWidth));
}

void QseSppAudacityController::updateCursor(int x, const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_selection && !m_selection->isNull())
    {
        QseRange range = m_selection->selectedRange();
        // left bound of selection
        if (QseSppGeometry::checkSampleIndexVisibility(geometry, range.first(),
                rect.width()))
        {
            int pos = QseSppGeometry::calcOffset(geometry, range.first());
            if (qAbs(pos - x) < 5)
            {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
        // right bound of selection
        if (QseSppGeometry::checkSampleIndexVisibility(geometry, range.last(),
                rect.width()))
        {
            int pos = QseSppGeometry::calcOffset(geometry, range.last());
            if (qAbs(pos - x) < 5)
            {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
    }

    emit cursorChanged(defaultCursor());
}
