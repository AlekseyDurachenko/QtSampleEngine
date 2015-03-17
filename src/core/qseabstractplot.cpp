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


QseAbstractPlot::QseAbstractPlot(QObject *parent) : QObject(parent)
{
    m_updateOnce = true;
}

/*! This method set flag isUpdateOnce() to true, and emit changed()
 */
void QseAbstractPlot::setUpdateOnce(bool need)
{
    if (m_updateOnce == need)
        return;

    m_updateOnce = need;
    if (m_updateOnce)
        emit updateNeeded();
}

/*! This method used for reset the cached values of the plotter,
 *  we should realize it in the children class
 */
void QseAbstractPlot::reset()
{
}
