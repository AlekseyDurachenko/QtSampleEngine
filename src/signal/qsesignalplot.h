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
#ifndef QSESIGNALPLOT_H
#define QSESIGNALPLOT_H


#include "qsegeometry.h"
#include "qseabstractplot.h"
#include <QPen>
class QseAbstractSignalPlotDelegate;
class QseAbstractSignalDataSource;


class QseSignalPlot : public QseAbstractPlot
{
    Q_OBJECT
    Q_ENUMS(ZeroLine)
    Q_PROPERTY(ZeroLine zeroLine READ zeroLine WRITE setZeroLine)
public:
    enum ZeroLine {
        Top     = 0x01,
        Middle  = 0x02,
        Bottom  = 0x03
    };

    explicit QseSignalPlot(QObject *parent = 0);
    virtual ~QseSignalPlot();

    inline QseAbstractSignalDataSource *dataSource() const;
    void setDataSource(QseAbstractSignalDataSource *dataSource);

    inline QseAbstractSignalPlotDelegate *plotDelegate() const;
    void setPlotDelegate(QseAbstractSignalPlotDelegate *plotDelegate);

    inline ZeroLine zeroLine() const;
    void setZeroLine(ZeroLine zeroLine);

    virtual bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);

private slots:
    void dataSource_dataChanged();
    void dataSource_destroyed();
    void plotDelegate_changed();
    void plotDelegate_destroyed();

private:
    QseAbstractSignalDataSource *m_dataSource;
    QseAbstractSignalPlotDelegate *m_plotDelegate;
    ZeroLine m_zeroLine;
    double *m_minimums;
    double *m_maximums;
};

QseAbstractSignalDataSource *QseSignalPlot::dataSource() const
{
    return m_dataSource;
}

QseAbstractSignalPlotDelegate *QseSignalPlot::plotDelegate() const
{
    return m_plotDelegate;
}

QseSignalPlot::ZeroLine QseSignalPlot::zeroLine() const
{
    return m_zeroLine;
}


#endif // QSESIGNALPLOT_H
