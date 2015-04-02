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
#include "qsepeakarray.h"
#include <QDebug>


QsePeakArray::QsePeakArray(const QVector<double> &minimums,
        const QVector<double> &maximums)
{
    qRegisterMetaType<QsePeakArray>("QsePeakArray");

    if (!maximums.isEmpty())
        Q_ASSERT_X((maximums.count() == minimums.count()), "compare",
                   "count of minimums must be equal to count of maximums");

    m_minimums = minimums;
    m_maximums = maximums;
}

bool operator ==(const QsePeakArray &l, const QsePeakArray &r)
{
    return (l.minimums() == r.minimums()
            && l.maximums() == r.maximums());
}


bool operator !=(const QsePeakArray &l, const QsePeakArray &r)
{
    return (l.minimums() != r.minimums()
            || l.maximums() != r.maximums());
}

QsePeakArray operator +(const QsePeakArray &a, const QsePeakArray &b)
{
    const int count = a.count() + b.count();
    QVector<double> minimums(count);
    QVector<double> maximums(count);

    for (int i = 0; i < a.count(); ++i)
    {
        minimums[i] = a.minimums().at(i);
        maximums[i] = a.maximums().at(i);
    }
    for (int i = 0; i < b.count(); ++i)
    {
        minimums[a.count()+i] = b.minimums().at(i);
        maximums[a.count()+i] = b.maximums().at(i);
    }

    return QsePeakArray(minimums, maximums);
}

QDebug operator<<(QDebug dbg, const QsePeakArray &peaks)
{
    if (peaks.isEmpty())
    {
        dbg.nospace() << "QsePeakArray()";
    }
    else if (!peaks.hasMaximums())
    {
        dbg.nospace() << "QsePeakArray(";
        for (int i = 0; i < peaks.count(); ++i)
        {
            dbg.nospace() << peaks.minimums().at(i);
            if (i < peaks.count()-1)
                dbg.nospace() << ", ";
        }
        dbg.nospace() << ")";
    }
    else
    {
        dbg.nospace() << "QsePeakArray(";
        for (int i = 0; i < peaks.count(); ++i)
        {
            dbg.nospace() << "(";
            dbg.nospace() << peaks.minimums().at(i);
            dbg.nospace() << ", ";
            dbg.nospace() << peaks.maximums().at(i);
            dbg.nospace() << ")";
            if (i < peaks.count()-1)
                dbg.nospace() << ", ";
        }
        dbg.nospace() << ")";
    }

    return dbg.space();
}

