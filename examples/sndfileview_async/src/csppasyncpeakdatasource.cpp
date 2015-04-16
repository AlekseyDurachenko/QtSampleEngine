// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "csppasyncpeakdatasource.h"
#include "cspppeakreply.h"
#include <QThread>


CSppAsyncPeakDataSource::CSppAsyncPeakDataSource(QObject *parent) :
    QseAbstractSppAsyncPeakDataSource(parent)
{
    m_thread = new QThread(this);
    m_thread->start();
}

CSppAsyncPeakDataSource::~CSppAsyncPeakDataSource()
{
    m_thread->quit();
    m_thread->wait();
}

qint64 CSppAsyncPeakDataSource::count() const
{
    return m_samples.count();
}

qint64 CSppAsyncPeakDataSource::minIndex() const
{
    return 0;
}

qint64 CSppAsyncPeakDataSource::maxIndex() const
{
    return m_samples.count()-1;
}

QseAbstractSppPeakReply *CSppAsyncPeakDataSource::read(
        const QseSppPeakRequest &request)
{
    CSppPeakReply *reply = new CSppPeakReply(m_samples, request);
    reply->moveToThread(m_thread);
    reply->start();
    return reply;
}

void CSppAsyncPeakDataSource::setSamples(const QVector<double> &samples,
        double sampleRate)
{
    m_samples = samples;
    m_sampleRate = sampleRate;

    emit dataChanged();
}
