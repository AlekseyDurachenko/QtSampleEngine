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
#ifndef QSEAXISWIDGET_H
#define QSEAXISWIDGET_H

#include <QWidget>
#include <QPen>
#include "qseabstractwidget.h"
#include "qseabstractmetricprovider.h"


class QseAxisWidget : public QseAbstractWidget
{
    Q_OBJECT
public:
    enum Orientation { Left, Right, Top, Down };
    explicit QseAxisWidget(Orientation orientation = Left, QWidget *parent = 0);

    inline const QPen &metricPen() const;
    inline const QPen &textPen() const;
    inline const QBrush &background() const;
    inline const QFont &textFont() const;
    inline int metricSize() const;
    inline Orientation orientation() const;
    inline QseAbstractMetricProvider *metricProvider();

    void setMetricPen(const QPen &pen);
    void setTextPen(const QPen &pen);
    void setBackground(const QBrush &brush);
    void setTextFont(const QFont &font);
    void setMetricSize(int size);
    void setOrientation(Orientation orientation);
    void setMetricProvider(QseAbstractMetricProvider *provider);
private slots:
    void metricProviderDestroyed();
protected:
    void paintEvent(QPaintEvent *event);
    QSize minimumSizeHint() const;
protected:
    void recalcProviderMinimumSize(QseAbstractMetricProvider *provider);
    void topDownRender(QPainter *painter);
    void leftRightRender(QPainter *painter);
protected:
    QseAbstractMetricProvider *m_provider;
    QImage m_resImg;
    QBrush m_background;
    QPen m_metricPen;
    QPen m_textPen;
    QFont m_textFont;
    int m_metricSize;
    Orientation m_orientation;
};


const QPen &QseAxisWidget::metricPen() const
{
    return m_metricPen;
}

const QPen &QseAxisWidget::textPen() const
{
    return m_textPen;
}

const QBrush &QseAxisWidget::background() const
{
    return m_background;
}

const QFont &QseAxisWidget::textFont() const
{
    return m_textFont;
}

int QseAxisWidget::metricSize() const
{
    return m_metricSize;
}

inline QseAbstractMetricProvider *QseAxisWidget::metricProvider()
{
    return m_provider;
}

inline QseAxisWidget::Orientation QseAxisWidget::orientation() const
{
    return m_orientation;
}

#endif // QSEABSTRACTAXISWIDGET_H
