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
    qRegisterMetaType<QseSppPeakRequest>("QseSppPeakRequest");

    m_x = 0;
    m_samplePerPixel = 0;
    m_width = 0;
    m_rightAlign = false;
}

QseSppPeakRequest::QseSppPeakRequest(const QseSppGeometry &geometry,
                                     const QRect &rect,
                                     bool rightAlign)
{
    qRegisterMetaType<QseSppPeakRequest>("QseSppPeakRequest");

    m_x = geometry.x();
    m_samplePerPixel = geometry.samplesPerPixel();
    m_width = rect.width();
    m_rightAlign = rightAlign;
}

QseSppPeakRequest::QseSppPeakRequest(const QseSppGeometry &geometry,
                                     int width,
                                     bool rightAlign)
{
    qRegisterMetaType<QseSppPeakRequest>("QseSppPeakRequest");

    m_x = geometry.x();
    m_samplePerPixel = geometry.samplesPerPixel();
    m_width = width;
    m_rightAlign = rightAlign;
}

QseSppPeakRequest::QseSppPeakRequest(qint64 x,
                                     qint64 samplePerPixel,
                                     int width,
                                     bool rightAlign)
{
    qRegisterMetaType<QseSppPeakRequest>("QseSppPeakRequest");

    m_x = x;
    m_samplePerPixel = samplePerPixel;
    m_width = width;
    m_rightAlign = rightAlign;
}

void QseSppPeakRequest::setX(qint64 x)
{
    m_x = x;
}

void QseSppPeakRequest::setSamplePerPixel(qint64 samplePerPixel)
{
    m_samplePerPixel = samplePerPixel;
}

void QseSppPeakRequest::setWidth(int width)
{
    m_width = width;
}

void QseSppPeakRequest::setRightAlign(bool rightAlign)
{
    m_rightAlign  = rightAlign;
}


bool operator ==(const QseSppPeakRequest &l, const QseSppPeakRequest &r)
{
    return (l.x() == r.x()
            && l.samplePerPixel() == r.samplePerPixel()
            && l.width() == r.width()
            && l.rightAlign() == r.rightAlign());
}


bool operator !=(const QseSppPeakRequest &l, const QseSppPeakRequest &r)
{
    return (l.x() != r.x()
            || l.samplePerPixel() != r.samplePerPixel()
            || l.width() != r.width()
            || l.rightAlign() != r.rightAlign());
}
