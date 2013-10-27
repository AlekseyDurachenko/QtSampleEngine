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
#include "qsecursor.h"

QseCursor::QseCursor(QObject *parent) :
    QObject(parent)
{
    m_maximum = m_index = -1;
}

void QseCursor::setIndex(qint64 index)
{
    if (index < -1)
        index = -1;
    else if (index > m_maximum)
        index = m_maximum;

    if (m_index != index)
    {
        m_index = index;
        emit changed();
    }
}

void QseCursor::reset()
{
    setIndex(-1);
}

void QseCursor::setMaximum(qint64 maximum)
{
    m_maximum = maximum;
    setIndex(m_index);
}
