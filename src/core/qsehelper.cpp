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
#include "qsehelper.h"

// ----------------------------------------------------------------------
namespace Qse {
// ----------------------------------------------------------------------


/*! \brief The calculator of intersection
*
*   \param p11x the first x coordinate of line No1
*   \param p11y the first y coordinate of line No1
*   \param p12x the last x coordinate of line No1
*   \param p12y the last y coordinate of line No1
*   \param p21x the first x coordinate of line No2
*   \param p21y the first y coordinate of line No2
*   \param p22x the last x coordinate of line No2
*   \param p22y the last y coordinate of line No2
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
void calcIntersection(const double& p11x, const double& p11y,
        const double& p12x, const double& p12y,
        const double& p21x, const double& p21y,
        const double& p22x, const double& p22y,
        double& x, double& y)
{
    double Z  = (p12y-p11y)*(p21x-p22x)-(p21y-p22y)*(p12x-p11x);
    double Cb = (p21y-p11y)*(p21x-p22x)-(p21y-p22y)*(p21x-p11x);

    double Ub = Cb/Z;

    x = p11x + (p12x - p11x) * Ub;
    y = p11y + (p12y - p11y) * Ub;
}


// ----------------------------------------------------------------------
} // namespace Qse
// ----------------------------------------------------------------------
