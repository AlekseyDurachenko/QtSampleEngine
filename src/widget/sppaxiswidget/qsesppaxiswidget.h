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
#ifndef QSESPPAXISWIDGET_H
#define QSESPPAXISWIDGET_H

#include "qseabstractsppwidget.h"
#include <QPen>
class QseAbstractSppMetricProvider;


class QseSppAxisWidget : public QseAbstractSppWidget
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(QPen metricPen READ metricPen WRITE setMetricPen)
    Q_PROPERTY(QPen textPen READ textPen WRITE setTextPen)
    Q_PROPERTY(QBrush background READ background WRITE setBackground)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(int metricSize READ metricSize WRITE setMetricSize)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation)
public:
    enum Orientation
    {
        Left    = 0x01,
        Right   = 0x02,
        Top     = 0x03,
        Bottom  = 0x04
    };
    explicit QseSppAxisWidget(Orientation orientation = Left,
                              QWidget *parent = 0);

    inline const QPen &metricPen() const;
    void setMetricPen(const QPen &pen);

    inline const QPen &textPen() const;
    void setTextPen(const QPen &pen);

    inline const QBrush &background() const;
    void setBackground(const QBrush &brush);

    inline const QFont &textFont() const;
    void setTextFont(const QFont &font);

    inline int metricSize() const;
    void setMetricSize(int size);

    inline Orientation orientation() const;
    void setOrientation(Orientation orientation);

    inline QseAbstractSppMetricProvider *metricProvider();
    void setMetricProvider(QseAbstractSppMetricProvider *provider);
private slots:
    void provider_destroyed();
protected:
    void paintEvent(QPaintEvent *event);
    QSize minimumSizeHint() const;
protected:
    void recalcProviderMinimumSize(QseAbstractSppMetricProvider *provider);
    void topDownRender(QPainter *painter);
    void leftRightRender(QPainter *painter);
protected:
    QseAbstractSppMetricProvider *m_provider;
    QImage m_cache;
    QBrush m_background;
    QPen m_metricPen;
    QPen m_textPen;
    QFont m_textFont;
    int m_metricSize;
    Orientation m_orientation;
};


const QPen &QseSppAxisWidget::metricPen() const
{
    return m_metricPen;
}

const QPen &QseSppAxisWidget::textPen() const
{
    return m_textPen;
}

const QBrush &QseSppAxisWidget::background() const
{
    return m_background;
}

const QFont &QseSppAxisWidget::textFont() const
{
    return m_textFont;
}

int QseSppAxisWidget::metricSize() const
{
    return m_metricSize;
}

inline QseAbstractSppMetricProvider *QseSppAxisWidget::metricProvider()
{
    return m_provider;
}

inline QseSppAxisWidget::Orientation QseSppAxisWidget::orientation() const
{
    return m_orientation;
}


#endif // QSESPPAXISWIDGET_H
