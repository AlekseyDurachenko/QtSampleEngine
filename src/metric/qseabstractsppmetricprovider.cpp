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
#include "qseabstractsppmetricprovider.h"

/*!\fn QseAbstractMetricProvider::create()
 *
 * \brief create creates the metric points
 *
 * \param offset the offset from the corrdinate 0 (zero) in units
 * \param unitPerPixel the coefficient wich shows how many
 *        units placed at the one pixel
 * \param minStep the minimum step between main (level 1) metrics
 * \param size the width/height of the widget
 */


QseAbstractSppMetricProvider::QseAbstractSppMetricProvider(QObject *parent)
    : QseAbstractMetricProvider(parent)
{
}
