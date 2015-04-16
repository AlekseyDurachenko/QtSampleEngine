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
#include "qsespppeakrequest.h"


QseSppPeakRequest::QseSppPeakRequest()
{
    m_x = 0;
    m_spp = 0;
    m_width = 0;
    m_rightAlign = false;
}

QseSppPeakRequest::QseSppPeakRequest(const QseSppGeometry &geometry,
        const QRect &rect, bool rightAlign)
{
    m_x = geometry.x();
    m_spp = geometry.samplesPerPixel();
    m_width = rect.width();
    m_rightAlign = rightAlign;
}

QseSppPeakRequest::QseSppPeakRequest(qint64 x, qint64 spp, int width,
        bool rightAlign)
{
    m_x = x;
    m_spp = spp;
    m_width = width;
    m_rightAlign = rightAlign;
}

void QseSppPeakRequest::setX(qint64 x)
{
    m_x = x;
}

void QseSppPeakRequest::setSpp(qint64 spp)
{
    m_spp = spp;
}

void QseSppPeakRequest::setWidth(int width)
{
    m_width = width;
}

void QseSppPeakRequest::setRightAlign(bool rightAlign)
{
    m_rightAlign  = rightAlign;
}
