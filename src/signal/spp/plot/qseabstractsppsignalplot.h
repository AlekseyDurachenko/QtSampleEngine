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
#ifndef QSEABSTRACTSPPSIGNALPLOT_H
#define QSEABSTRACTSPPSIGNALPLOT_H

#include <QPen>
#include "qsesppgeometry.h"
#include "qsepeakarray.h"
#include "qseabstractsppplot.h"
class QseAbstractSppSignalPlotDelegate;
class QseAbstractPeakDataSource;

class QseAbstractSppSignalPlot : public QseAbstractSppPlot
{
    Q_OBJECT
    Q_ENUMS(ZeroLine)
    Q_PROPERTY(ZeroLine zeroLine READ zeroLine WRITE setZeroLine)
    Q_PROPERTY(qreal canvasOpacity READ canvasOpacity WRITE setCanvasOpacity)
    Q_PROPERTY(QBrush canvasBrush READ canvasBrush WRITE setCanvasBrush)
    Q_PROPERTY(bool canvasVisible READ isCanvasVisible WRITE setCanvasVisible)
public:
    enum ZeroLine
    {
        Top     = 0x01,
        Middle  = 0x02,
        Bottom  = 0x03
    };

    explicit QseAbstractSppSignalPlot(QObject *parent = 0);

    inline qreal canvasOpacity() const;
    void setCanvasOpacity(qreal opacity);

    inline const QBrush &canvasBrush() const;
    void setCanvasBrush(const QBrush &brush);

    inline bool isCanvasVisible() const;
    void setCanvasVisible(bool visible);

    inline QseAbstractSppSignalPlotDelegate *plotDelegate() const;
    void setPlotDelegate(QseAbstractSppSignalPlotDelegate *plotDelegate);

    inline ZeroLine zeroLine() const;
    void setZeroLine(ZeroLine zeroLine);

    virtual bool hasChanges(const QRect &rect, const QseSppGeometry &geometry);
    virtual bool isVisible(const QRect &rect, const QseSppGeometry &geometry);
private slots:
    void plotDelegate_changed();
    void plotDelegate_destroyed();
protected:
    void drawCanavs(QPainter *painter, const QRect &rect,
                    const QseSppGeometry &geometry);
    inline int calcDy(const QRect &rect);
protected:
    // TODO: need to more correct method name
    virtual QseAbstractPeakDataSource *usedDataSource() const = 0;
private:
    QseAbstractSppSignalPlotDelegate *m_plotDelegate;
    ZeroLine m_zeroLine;
    bool m_canvasVisible;
    qreal m_opacity;
    QBrush m_brush;
};

qreal QseAbstractSppSignalPlot::canvasOpacity() const
{
    return m_opacity;
}

const QBrush &QseAbstractSppSignalPlot::canvasBrush() const
{
    return m_brush;
}

bool QseAbstractSppSignalPlot::isCanvasVisible() const
{
    return m_canvasVisible;
}

QseAbstractSppSignalPlotDelegate *QseAbstractSppSignalPlot::plotDelegate() const
{
    return m_plotDelegate;
}

QseAbstractSppSignalPlot::ZeroLine QseAbstractSppSignalPlot::zeroLine() const
{
    return m_zeroLine;
}

int QseAbstractSppSignalPlot::calcDy(const QRect &rect)
{
    switch (zeroLine())
    {
    case Top:
        return 0;
    case Middle:
        return rect.height()/2.0;
    case Bottom:
        return rect.height();
    }

    return rect.height()/2.0;
}


#endif // QSEABSTRACTSPPSIGNALPLOT_H
