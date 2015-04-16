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
#ifndef QSEPEAKARRAY_H
#define QSEPEAKARRAY_H

#include <QVector>
#include <QMetaType>


class QsePeakArray
{
public:
    QsePeakArray(const QVector<double> &minimums = QVector<double>(),
                 const QVector<double> &maximums = QVector<double>());

    inline bool isEmpty() const;
    inline bool hasMaximums() const;
    inline int count() const;
    inline const QVector<double> &minimums() const;
    inline const QVector<double> &maximums() const;

    void push_front(const QsePeakArray &peaks);
    void push_back(const QsePeakArray &peaks);

    void clear();
private:
    QVector<double> m_minimums;
    QVector<double> m_maximums;
};
Q_DECLARE_METATYPE(QsePeakArray)

bool operator ==(const QsePeakArray &l, const QsePeakArray &r);
bool operator !=(const QsePeakArray &l, const QsePeakArray &r);
QsePeakArray operator +(const QsePeakArray &a, const QsePeakArray &b);
QDebug operator<<(QDebug dbg, const QsePeakArray &peaks);

bool QsePeakArray::isEmpty() const
{
    return (m_maximums.isEmpty() && m_minimums.isEmpty());
}

bool QsePeakArray::hasMaximums() const
{
    return (!m_maximums.isEmpty());
}

int QsePeakArray::count() const
{
    return m_minimums.count();
}

const QVector<double> &QsePeakArray::minimums() const
{
    return m_minimums;
}

const QVector<double> &QsePeakArray::maximums() const
{
    return m_maximums;
}


#endif // QSEPEAKARRAY_H
