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
#include "qseabstractplot.h"


template<class Geometry>
QseAbstractPlot<Geometry>::QseAbstractPlot(QObject *parent) :
    QObject(parent)
{
}

/*! This method set flag isUpdateOnce() to true, and emit changed()
 */
template<class Geometry>
void QseAbstractPlot<Geometry>::setUpdateOnce(bool need)
{
    if (m_updateOnce)
        return;

    m_updateOnce = need;
    if (m_updateOnce)
        emit changed();
}

/*! This method used for reset the cached values of the plotter,
 *  we should realize it in the children class
 */
template<class Geometry>
void QseAbstractPlot<Geometry>::reset()
{
}

template<class Geometry>
bool QseAbstractPlot<Geometry>::isVisible(const QRect &, const Geometry &)
{
    return true;
}

template<class Geometry>
bool QseAbstractPlot<Geometry>::hasChanges(const QRect &, const Geometry &)
{
    return false;
}

template<class Geometry>
void QseAbstractPlot<Geometry>::draw(QPainter *, const QRect &, const Geometry &)
{
    m_updateOnce = false;
}
