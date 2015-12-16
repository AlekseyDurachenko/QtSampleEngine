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
#include "qsegeometry.h"
#include <QDebug>


QseGeometry::QseGeometry(qint64 x,
                         double y,
                         qint64 spp,
                         double height)
{
    qRegisterMetaType<QseGeometry>("QseGeometry");

    m_x = x;
    m_y = y;
    m_height = height;
    setSpp(spp);
}

void QseGeometry::setX(qint64 x)
{
    m_x = x;
}

void QseGeometry::setY(double y)
{
    m_y = y;
}

void QseGeometry::setSpp(qint64 spp)
{
    if (spp == 1) {
        m_spp = -1;
    }
    else if (spp == 0) {
        m_spp = 2;
    }
    else {
        m_spp = spp;
    }
}

void QseGeometry::setHeight(double height)
{
    m_height = height;
}

QseGeometry QseGeometry::addX(qint64 x) const
{
    return replaceX(m_x + x);
}

QseGeometry QseGeometry::addY(double y) const
{
    return replaceY(m_y + y);
}

QseGeometry QseGeometry::addSpp(qint64 spp) const
{
    return replaceSpp(m_spp + spp);
}

QseGeometry QseGeometry::addHeight(double height) const
{
    return replaceHeight(m_height + height);
}

QseGeometry QseGeometry::replaceX(qint64 x) const
{
    return QseGeometry(x, m_y, m_spp, m_height);
}

QseGeometry QseGeometry::replaceY(double y) const
{
    return QseGeometry(m_x, y, m_spp, m_height);
}

QseGeometry QseGeometry::replaceSpp(qint64 spp) const
{
    return QseGeometry(m_x, m_y, spp, m_height);
}

QseGeometry QseGeometry::replaceHeight(double height) const
{
    return QseGeometry(m_x, m_y, m_spp, height);
}

double QseGeometry::toRealSpp() const
{
    if (m_spp > 0)
        return m_spp;
    else
        return 1.0 / (-m_spp);
}

bool QseGeometry::isSampleVisible(const QseGeometry &geometry,
                                  qint64 sampleIndex,
                                  qint64 width)
{
    const qint64 x = geometry.x();
    const qint64 spp = geometry.spp();

    if (spp > 0) {
        return ((x <= sampleIndex) && (sampleIndex < x + (width * spp)));
    }
    else {
        return ((x <= sampleIndex)
                && (sampleIndex < x + (width / -spp) + ((width % (-spp)) ? (1) : (0))));
    }
}

qint64 QseGeometry::calcOffset(const QseGeometry &geometry, qint64 sampleIndex)
{
    const qint64 x = geometry.x();
    const qint64 spp = geometry.spp();

    if (spp > 0)
        return (sampleIndex - x) / spp;
    else
        return (sampleIndex - x) * (-spp);
}

qint64 QseGeometry::widthFromSamples(const QseGeometry &geometry, qint64 count)
{
    const qint64 spp = geometry.spp();

    if (spp > 0)
        return count / spp + ((count % spp) ? (1) : (0));
    else
        return count * (-spp);
}

qint64 QseGeometry::samplesFromWidth(const QseGeometry &geometry, qint64 width)
{
    const qint64 spp = geometry.spp();

    if (spp > 0)
        return width * spp;
    else
        return width / (-spp) + ((width % (-spp)) ? (1) : (0));
}

qint64 QseGeometry::calcSampleIndex(const QseGeometry &geometry, qint64 offset)
{
    const qint64 x = geometry.x();
    const qint64 spp = geometry.spp();

    if (spp > 0)
        return (x + (offset * spp));
    else
        return (x + qRound64(static_cast<double>(offset) / (-spp)));
}

QDebug operator <<(QDebug dbg, const QseGeometry &geometry)
{
    dbg.nospace() << "QseGeometry({";
    dbg.nospace() << "X: " << geometry.x() << ", ";
    dbg.nospace() << "Y: " << geometry.y() << ", ";
    dbg.nospace() << "Spp: " << geometry.spp() << ", ";
    dbg.nospace() << "Height: " << geometry.height();
    dbg.nospace() << "})";
    return dbg.space();
}
