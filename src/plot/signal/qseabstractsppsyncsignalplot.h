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
#ifndef QSEABSTRACTSPPSYNCSIGNALPLOT_H
#define QSEABSTRACTSPPSYNCSIGNALPLOT_H

#include "qseabstractsppsignalplot.h"
class QseAbstractSppSyncDataSource;


class QseAbstractSppSyncSignalPlot : public QseAbstractSppSignalPlot
{
    Q_OBJECT
public:
    explicit QseAbstractSppSyncSignalPlot(QObject *parent = 0);

    inline QseAbstractSppSyncDataSource *dataSource() const;
    void setDataSource(QseAbstractSppSyncDataSource *dataSource);

    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseSppGeometry &geometry);
private slots:
    void dataSource_destroyed(QObject *obj);
private:
    QseAbstractSppSyncDataSource *m_dataSource;
};

QseAbstractSppSyncDataSource *QseAbstractSppSyncSignalPlot::dataSource() const
{
    return m_dataSource;
}


#endif // QSEABSTRACTSPPSYNCSIGNALPLOT_H