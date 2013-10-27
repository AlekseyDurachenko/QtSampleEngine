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
#include "qsefunc.h"


bool QseFunc::isSampleVisible(qint64 sample, qint64 x, qint64 samplePerPixel, int width)
{
    if (samplePerPixel > 0)
        return (x*samplePerPixel <= sample) && (sample < (x+width)*samplePerPixel);
    else
        return (x <= sample) && (sample < x + width / qAbs(samplePerPixel));
}

int QseFunc::mapSampleToWidget(qint64 sample, qint64 x, qint64 samplePerPixel)
{
    if (samplePerPixel > 0)
        return (sample - x*samplePerPixel) / samplePerPixel;
    else
        return (sample - x) * qAbs(samplePerPixel);
}

qint64 QseFunc::mapWidgetToSample(int n, qint64 plotX, qint64 samplePerPixel)
{
    if (samplePerPixel > 0)
        return (plotX + n) * samplePerPixel;
    else
        return plotX + qRound(static_cast<qreal>(n) / qAbs(samplePerPixel));
}

qint64 QseFunc::width(qint64 samplePerPixel, qint64 frames)
{
    if (samplePerPixel < 0)
        return frames;
    else
        return frames / qAbs(samplePerPixel) + ((frames % qAbs(samplePerPixel)) ? 1 : 0);
}


/*! \brief The calculator of intersection
*
*   \param p11x the first coordinate of line No1
*   \param p11y the first coordinate of line No1
*   \param p12x the last coordinate of line No1
*   \param p12y the last coordinate of line No1
*   \param p21x the first coordinate of line No2
*   \param p21y the first coordinate of line No2
*   \param p22x the last coordinate of line No2
*   \param p22y the last coordinate of line No2
*   \retval x coordinate of intersection
*   \retval y coordinate of intersection
*   \code
*            (p21x,p21y)*
*                       |
*          (p11x,p11y)  |(x,y)
*               *-------+-------*
*                       |  (p12x,p12y)
*                       |
*                       *(p22x,p22y)
*   \endcode
*/
void QseFunc::findLineIntersection(const double& p11x, const double& p11y, const double& p12x, const double& p12y,
    const double& p21x, const double& p21y, const double& p22x, const double& p22y, double& x, double& y)
{
    double Z  = (p12y-p11y)*(p21x-p22x)-(p21y-p22y)*(p12x-p11x);
    double Cb = (p21y-p11y)*(p21x-p22x)-(p21y-p22y)*(p21x-p11x);

    double Ub = Cb/Z;

    x = p11x + (p12x - p11x) * Ub;
    y = p11y + (p12y - p11y) * Ub;
}
