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
#include <QDebug>


QseRange::QseRange()
{
    qRegisterMetaType<QseRange>("QseRange");

    reset();
}

QseRange::QseRange(qint64 first, qint64 last)
{
    qRegisterMetaType<QseRange>("QseRange");

    setRange(first, last);
}

void QseRange::setRange(qint64 first, qint64 last)
{
    if (m_first != first || m_last != last)
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

    m_isNull = false;
}

void QseRange::reset()
{
    m_first = 0;
    m_last = 0;
    m_isNull = true;
}

void QseRange::setFirst(qint64 first)
{
    if (m_isNull)
        setRange(first, first);
    else
        setRange(first, m_last);
}

void QseRange::setLast(qint64 last)
{
    if (m_isNull)
        setRange(last, last);
    else
        setRange(m_first, last);
}

QseRange QseRange::replaceFirst(qint64 first)
{
    if (m_isNull)
        return QseRange(first, first);
    else
        return QseRange(first, m_last);
}

QseRange QseRange::replaceLast(qint64 last)
{
    if (m_isNull)
        return QseRange(last, last);
    else
        return QseRange(m_first, last);
}

bool operator ==(const QseRange &l, const QseRange &r)
{
    return (l.first() == r.first()
            && l.last() == r.last()
            && l.isNull() == r.isNull());
}

bool operator !=(const QseRange &l, const QseRange &r)
{
    return (l.first() != r.first()
            || l.last() != r.last()
            || l.isNull() != r.isNull());
}

QDebug operator<<(QDebug dbg, const QseRange &range)
{
    if (range.isNull())
        dbg.nospace() << "QseRange()";
    else
        dbg.nospace() << "QseRange([" << range.first() << ";" << range.last()
                      << "])";
    return dbg.space();
}
