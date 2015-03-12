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
#ifndef QSESPWGEOMETRY_H
#define QSESPWGEOMETRY_H

#include <QtGlobal>
#include <QMetaType>


class QseSpwGeometry
{
public:
    QseSpwGeometry(qint64 x = 0, double y = 0, qint64 samplesPerWindow = 1,
                   double height = 1.0);

    inline qint64 x() const;
    void setX(qint64 x);

    inline double y() const;
    void setY(double y);

    inline qint64 samplesPerWindow() const;
    void setSamplesPerWindow(qint64 samplesPerWindow);

    inline double height() const;
    void setHeight(double height);

    QseSpwGeometry addX(qint64 x) const;
    QseSpwGeometry addY(double y) const;
    QseSpwGeometry addSamplesPerWindow(qint64 samplesPerWindow) const;
    QseSpwGeometry addHeight(double height) const;

    QseSpwGeometry replaceX(qint64 x) const;
    QseSpwGeometry replaceY(double y) const;
    QseSpwGeometry replaceSamplesPerWindow(qint64 samplePerWindow) const;
    QseSpwGeometry replaceHeight(double height) const;
private:
    qint64 m_x;
    double m_y;
    qint64 m_samplesPerWindow;
    double m_height;
};
Q_DECLARE_METATYPE(QseSpwGeometry)

bool operator ==(const QseSpwGeometry &l, const QseSpwGeometry &r);
bool operator !=(const QseSpwGeometry &l, const QseSpwGeometry &r);

qint64 QseSpwGeometry::x() const
{
    return m_x;
}

double QseSpwGeometry::y() const
{
    return m_y;
}

qint64 QseSpwGeometry::samplesPerWindow() const
{
    return m_samplesPerWindow;
}

double QseSpwGeometry::height() const
{
    return m_height;
}


#endif // QSESPWGEOMETRY_H
