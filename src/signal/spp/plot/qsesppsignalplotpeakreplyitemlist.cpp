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
#include "qsesppsignalplotpeakreplyitemlist.h"


QseSppSignalPlotPeakReplyItemList::QseSppSignalPlotPeakReplyItemList()
{
}

bool QseSppSignalPlotPeakReplyItemList::contains(
        QseAbstractSppPeakReply *reply) const
{
    for (int i = 0; i < m_items.count(); ++i)
        if (m_items[i].reply() == reply)
            return true;
    return false;
}

int QseSppSignalPlotPeakReplyItemList::indexOf(
        QseAbstractSppPeakReply *reply) const
{
    for (int i = 0; i < m_items.count(); ++i)
        if (m_items[i].reply() == reply)
            return i;
    return -1;
}

void QseSppSignalPlotPeakReplyItemList::insert(
        const QseSppSignalPlotPeakReplyItem &item)
{
    m_items.push_back(item);
}

void QseSppSignalPlotPeakReplyItemList::removeAt(int i)
{
    m_items.removeAt(i);
}

void QseSppSignalPlotPeakReplyItemList::clear()
{
    m_items.clear();
}
