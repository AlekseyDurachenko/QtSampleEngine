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
#ifndef QSESPPPEAKREQUEST_H
#define QSESPPPEAKREQUEST_H

#include <QtGlobal>
#include <QRect>
#include "qsesppgeometry.h"

class QseSppPeakRequest
{
public:
    QseSppPeakRequest();
    QseSppPeakRequest(const QseSppGeometry &geometry, const QRect &rect,
                      bool rightAlign = false);
    QseSppPeakRequest(qint64 x, qint64 spp, int width, bool rightAlign = false);

    inline const qint64 &x() const;
    void setX(qint64 x);

    inline const qint64 &spp() const;
    void setSpp(qint64 spp);

    inline const int &width() const;
    void setWidth(int width);

    inline const bool &rightAlign() const;
    void setRightAlign(bool rightAlign);
private:
    qint64 m_x;
    qint64 m_spp;
    int m_width;
    bool m_rightAlign;
};

bool operator ==(const QseSppPeakRequest &l, const QseSppPeakRequest &r);
bool operator !=(const QseSppPeakRequest &l, const QseSppPeakRequest &r);

const qint64 &QseSppPeakRequest::x() const
{
    return m_x;
}

const qint64 &QseSppPeakRequest::spp() const
{
    return m_spp;
}

const int &QseSppPeakRequest::width() const
{
    return m_width;
}

const bool &QseSppPeakRequest::rightAlign() const
{
    return m_rightAlign;
}


#endif // QSESPPPEAKREQUEST_H
