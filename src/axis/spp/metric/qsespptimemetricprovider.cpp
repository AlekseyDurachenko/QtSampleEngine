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
#include "qsespptimemetricprovider.h"
#include "qsemetricmapper.h"
#include <QFontMetrics>
#include <QTime>


QseSppTimeMetricProvider::QseSppTimeMetricProvider(QObject *parent) :
    QseAbstractSppMetricProvider(parent)
{
    m_mapper = new QseMetricMapper();
    m_sampleRate = 1.0;
}

QseSppTimeMetricProvider::~QseSppTimeMetricProvider()
{
    delete m_mapper;
}

void QseSppTimeMetricProvider::setSampleRate(double sampleRate)
{
    if (sampleRate != m_sampleRate)
    {
        m_sampleRate = sampleRate;
        emit changed();
    }
}

int QseSppTimeMetricProvider::maximumTextLenght() const
{
    return 15;
}

QList<QseMetricItem> QseSppTimeMetricProvider::create(
        const QseSppGeometry &geometry, int size) const
{
    QList<QseMetricItem> items;

    // parameters for current metrics
    //double offset = geometry.toAbsoluteSampleOffset(1.0 / m_sampleRate);
    //double unitPerPixel = //geometry.toAbsoluteSamplePerPixel(1.0 / m_sampleRate);
    double samplingInterval = 1.0 / m_sampleRate;

    double offset;
    if (geometry.samplesPerPixel() > 0)
        offset = geometry.x() * samplingInterval;
    else
        offset = geometry.x() * samplingInterval;

    double unitPerPixel;
    if (geometry.samplesPerPixel() > 0)
        unitPerPixel = geometry.samplesPerPixel() * samplingInterval;
    else
        unitPerPixel = 1.0 / -geometry.samplesPerPixel() * samplingInterval;

    // Value Of Division
    double vod = m_mapper->calcNearestValue(unitPerPixel, minimumStep());
    // because QTime cannot show time less then 0.001sec we shoud
    // use 0.001 as minimum vod
    if (vod < 0.001)
        vod = 0.001;
    // estimate pixel count betweeen metrics
    double step = vod / unitPerPixel;

    // sc - section count
    int sc = static_cast<int>(offset / vod);

    for (double i = step*sc - offset/unitPerPixel, v = sc*vod; i < size; i += step, v += vod)
    {
        QTime time = QTime(0, 0, 0).addMSecs(static_cast<int>(v*1000.0));
        QString text = time.toString("hh:mm:ss.zzz");
        items.push_back(QseMetricItem(qRound(i), 1, text));
    }

    return items;
}
