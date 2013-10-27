// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSEFUNC_H
#define QSEFUNC_H

#include <QtGlobal>
#include "qsegeometry.h"


class QseFunc
{
public:
    static bool isSampleVisible(qint64 sample, qint64 plotX, qint64 samplePerPixel, int width);
    static int mapSampleToWidget(qint64 sample, qint64 plotX, qint64 samplePerPixel);
    static qint64 mapWidgetToSample(int n, qint64 plotX, qint64 samplePerPixel);
    static qint64 width(qint64 samplePerPixel, qint64 frames);
    static void findLineIntersection(const double& p11x, const double& p11y, const double& p12x, const double& p12y,
        const double& p21x, const double& p21y, const double& p22x, const double& p22y, double& x, double& y);
};


#endif // QSEFUNC_H
