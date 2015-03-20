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
#include "qsesppstandardselectioncontroller.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include "qsesppgeometry.h"
#include "qseselection.h"


QseSppStandardSelectionController::QseSppStandardSelectionController(QObject *parent) :
    QseAbstractSppStandardController(parent)
{
    m_selection = 0;
    m_dragAction = false;
}

void QseSppStandardSelectionController::setSelection(QseSelection *selection)
{
    m_selection = selection;
}

void QseSppStandardSelectionController::mouseMoveEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_selection
            && m_dragAction
            && event->buttons() == mouseButtons()
            && event->modifiers() == keyboardModifiers())
    {
        qint64 sample = QseSppGeometry::calcSampleIndex(geometry, event->x());
        m_selection->setSelectedRange(QseRange(m_otherDragSample, sample));
    }

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), geometry);
}

void QseSppStandardSelectionController::mousePressEvent(QMouseEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (m_selection
            && event->button() == Qt::LeftButton
            && event->modifiers() == Qt::ShiftModifier)
    {
        qint64 sample = QseSppGeometry::calcSampleIndex(geometry, event->x());

//        // when selection is exists, we extend it to the current cursor position
//        if (!m_selection->isNull())
//        {
//            QseRange range = m_selection->selectedRange();

//            if (sample > range.last())
//                m_selection->setSelectedRange(range.replaceLast(sample));
//            else if (sample < range.first())
//                m_selection->setSelectedRange(range.replaceFirst(sample));
//            // when we in the selection range, we set left() of right()
//            // bound of the selection, wich more closely to the cursor
//            else if (range.last()-sample < sample-range.first())
//                m_selection->setSelectedRange(QseRange(range.first(), sample));
//            else
//                m_selection->setSelectedRange(QseRange(sample, range.last()));
//        }

        if (!m_dragAction)
        {
            if (m_selection->isNull())
                m_selection->resetSelectedRange();

            m_dragAction = true;
            m_otherDragSample = sample;
            m_selection->setSelectedRange(QseRange(sample, sample));
        }
    }

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), geometry);
}

void QseSppStandardSelectionController::mouseReleaseEvent(QMouseEvent *event,
        const QRect &rect, const QseSppGeometry &geometry)
{
    if (event->buttons() != mouseButtons())
        m_dragAction = false;

    m_lastCursorPosition = event->pos();
    updateCursor(event->modifiers(), event->x(), geometry);
}

void QseSppStandardSelectionController::keyPressEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    if (event->modifiers() != keyboardModifiers())
        m_dragAction = false;

    updateCursor(event->modifiers(), m_lastCursorPosition.x(), geometry);
}

void QseSppStandardSelectionController::keyReleaseEvent(QKeyEvent *event,
        const QRect &/*rect*/, const QseSppGeometry &geometry)
{
    updateCursor(event->modifiers(), m_lastCursorPosition.x(), geometry);
}

void QseSppStandardSelectionController::updateCursor(Qt::KeyboardModifiers km,
        int x, const QseSppGeometry &geometry)
{
    if (!m_selection)
    {
        emit cursorChanged(defaultCursor());
    }
}
