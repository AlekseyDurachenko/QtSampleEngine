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


QseSppGeometry::QseSppGeometry(qint64 x, double y, qint64 samplePerPixel, double height)
{
    qRegisterMetaType<QseSppGeometry>("QseSppGeometry");
    setX(x);
    setY(y);
    setSamplePerPixel(samplePerPixel);
    setHeight(height);
}

void QseSppGeometry::setX(qint64 x)
{
    m_x = x;
}

void QseSppGeometry::setY(double y)
{
    m_y = y;
}

void QseSppGeometry::setSamplePerPixel(qint64 samplePerPixel)
{
    if (samplePerPixel == 1)
        m_samplePerPixel = -1;
    else if (samplePerPixel == 0)
        m_samplePerPixel = 2;
    else
        m_samplePerPixel = samplePerPixel;
}

void QseSppGeometry::setHeight(double height)
{
    m_height = height;
}

QseSppGeometry QseSppGeometry::addX(qint64 x) const
{
    return QseSppGeometry(m_x+x, m_y, m_samplePerPixel, m_height);
}

double QseSppGeometry::toAbsoluteSamplePerPixel(double factor) const
{
    if (m_samplePerPixel > 0)
        return (m_samplePerPixel * factor);
    else
        return (1.0 / -m_samplePerPixel * factor);
}

double QseSppGeometry::toAbsoluteSampleOffset(double factor) const
{
    if (m_samplePerPixel > 0)
        return (m_x * factor * m_samplePerPixel);
    else
        return (m_x * factor);
}

bool QseSppGeometry::isSampleVisible(qint64 sampleIndex, int width) const
{
    if (m_samplePerPixel > 0)
        return (m_x*m_samplePerPixel <= sampleIndex)
                && (sampleIndex < (m_x+width)*m_samplePerPixel);
    else
        return (m_x <= sampleIndex)
                && (sampleIndex < m_x-width/m_samplePerPixel);
}

int QseSppGeometry::toWidgetOffset(qint64 sampleIndex) const
{
    if (m_samplePerPixel > 0)
        return (sampleIndex - m_x*m_samplePerPixel) / m_samplePerPixel;
    else
        return (sampleIndex - m_x) * qAbs(m_samplePerPixel);
}

qint64 QseSppGeometry::toSampleIndex(int widgetOffset) const
{
    if (m_samplePerPixel > 0)
        return (m_x + widgetOffset) * m_samplePerPixel;
    else
        return m_x + qRound(static_cast<qreal>(widgetOffset) / qAbs(m_samplePerPixel));
}

bool operator == (const QseSppGeometry &left, const QseSppGeometry &right)
{
    return left.x() == right.x()
        && left.y() == right.y()
        && left.samplePerPixel() == right.samplePerPixel()
        && left.height() == right.height();
}

bool operator != (const QseSppGeometry &left, const QseSppGeometry &right)
{
    return left.x() != right.x()
        || left.y() != right.y()
        || left.samplePerPixel() != right.samplePerPixel()
        || left.height() != right.height();
}