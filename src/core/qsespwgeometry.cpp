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
#include "qsespwgeometry.h"


QseSpwGeometry::QseSpwGeometry(qint64 x, double y, qint64 samplesPerWindow,
        double height)
{
    m_x = x;
    m_y = y;
    if (samplesPerWindow > 0)
        m_samplesPerWindow = samplesPerWindow;
    else
        m_samplesPerWindow = 1;
    m_height = height;
}

void QseSpwGeometry::setX(qint64 x)
{
    m_x = x;
}

void QseSpwGeometry::setY(double y)
{
    m_y = y;
}

void QseSpwGeometry::setSamplesPerWindow(qint64 samplesPerWindow)
{
    if (samplesPerWindow > 0)
        m_samplesPerWindow = samplesPerWindow;
    else
        m_samplesPerWindow = 1;
}

void QseSpwGeometry::setHeight(double height)
{
    m_height = height;
}

QseSpwGeometry QseSpwGeometry::addX(qint64 x) const
{
    return replaceX(this->x() + x);
}

QseSpwGeometry QseSpwGeometry::addY(double y) const
{
    return replaceY(this->y() + y);
}

QseSpwGeometry QseSpwGeometry::addSamplesPerWindow(qint64 samplesPerWindow) const
{
    return replaceSamplesPerWindow(this->samplesPerWindow() + samplesPerWindow);
}

QseSpwGeometry QseSpwGeometry::addHeight(double height) const
{
    return replaceHeight(this->height() + height);
}

QseSpwGeometry QseSpwGeometry::replaceX(qint64 x) const
{
    return QseSpwGeometry(x, y(), samplesPerWindow(), height());
}

QseSpwGeometry QseSpwGeometry::replaceY(double y) const
{
    return QseSpwGeometry(x(), y, samplesPerWindow(), height());
}

QseSpwGeometry QseSpwGeometry::replaceSamplesPerWindow(
        qint64 samplesPerWindow) const
{
    return QseSpwGeometry(x(), y(), samplesPerWindow, height());
}

QseSpwGeometry QseSpwGeometry::replaceHeight(double height) const
{
    return QseSpwGeometry(x(), y(), samplesPerWindow(), height);
}

bool operator ==(const QseSpwGeometry &l, const QseSpwGeometry &r)
{
    return (l.x() == r.x()
            && l.y() == r.y()
            && l.samplesPerWindow() == r.samplesPerWindow()
            && l.height() == r.height());
}

bool operator !=(const QseSpwGeometry &l, const QseSpwGeometry &r)
{
    return (l.x() != r.x()
            || l.y() != r.y()
            || l.samplesPerWindow() != r.samplesPerWindow()
            || l.height() != r.height());
}
