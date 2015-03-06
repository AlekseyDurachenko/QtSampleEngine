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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef QSESPPGEOMETRY_H
#define QSESPPGEOMETRY_H

#include <QtGlobal>
#include <QMetaType>


// this class provide the widget geometry. In the any plotter.
// The 'x' coordinate is widget offset from the 0 (zero) position to
// the start of the visible widget. if samplePerPixel < 0 then
// x equal the sample offset.
// The 'y' is offset in the unit. If y == 0, then center line
// in the center of the widget.
// The 'samplePerPixel' is the x axis scale factor. If samplePerPixe. > 0, then
// we suppouse the samplePerPixel is count of sample per pixel. Otherwise, when
// samplePerPixel < 0, we suppouse the samplePerPixel is pixel count per sample.
// the correct values of the 'samplePerPixel' is [-oo, -1] and [2, +oo]
// 0, 1 is ambiguous and will be replaset in the set method (see the notes)
// The 'height' is ount of unit per widget height.
//
// Note: because the same value of the 'samplePerPixel' can be ambiguous, we
// introduce the axiom, if 'samplePerPixel' == 0, then samplePerPixel = 2,
// because most likely the previouse value -1, and we try to increase it.
// if 'samplePerPixel' == 1, then samplePerPixel = -1,
// because most likely the previouse value 2, and we try to decrease it.
class QseSppGeometry
{
public:
    QseSppGeometry(qint64 x = 0, double y = 0, qint64 samplePerPixel = -1, double height = 2.0);

    inline qint64 x() const;
    void setX(qint64 x);

    inline double y() const;
    void setY(double y);

    inline qint64 samplePerPixel() const;
    void setSamplePerPixel(qint64 samplePerPixel);

    inline double height() const;
    void setHeight(double height);

    QseSppGeometry addX(qint64 x) const;

    double toAbsoluteSamplePerPixel(double factor = 1.0) const;
    double toAbsoluteSampleOffset(double factor = 1.0) const;

    bool isSampleVisible(qint64 sampleIndex, int width) const;
    int toWidgetOffset(qint64 sampleIndex) const;
    qint64 toSampleIndex(int widgetOffset) const;

    friend bool operator == (const QseSppGeometry &left, const QseSppGeometry &right);
    friend bool operator != (const QseSppGeometry &left, const QseSppGeometry &right);
private:
    qint64 m_x, m_samplePerPixel;
    double m_y, m_height;
};
Q_DECLARE_METATYPE(QseSppGeometry)

qint64 QseSppGeometry::x() const
{
    return m_x;
}

double QseSppGeometry::y() const
{
    return m_y;
}

qint64 QseSppGeometry::samplePerPixel() const
{
    return m_samplePerPixel;
}

double QseSppGeometry::height() const
{
    return m_height;
}


#endif // QSESPPGEOMETRY_H
