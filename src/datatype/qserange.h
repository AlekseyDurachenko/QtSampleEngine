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
#ifndef QSERANGE_H
#define QSERANGE_H

#include <QtGlobal>
#include <QMetaType>


class QseRange
{
public:
    QseRange();
    QseRange(qint64 first, qint64 last);

    inline bool isNull() const;
    inline qint64 count() const;

    void setRange(qint64 first, qint64 last);
    void reset();

    inline qint64 first() const;
    void setFirst(qint64 first);

    inline qint64 last() const;
    void setLast(qint64 last);

    QseRange replaceFirst(qint64 first) const;
    QseRange replaceLast(qint64 last) const;

    friend inline bool operator ==(const QseRange &l, const QseRange &r);
    friend inline bool operator !=(const QseRange &l, const QseRange &r);
    friend QDebug operator <<(QDebug dbg, const QseRange &range);

private:
    bool m_isNull;
    qint64 m_first;
    qint64 m_last;
};
Q_DECLARE_METATYPE(QseRange)


inline bool QseRange::isNull() const
{
    return m_isNull;
}

inline qint64 QseRange::count() const
{
    return m_last - m_first;
}

inline qint64 QseRange::first() const
{
    return m_first;
}

inline qint64 QseRange::last() const
{
    return m_last;
}

inline bool operator ==(const QseRange &l, const QseRange &r)
{
    return (l.m_first == r.m_first
            && l.m_last == r.m_last
            && l.m_isNull == r.m_isNull);
}

inline bool operator !=(const QseRange &l, const QseRange &r)
{
    return (l.m_first != r.m_first
            || l.m_last != r.m_last
            || l.m_isNull != r.m_isNull);
}


#endif // QSERANGE_H
