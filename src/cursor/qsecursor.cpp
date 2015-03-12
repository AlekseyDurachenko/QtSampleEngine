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

void QseCursor::setAvailableRange(const QseRange &range)
{
    if (range != m_range)
    {
        m_range = range;
        setIndex(m_index);
    }
}

void QseCursor::setIndex(qint64 index)
{
    qint64 newIndex = index;
    if (newIndex < 0 || m_range.isNull())
        newIndex = -1;
    else if (newIndex < m_range.first())
        newIndex = m_range.first();
    else if (newIndex > m_range.last())
        newIndex = m_range.last();

    if (newIndex != m_index)
    {
        m_index = newIndex;
        emit changed();
    }
}

/*! set index to null
 */
void QseCursor::reset()
{
    if (m_index != -1)
    {
        m_index = -1;
        emit changed();
    }
}
