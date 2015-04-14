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
#include "qsemetricmapper.h"


QseMetricMapper::QseMetricMapper()
{
    init();
}

void QseMetricMapper::init()
{
    m_relativeLessOne.reserve(DBL_MAX_10_EXP);
    m_relativeMoreOne.reserve(DBL_MAX_10_EXP-1);

    double valueLess = 0.1;
    for (int pow = 1; pow <= DBL_MAX_10_EXP; ++pow)
    {
        m_relativeLessOne.push_back(valueLess * 5);
        m_relativeLessOne.push_back(valueLess * 2);
        m_relativeLessOne.push_back(valueLess);
        valueLess *= 0.1;
    }

    double valueMore = 1.0;
    for (int pow = 1; pow < DBL_MAX_10_EXP; ++pow)
    {
        m_relativeMoreOne.push_back(valueMore);
        m_relativeMoreOne.push_back(valueMore * 2);
        m_relativeMoreOne.push_back(valueMore * 5);
        valueMore *= 10.0;
    }
}

double QseMetricMapper::calcNearestValue(double unitPerPixel, double minimum)
{
    const double approxIntervalMetric = minimum * unitPerPixel;

    // TODO: binary search or something like are required
    if (approxIntervalMetric > 0.5)
    {
        for (int i = 0; i < m_relativeMoreOne.count(); ++i)
            if (m_relativeMoreOne[i] >= approxIntervalMetric)
                return m_relativeMoreOne[i];
    }
    else
    {
        double k = m_relativeLessOne[0];
        for (int i = 1; i < m_relativeMoreOne.count(); ++i)
        {
            if (m_relativeLessOne[i] < approxIntervalMetric)
                return k;
            k = m_relativeLessOne[i];
        }
    }

    return approxIntervalMetric;
}
