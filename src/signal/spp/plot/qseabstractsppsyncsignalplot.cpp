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
                this, SLOT(setUpdateOnce()));
        connect(m_dataSource, SIGNAL(destroyed(QObject*)),
                this, SLOT(dataSource_destroyed(QObject*)));
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
