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
#include "qsecursor.h"


QseCursor::QseCursor(QObject *parent) : QObject(parent)
{
    m_index = -1;
}

void QseCursor::setAvailableRange(const QseRange &availableRange)
{
    if (availableRange != m_availableRange)
    {
        m_availableRange = availableRange;
        if (!isNull())
            setIndex(m_index);
    }
}

void QseCursor::setIndex(qint64 index)
{
    qint64 newIndex = index;
    if (m_availableRange.isNull())
        newIndex = -1;
    else if (newIndex < m_availableRange.first())
        newIndex = m_availableRange.first();
    else if (newIndex > m_availableRange.last())
        newIndex = m_availableRange.last();

    if (newIndex != m_index)
    {
        m_index = newIndex;
        emit indexChanged();
    }
}

void QseCursor::resetAvailableRange()
{
    setAvailableRange(QseRange());
}

/*! set index to null
 */
void QseCursor::resetIndex()
{
    if (m_index != -1)
    {
        m_index = -1;
        emit indexChanged();
    }
}
