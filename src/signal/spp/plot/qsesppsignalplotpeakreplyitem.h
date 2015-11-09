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
#ifndef QSESPPSIGNALPLOTPEAKREPLYITEM_H
#define QSESPPSIGNALPLOTPEAKREPLYITEM_H


#include <QRect>
#include "qsesppgeometry.h"
class QseAbstractSppPeakReply;


class QseSppSignalPlotPeakReplyItem
{
public:
    enum PushType {
        PushBack    = 0x00,
        PushFront   = 0x01,
        ReplaceAll  = 0x02
    };

    QseSppSignalPlotPeakReplyItem(PushType type,
                                  QseAbstractSppPeakReply *reply,
                                  const QseSppGeometry &geometry,
                                  const QRect &rect);

    inline PushType pushType() const
    {
        return m_appendType;
    }

    inline QseAbstractSppPeakReply *reply() const
    {
        return m_reply;
    }

    inline const QseSppGeometry &geometry() const
    {
        return m_geometry;
    }

    inline const QRect &rect() const
    {
        return m_rect;
    }

private:
    PushType m_appendType;
    QseAbstractSppPeakReply *m_reply;
    QseSppGeometry m_geometry;
    QRect m_rect;
};


#endif // QSESPPSIGNALPLOTPEAKREPLYITEM_H
