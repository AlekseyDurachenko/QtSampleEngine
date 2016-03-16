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
#include "qsestandardselectioncontroller.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include "qsegeometry.h"
#include "qseselection.h"


QseStandardSelectionController::QseStandardSelectionController(QObject *parent)
    : QseAbstractStandardController(parent)
{
    m_selection = 0;
    m_dragAction = false;
}

void QseStandardSelectionController::setSelection(QseSelection *selection)
{
    if (m_selection == selection)
        return;

    if (m_selection)
        disconnect(m_selection, 0, this, 0);

    m_selection = selection;
    if (m_selection) {
        connect(m_selection, SIGNAL(destroyed()),
                this, SLOT(selection_destroyed()));
    }
}

void QseStandardSelectionController::mouseMoveEvent(QMouseEvent *event,
                                                    const QRect &rect,
                                                    const QseGeometry &geometry)
{
    if (m_selection
            && m_dragAction
            && event->buttons() == mouseButtons()
            && event->modifiers() == keyboardModifiers()) {
        const qint64 sample = QseGeometry::calcSampleIndex(geometry, event->x());
        m_selection->setSelectedRange(QseRange(m_otherDragSample, sample));
    }

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), rect, geometry);
}

void QseStandardSelectionController::mousePressEvent(QMouseEvent *event,
                                                     const QRect &rect,
                                                     const QseGeometry &geometry)
{
    if (m_selection
            && event->button() == mouseButtons()
            && event->modifiers() == keyboardModifiers()) {
        const qint64 sample = QseGeometry::calcSampleIndex(geometry, event->x());

        // resize selection if mouse around the selection bounds
        if (!m_selection->isNull()) {
            const QseRange range = m_selection->selectedRange();
            // left bound of selection
            if (QseGeometry::isSampleVisible(geometry, range.first(), rect.width())) {
                const int pos = QseGeometry::calcOffset(geometry, range.first());
                if (qAbs(pos - event->x()) < 5) {
                    m_dragAction = true;
                    m_otherDragSample = range.last();
                    m_selection->setSelectedRange(range.replaceFirst(sample));
                }
            }
            // right bound of selection
            if (!m_dragAction
                    && QseGeometry::isSampleVisible(geometry, range.last(), rect.width())) {
                const int pos = QseGeometry::calcOffset(geometry, range.last());
                if (qAbs(pos - event->x()) < 5) {
                    m_dragAction = true;
                    m_otherDragSample = range.first();
                    m_selection->setSelectedRange(range.replaceLast(sample));
                }
            }
        }

        // start new selection if mouse away the selection bounds
        if (!m_dragAction) {
            if (m_selection->isNull())
                m_selection->resetSelectedRange();

            m_dragAction = true;
            m_otherDragSample = sample;
            m_selection->setSelectedRange(QseRange(sample, sample));
        }
    }

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), rect, geometry);
}

void QseStandardSelectionController::mouseReleaseEvent(QMouseEvent *event,
                                                       const QRect &rect,
                                                       const QseGeometry &geometry)
{
    if (event->buttons() != mouseButtons())
        m_dragAction = false;

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), rect, geometry);
}

void QseStandardSelectionController::keyPressEvent(QKeyEvent *event,
                                                   const QRect &rect,
                                                   const QseGeometry &geometry)
{
    if (event->modifiers() != keyboardModifiers())
        m_dragAction = false;

    updateCursor(event->modifiers(), m_lastCursorPosition.x(), rect, geometry);
}

void QseStandardSelectionController::keyReleaseEvent(QKeyEvent *event,
                                                     const QRect &rect,
                                                     const QseGeometry &geometry)
{
    if (event->modifiers() != keyboardModifiers())
        m_dragAction = false;

    updateCursor(event->modifiers(), m_lastCursorPosition.x(), rect, geometry);
}

void QseStandardSelectionController::updateCursor(Qt::KeyboardModifiers km,
                                                  int x,
                                                  const QRect &rect,
                                                  const QseGeometry &geometry)
{
    if (!m_selection || km != keyboardModifiers()) {
        emit cursorChanged(defaultCursor());
        return;
    }

    if (m_dragAction) {
        emit cursorChanged(QCursor(Qt::SizeHorCursor));
        return;
    }

    // show the resize cursor if mouse around the selection bounds
    if (!m_selection->isNull()) {
        const QseRange range = m_selection->selectedRange();
        // left bound of selection
        if (QseGeometry::isSampleVisible(geometry, range.first(), rect.width())) {
            const int pos = QseGeometry::calcOffset(geometry, range.first());
            if (qAbs(pos - x) < 5) {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
        // right bound of selection
        if (QseGeometry::isSampleVisible(geometry, range.last(), rect.width())) {
            const int pos = QseGeometry::calcOffset(geometry, range.last());
            if (qAbs(pos - x) < 5) {
                emit cursorChanged(QCursor(Qt::SizeHorCursor));
                return;
            }
        }
    }

    emit cursorChanged(defaultCursor());
}

void QseStandardSelectionController::selection_destroyed()
{
    m_selection = 0;
}
