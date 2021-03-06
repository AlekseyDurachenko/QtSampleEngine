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
#ifndef QSEMETRICITEM_H
#define QSEMETRICITEM_H


#include <QString>


class QseMetricItem
{
public:
    explicit QseMetricItem(int offset = -1, int level = 1, const QString &text = QString());

    inline bool isNull() const;

    inline int offset() const;
    void setOffset(int offset);

    inline int level() const;
    void setLevel(int level);

    inline const QString &text() const;
    void setText(const QString &text);

private:
    int m_offset;
    int m_level;
    QString m_text;
};

inline bool QseMetricItem::isNull() const
{
    return (m_offset < 0);
}

inline int QseMetricItem::offset() const
{
    return m_offset;
}

inline int QseMetricItem::level() const
{
    return m_level;
}

inline const QString &QseMetricItem::text() const
{
    return m_text;
}


#endif // QSEMETRICITEM_H
