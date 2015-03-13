// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "qserange.h"


QseRange::QseRange(qint64 first, qint64 last)
{
    qRegisterMetaType<QseRange>("QseRange");

    setRange(first, last);
}

void QseRange::setRange(qint64 first, qint64 last)
{
    if (m_first != first || m_last != last)
    {
        if (first < 0 || last < 0)
        {
            m_first = m_last = -1;
        }
        else
        {
            if (last > first)
            {
                m_first = first;
                m_last = last;
            }
            else
            {
                m_first = last;
                m_last = first;
            }
        }
    }
}

void QseRange::reset()
{
    m_first = m_last = -1;
}

void QseRange::setFirst(qint64 first)
{
    if (m_last == -1)
        setRange(first, first);
    else
        setRange(first, m_last);
}

void QseRange::setLast(qint64 last)
{
    if (m_first == -1)
        setRange(last, last);
    else
        setRange(m_first, last);
}

QseRange QseRange::replaceFirst(qint64 first)
{
    return QseRange(first, m_last);
}

QseRange QseRange::replaceLast(qint64 last)
{
    return QseRange(m_first, last);
}

bool operator ==(const QseRange &l, const QseRange &r)
{
    return (l.first() == r.first()
            && l.last() == r.last());
}

bool operator !=(const QseRange &l, const QseRange &r)
{
    return (l.first() != r.first()
            || l.last() != r.last());
}