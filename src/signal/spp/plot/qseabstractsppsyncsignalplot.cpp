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
#include "qseabstractsppsyncsignalplot.h"
#include "qseabstractsppsyncpeakdatasource.h"


QseAbstractSppSyncSignalPlot::QseAbstractSppSyncSignalPlot(QObject *parent) :
    QseAbstractSppSignalPlot(parent)
{
    m_dataSource = 0;
    m_firstChangedSample = -1;
    m_lastChangedSample = -1;
    m_hasDataChanges = false;
}

void QseAbstractSppSyncSignalPlot::setDataSource(
        QseAbstractSppSyncPeakDataSource *dataSource)
{
    if (m_dataSource)
        disconnect(m_dataSource, 0, this, 0);

    m_dataSource = dataSource;
    if (m_dataSource)
    {
        connect(m_dataSource, SIGNAL(dataChanged()),
                this, SLOT(dataSource_dataChanged()));
        connect(m_dataSource, SIGNAL(dataChanged(qint64,qint64)),
                this, SLOT(dataSource_dataChanged(qint64,qint64)));
        connect(m_dataSource, SIGNAL(destroyed(QObject*)),
                this, SLOT(dataSource_destroyed(QObject*)));

        m_hasDataChanges = true;
        if (!m_dataSource || m_dataSource->count() == 0)
        {
            m_firstChangedSample = -1;
            m_lastChangedSample = -1;
        }
        else
        {
            m_firstChangedSample = 0;
            m_lastChangedSample = m_dataSource->count()-1;
        }
    }

    setUpdateOnce(true);
}

bool QseAbstractSppSyncSignalPlot::hasChanges(const QRect &rect,
        const QseSppGeometry &geometry)
{
    return (isUpdateOnce() || rect != lastRect() || geometry != lastGeometry());
}

bool QseAbstractSppSyncSignalPlot::isVisible(const QRect &rect,
        const QseSppGeometry &geometry)
{
    if (m_dataSource == 0)
        return false;

    if (m_dataSource->count() == 0)
        return false;

    // TODO: fix algorithm, because it can cause the overflow
    int sl = QseSppGeometry::calcOffset(geometry, 0);
    int sr = QseSppGeometry::calcOffset(geometry, m_dataSource->count()-1);

    if ((sl < 0 && sr < 0) || (sl >= rect.width() && sr >= rect.width()))
        return false;

    return true;
}

void QseAbstractSppSyncSignalPlot::dataSource_destroyed(QObject *obj)
{
    if (obj == m_dataSource)
        m_dataSource = 0;
}

void QseAbstractSppSyncSignalPlot::dataSource_dataChanged()
{
    m_hasDataChanges = true;
    if (!m_dataSource || m_dataSource->count() == 0)
    {
        m_firstChangedSample = -1;
        m_lastChangedSample = -1;
    }
    else
    {
        m_firstChangedSample = 0;
        m_lastChangedSample = m_dataSource->count()-1;
    }

    setUpdateOnce(true);
}

void QseAbstractSppSyncSignalPlot::dataSource_dataChanged(qint64 first,
        qint64 last)
{
    m_hasDataChanges = true;
    if (!m_dataSource || m_dataSource->count() == 0)
    {
        m_firstChangedSample = -1;
        m_lastChangedSample = -1;
    }
    else
    {
        m_firstChangedSample = first;
        m_lastChangedSample = last;
    }

    setUpdateOnce(true);
}

bool QseAbstractSppSyncSignalPlot::hasDataChanges() const
{
    return m_hasDataChanges;
}

qint64 QseAbstractSppSyncSignalPlot::firstChangedSample() const
{
    return m_firstChangedSample;
}

qint64 QseAbstractSppSyncSignalPlot::lastChangedSample() const
{
    return m_lastChangedSample;
}

void QseAbstractSppSyncSignalPlot::resetDataChanges()
{
    m_firstChangedSample = -1;
    m_lastChangedSample = -1;
    m_hasDataChanges = false;
}
