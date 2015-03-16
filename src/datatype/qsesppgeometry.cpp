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
#include "qsesppgeometry.h"
#include <QDebug>


QseSppGeometry::QseSppGeometry(qint64 x, double y, qint64 samplePerPixel,
        double height)
{
    qRegisterMetaType<QseSppGeometry>("QseSppGeometry");

    m_x = x;
    m_y = y;
    m_height = height;
    setSamplesPerPixel(samplePerPixel);
}

void QseSppGeometry::setX(qint64 x)
{
    m_x = x;
}

void QseSppGeometry::setY(double y)
{
    m_y = y;
}

void QseSppGeometry::setSamplesPerPixel(qint64 samplePerPixel)
{
    if (samplePerPixel == 1)
        m_samplesPerPixel = -1;
    else if (samplePerPixel == 0)
        m_samplesPerPixel = 2;
    else
        m_samplesPerPixel = samplePerPixel;
}

void QseSppGeometry::setHeight(double height)
{
    m_height = height;
}

QseSppGeometry QseSppGeometry::addX(qint64 x) const
{
    return replaceX(m_x + x);
}

QseSppGeometry QseSppGeometry::addY(double y) const
{
    return replaceY(m_y + y);
}

QseSppGeometry QseSppGeometry::addSamplesPerPixel(qint64 samplesPerPixel) const
{
    return replaceSamplesPerPixel(m_samplesPerPixel + samplesPerPixel);
}

QseSppGeometry QseSppGeometry::addHeight(double height) const
{
    return replaceHeight(m_height + height);
}

QseSppGeometry QseSppGeometry::replaceX(qint64 x) const
{
    return QseSppGeometry(x, m_y, m_samplesPerPixel, m_height);
}

QseSppGeometry QseSppGeometry::replaceY(double y) const
{
    return QseSppGeometry(m_x, y, m_samplesPerPixel, m_height);
}

QseSppGeometry QseSppGeometry::replaceSamplesPerPixel(
        qint64 samplesPerPixel) const
{
    return QseSppGeometry(m_x, m_y, samplesPerPixel, m_height);
}

QseSppGeometry QseSppGeometry::replaceHeight(double height) const
{
    return QseSppGeometry(m_x, m_y, m_samplesPerPixel, height);
}

double QseSppGeometry::toRealSamplesPerPixel() const
{
    if (m_samplesPerPixel > 0)
        return m_samplesPerPixel;
    else
        return 1.0 / (-m_samplesPerPixel);
}

bool operator ==(const QseSppGeometry &l, const QseSppGeometry &r)
{
    return (l.x() == r.x()
            && l.y() == r.y()
            && l.samplesPerPixel() == r.samplesPerPixel()
            && l.height() == r.height());
}

bool operator !=(const QseSppGeometry &l, const QseSppGeometry &r)
{
    return (l.x() != r.x()
            || l.y() != r.y()
            || l.samplesPerPixel() != r.samplesPerPixel()
            || l.height() != r.height());
}

bool QseSppGeometry::checkSampleIndexVisibility(const QseSppGeometry &geometry,
        qint64 sampleIndex, int width)
{
    const qint64 &x = geometry.x();
    const qint64 &spp = geometry.samplesPerPixel();

    if (spp > 0)
        return (x <= sampleIndex) && (sampleIndex < x+(width*spp));
    else
        return (x <= sampleIndex) && (sampleIndex < x-(width/spp));
}

int QseSppGeometry::calcOffset(const QseSppGeometry &geometry,
        qint64 sampleIndex)
{
    const qint64 &x = geometry.x();
    const qint64 &spp = geometry.samplesPerPixel();

    if (spp > 0)
        return (sampleIndex - x) / spp;
    else
        return (sampleIndex - x) * (-spp);
}

qint64 QseSppGeometry::calcSampleIndex(const QseSppGeometry &geometry,
        int offset)
{
    const qint64 &x = geometry.x();
    const qint64 &spp = geometry.samplesPerPixel();

    if (spp > 0)
        return x + (offset * spp);
    else
        return x + qRound(static_cast<double>(offset) / (-spp));
}


QDebug operator<<(QDebug dbg, const QseSppGeometry &geometry)
{
    dbg.nospace() << "QseSppGeometry({";
    dbg.nospace() << "X: " << geometry.x() << ", ";
    dbg.nospace() << "Y: " << geometry.y() << ", ";
    dbg.nospace() << "SamplePerPixel: " << geometry.samplesPerPixel() << ", ";
    dbg.nospace() << "Height: " << geometry.height();
    dbg.nospace() << "})";
    return dbg.space();
}
