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
#include "qsesppsignallinearamplmetricprovider.h"
#include "qsemetricmapper.h"
#include <QDebug>


QseSppSignalLinearAmplMetricProvider::QseSppSignalLinearAmplMetricProvider(QObject *parent)
    : QseAbstractSppMetricProvider(parent)
{
    m_mapper = new QseMetricMapper();
    m_factor = 1.0;
}

QseSppSignalLinearAmplMetricProvider::~QseSppSignalLinearAmplMetricProvider()
{
    delete m_mapper;
}

void QseSppSignalLinearAmplMetricProvider::setFactor(double factor)
{
    if (m_factor != factor) {
        m_factor = factor;
        emit changed();
    }
}

int QseSppSignalLinearAmplMetricProvider::maximumTextLenght() const
{
    return 8;
}

QList<QseMetricItem> QseSppSignalLinearAmplMetricProvider::create(const QseSppGeometry &geometry,
                                                                  int size) const
{
    QList<QseMetricItem> items;

    // parameters of the metrics
    const double offset = geometry.y() * m_factor;
    const double unitPerPixel = geometry.height() / size * m_factor;

    // calculate the absolute position of the central lines
    const double center = size / 2.0 - offset / unitPerPixel;
    // value of division
    const double vod = m_mapper->calcNearestValue(unitPerPixel, minimumStep());
    // estimate pixel count betweeen metrics
    const double step = vod / unitPerPixel;

    // center line is visible
    if (center >= 0.0 && center < size) {
        items.push_back(QseMetricItem(center, 0, "0"));
        for (double i = center + step, v = vod; i < size; i += step, v += vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(-v)));
        for (double i = center - step, v = -vod; i >= 0.0; i -= step, v -= vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(-v)));
    }
    // center line is too up
    else if (center < 0.0) {
        // sc - section count
        const qint64 sc = qAbs(static_cast<qint64>(center / step));
        for (double i = center + step * sc, v = vod * sc; i < size; i += step, v += vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(-v)));
    }
    // center line is too down
    else {
        // sc - section count
        const qint64 sc = qAbs(static_cast<qint64>((center - size) / step));
        for (double i = center - step * sc, v = -vod * sc; i >= 0.0; i -= step, v -= vod)
            items.push_back(QseMetricItem(qRound(i), 1, QString::number(-v)));
    }

    return items;
}
