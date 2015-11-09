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
#ifndef QSESPPSIGNALPLOTPEAKREPLYITEMLIST_H
#define QSESPPSIGNALPLOTPEAKREPLYITEMLIST_H


#include <QList>
#include "qsesppsignalplotpeakreplyitem.h"


class QseSppSignalPlotPeakReplyItemList
{
public:
    QseSppSignalPlotPeakReplyItemList();

    bool contains(QseAbstractSppPeakReply *reply) const;
    int indexOf(QseAbstractSppPeakReply *reply) const;
    inline const QseSppSignalPlotPeakReplyItem &at(int i) const;
    inline int count() const;

    void insert(const QseSppSignalPlotPeakReplyItem &item);
    void removeAt(int i);
    void clear();

private:
    QList<QseSppSignalPlotPeakReplyItem> m_items;
};

const QseSppSignalPlotPeakReplyItem &QseSppSignalPlotPeakReplyItemList::at(
        int i) const
{
    return m_items[i];
}

int QseSppSignalPlotPeakReplyItemList::count() const
{
    return m_items.count();
}


#endif // QSESPPSIGNALPLOTPEAKREPLYITEMLIST_H
