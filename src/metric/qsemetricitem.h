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
#ifndef QSEMETRICITEM_H
#define QSEMETRICITEM_H

#include <QString>


/*! \brief The QseMetricItem class provides the information about one metric
 *
 * \li offset - is offset as pixels from the 0 of coordinate system. if
 * offset less then -1 it means the item is incorrect otherwords it is null.
 *
 * \li level - indicate the line (metric) style. Usually "0" is center line
 * (gravity zero of the coordinate system), "1" is main corrdinate metrics.
 *
 * \li name - is the text wich associated with the metric (for example the
 * value of the amplitude or time or something else).
 */
class QseMetricItem
{
public:
    QseMetricItem(int offset = -1, int level = 1, const QString &text = QString());

    inline bool isNull() const;
    inline int offset() const;
    inline int level() const;
    inline const QString &text() const;

    inline void setOffset(int offset);
    inline void setLevel(int level);
    inline void setText(const QString &text);
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

inline void QseMetricItem::setOffset(int offset)
{
    m_offset = offset;
}

inline void QseMetricItem::setLevel(int level)
{
    m_level = level;
}

inline void QseMetricItem::setText(const QString &text)
{
    m_text = text;
}


#endif // QSEMETRICITEM_H
