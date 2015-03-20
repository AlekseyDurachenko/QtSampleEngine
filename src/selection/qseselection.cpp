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
#include "qseselection.h"


QseSelection::QseSelection(QObject *parent) : QObject(parent)
{
}

void QseSelection::setAvailableRange(const QseRange &availableRange)
{
    if (availableRange != m_availableRange)
    {
        m_availableRange = availableRange;
        setSelectedRange(m_selectedRange);
    }
}

void QseSelection::setSelectedRange(const QseRange &selectedRange)
{
    QseRange newSelectedRange = selectedRange;
    if (newSelectedRange.isNull() || m_availableRange.isNull())
    {
        newSelectedRange.reset();
    }
    else
    {
        if ((newSelectedRange.first() > m_availableRange.last()
                && newSelectedRange.last() > m_availableRange.last())
                || (newSelectedRange.first() < m_availableRange.first()
                    && newSelectedRange.last() < m_availableRange.first()))
        {
            newSelectedRange.reset();
        }
        else
        {
            if (newSelectedRange.first() < m_availableRange.first())
                newSelectedRange.setFirst(m_availableRange.first());
            if (newSelectedRange.last() > m_availableRange.last())
                newSelectedRange.setLast(m_availableRange.last());
        }
    }

    if (newSelectedRange != m_selectedRange)
    {
        m_selectedRange = newSelectedRange;
        emit selectionChanged();
    }
}

void QseSelection::resetAvailableRange()
{
    setAvailableRange(QseRange());
}

void QseSelection::resetSelectedRange()
{
    setSelectedRange(QseRange());
}
