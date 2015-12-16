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
#include "qseaudacitycontroller.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include "qseselection.h"
#include "qseposition.h"
#include "qsegeometry.h"


QseAudacityController::QseAudacityController(QObject *parent)
    : QseAbstractController(parent)
{
    m_position = 0;
    m_selection = 0;
    m_isSelectionAction = false;
    setDefaultCursor(QCursor(Qt::IBeamCursor));
}

void QseAudacityController::setPosition(QsePosition *position)
{
    if (position == m_position)
        return;

    if (m_position)
        disconnect(m_position, 0, this, 0);

    m_position = position;
    if (m_position) {
        connect(m_position, SIGNAL(destroyed()),
                this, SLOT(position_destroyed()));
    }
}

void QseAudacityController::setSelection(QseSelection *selection)
{
    if (selection == m_selection)
        return;

    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    m_selection = selection;
    if (m_selection) {
        connect(m_selection, SIGNAL(destroyed()),
                this, SLOT(selection_destroyed()));
    }
}

void QseAudacityController::mouseMoveEvent(QMouseEvent *event,
                                           const QRect &rect,
                                           const QseGeometry &geometry)
{
    if (event->buttons() & Qt::LeftButton) {
        changeSelection(event, geometry);
    }

    updateCursor(event->x(), rect, geometry);
}

void QseAudacityController::mousePressEvent(QMouseEvent *event,
                                            const QRect &rect,
                                            const QseGeometry &geometry)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        extendSelection(event, geometry);
        startSelection(event, rect, geometry);
    }
    else if (event->modifiers() & Qt::ControlModifier) {
        if (event->buttons() & Qt::LeftButton) {
            clickPlayPosition(event, geometry);
        }
    }
    else {
        if (event->buttons() & Qt::LeftButton) {
            startSelection(event, rect, geometry);
        }
    }

    updateCursor(event->x(), rect, geometry);
}

void QseAudacityController::mouseReleaseEvent(QMouseEvent *event,
                                              const QRect &rect,
                                              const QseGeometry &geometry)
{
    if (!(event->buttons() & Qt::LeftButton)) {
        endSelection();
    }

    updateCursor(event->x(), rect, geometry);
}

void QseAudacityController::wheelEvent(QWheelEvent *event,
                                       const QRect &rect,
                                       const QseGeometry &geometry)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        horizontalScroll(event, geometry);
    }
    else if (event->modifiers() & Qt::ControlModifier) {
        horizontalZoom(event, geometry);
    }

    updateCursor(event->x(), rect, geometry);
}

void QseAudacityController::position_destroyed()
{
    m_position = 0;
}

void QseAudacityController::selection_destroyed()
{
    m_selection = 0;
}

void QseAudacityController::startSelection(QMouseEvent *event,
                                           const QRect &rect,
                                           const QseGeometry &geometry)
{
    qint64 sample = QseGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    if (m_selection) {
        // resize selection if mouse around the selection bounds
        if (!m_selection->isNull()) {
            const QseRange range = m_selection->selectedRange();
            // left bound of selection
            if (QseGeometry::isSampleVisible(geometry, range.first(), rect.width())) {
                const int pos = QseGeometry::calcOffset(geometry, range.first());
                if (qAbs(pos - event->x()) < 5) {
                    m_isSelectionAction = true;
                    m_otherSample = range.last();
                    m_selection->setSelectedRange(range.replaceFirst(sample));
                }
            }
            // right bound of selection
            if (!m_isSelectionAction
                    && QseGeometry::isSampleVisible(geometry, range.last(), rect.width())) {
                const int pos = QseGeometry::calcOffset(geometry, range.last());
                if (qAbs(pos - event->x()) < 5) {
                    m_isSelectionAction = true;
                    m_otherSample = range.first();
                    m_selection->setSelectedRange(range.replaceLast(sample));
                }
            }
        }

        // start new selection if mouse away the selection bounds
        if (!m_isSelectionAction) {
            m_isSelectionAction = true;
            m_otherSample = sample;
            m_selection->resetSelectedRange();
            m_selection->setSelectedRange(QseRange(sample, sample));
        }
    }

    // change the current position if selection not found
    if (m_position && (!m_selection || m_selection->isNull()))
        m_position->setIndex(sample);
}

void QseAudacityController::extendSelection(QMouseEvent *event,
                                            const QseGeometry &geometry)
{
    if (!m_selection || m_selection->isNull())
        return;

    qint64 sample = QseGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    const QseRange range = m_selection->selectedRange();
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

void QseAudacityController::changeSelection(QMouseEvent *event,
                                            const QseGeometry &geometry)
{
    if (!m_isSelectionAction)
        return;

    qint64 sample = QseGeometry::calcSampleIndex(geometry, event->x());
    if (sample < 0)
        sample = 0;

    m_selection->setSelectedRange(QseRange(m_otherSample, sample));
    if (m_position && !m_selection->isNull())
        m_position->resetIndex();
}

void QseAudacityController::endSelection()
{
    m_isSelectionAction = false;
}

void QseAudacityController::clickPlayPosition(QMouseEvent *event,
                                              const QseGeometry &geometry)
{
    emit playClicked(QseGeometry::calcSampleIndex(geometry, event->x()));
}

void QseAudacityController::horizontalZoom(QWheelEvent *event,
                                           const QseGeometry &geometry)
{
    // calculate zoom
    int degree = event->delta() / 60;
    qint64 spp = geometry.spp();
    // zoom in
    if (degree > 0) {
        if (spp > 0)
            spp /= qAbs(degree);
        else
            spp *= qAbs(degree);
        if (spp == 0 || spp == 1)
            spp = -1;
    }
    // zoom out
    else if (degree < 0) {
        if (spp > 0)
            spp *= qAbs(degree);
        else
            spp /= qAbs(degree);
        if (spp == 0 || spp == 1)
            spp = 2;
    }

    QseGeometry result = geometry.replaceSpp(spp);
    qint64 sampleA = QseGeometry::calcSampleIndex(geometry, event->x());
    qint64 sampleB = QseGeometry::calcSampleIndex(result, event->x());
    qint64 x = geometry.x() + (sampleA - sampleB);

    // optimization: for exclude recalculation the peaks for zoom out
    if (result.spp() > 0)
        if (x % result.spp() != 0)
            x -= x % result.spp();

    emit geometryChanged(result.replaceX(x));
}

void QseAudacityController::horizontalScroll(QWheelEvent *event,
                                             const QseGeometry &geometry)
{
    int stepWidth = event->delta() / 4;
    qint64 spp = geometry.spp();
    if (spp > 0)
        stepWidth *= spp;

    emit geometryChanged(geometry.addX(-stepWidth));
}

void QseAudacityController::updateCursor(int x,
                                         const QRect &rect,
                                         const QseGeometry &geometry)
{
    if (m_selection && !m_selection->isNull()) {
        QseRange range = m_selection->selectedRange();
        // left bound of selection
        if (QseGeometry::isSampleVisible(geometry, range.first(), rect.width())) {
            int pos = QseGeometry::calcOffset(geometry, range.first());
            if (qAbs(pos - x) < 5) {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
        // right bound of selection
        if (QseGeometry::isSampleVisible(geometry, range.last(), rect.width())) {
            int pos = QseGeometry::calcOffset(geometry, range.last());
            if (qAbs(pos - x) < 5) {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
    }

    emit cursorChanged(defaultCursor());
}
