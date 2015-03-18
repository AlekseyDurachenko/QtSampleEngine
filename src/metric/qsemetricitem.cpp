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
#include "qsemetricitem.h"


/*!\class QseMetricItem
 *
 * \brief The QseMetricItem class provides the information about one metric
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


QseMetricItem::QseMetricItem(int offset, int level, const QString &text)
{
    m_offset = offset;
    m_level = level;
    m_text = text;
}

void QseMetricItem::setOffset(int offset)
{
    m_offset = offset;
}

void QseMetricItem::setLevel(int level)
{
    m_level = level;
}

void QseMetricItem::setText(const QString &text)
{
    m_text = text;
}
