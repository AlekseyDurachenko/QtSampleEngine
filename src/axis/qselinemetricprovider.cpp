// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "qselinemetricprovider.h"
#include <QDebug>

QseLineMetricProvider::QseLineMetricProvider(Orientation orientation,
    QObject *parent) : QseAbstractMetricProvider(parent)
{
    m_mapper = new QseMetricMapper();
    m_orientation = orientation;
    m_coeff = 1.0;
}

QseLineMetricProvider::~QseLineMetricProvider()
{
    delete m_mapper;
}

int QseLineMetricProvider::maximumTextLenght() const
{
    return 8;
}

QList<QseMetricItem> QseLineMetricProvider::create(const QseGeometry &geometry,
        int size) const
{
    QList<QseMetricItem> items;

    // parameters of the metrics
    double offset, unitPerPixel, center;
    if (m_orientation == Vertical)
    {
        offset = geometry.y();
        unitPerPixel = geometry.height() / size;
        center = - offset / unitPerPixel;
    }
    else
    {
        offset = geometry.x() * m_coeff;
        if (geometry.samplePerPixel() > 0)
        {
            unitPerPixel = geometry.samplePerPixel() * m_coeff;
            center = - (offset*geometry.samplePerPixel()) / unitPerPixel;
        }
        else
        {
            unitPerPixel = 1.0 / -geometry.samplePerPixel() * m_coeff;
            center = - offset / unitPerPixel;
        }
    }

    // calculate the absolute position of the central lines
    //double center = - offset / unitPerPixel;
    // value of division
    double vod = m_mapper->calcNearestValue(unitPerPixel, m_minimumStep);
    // estimate pixel count betweeen metrics
    double step = vod / unitPerPixel;

    // center line is visible
    if (center >= 0.0 && center < size)
    {
        items.push_back(QseMetricItem(center, 1, "0"));
        for (double i = center + step, v = vod; i < size; i += step, v += vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(v)));
        for (double i = center - step, v = -vod; i >= 0.0; i -= step, v -= vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(v)));
    }
    // center line is too up
    else if (center < 0.0)
    {
        // sc - section count
        qint64 sc = qAbs(static_cast<qint64>(center / step));
        for (double i = center + step*sc, v = vod*sc; i < size; i += step, v += vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(v)));
    }
    // center line is too down
    else
    {
        // sc - section count
        qint64 sc = qAbs(static_cast<qint64>((center - size) / step));
        for (double i = center - step*sc, v = -vod*sc; i >= 0.0; i -= step, v -= vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(v)));
    }

    return items;
}

void QseLineMetricProvider::setCoeff(double coeff)
{
    if (m_coeff != coeff)
    {
        m_coeff = coeff;
        emit changed();
    }
}
