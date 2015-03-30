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
#ifndef QSEABSTRACTSPPSIGNALPLOT_H
#define QSEABSTRACTSPPSIGNALPLOT_H

#include <QPen>
#include "qsesppgeometry.h"
#include "qseabstractsppplot.h"


class QseAbstractSppSignalPlot : public QseAbstractSppPlot
{
    Q_OBJECT
    Q_ENUMS(ZeroLine)
    Q_PROPERTY(ZeroLine zeroLine READ zeroLine WRITE setZeroLine)
public:
    enum ZeroLine
    {
        Top     = 0x01,
        Middle  = 0x02,
        Bottom  = 0x03
    };

    explicit QseAbstractSppSignalPlot(QObject *parent = 0);

    inline ZeroLine zeroLine() const;
    void setZeroLine(ZeroLine zeroLine);
protected:
    inline int calcDy(const QRect &rect);
private:
    ZeroLine m_zeroLine;
};

QseAbstractSppSignalPlot::ZeroLine QseAbstractSppSignalPlot::zeroLine() const
{
    return m_zeroLine;
}

int QseAbstractSppSignalPlot::calcDy(const QRect &rect)
{
    switch (zeroLine())
    {
    case Top:
        return 0;
    case Middle:
        return rect.height()/2.0;
    case Bottom:
        return rect.height();
    }

    return rect.height()/2.0;
}


#endif // QSEABSTRACTSPPSIGNALPLOT_H
