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
#ifndef QSEABSTRACTAXISWIDGET_H
#define QSEABSTRACTAXISWIDGET_H

#include "qseabstractwidget.h"
#include <QPen>
class QseAbstractMetricProvider;


class QseAbstractAxisWidget : public QseAbstractWidget
{
    Q_OBJECT
    Q_PROPERTY(QPen metricPen READ metricPen WRITE setMetricPen)
    Q_PROPERTY(QPen textPen READ textPen WRITE setTextPen)
    Q_PROPERTY(QBrush background READ background WRITE setBackground)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(int metricSize READ metricSize WRITE setMetricSize)
public:
    explicit QseAbstractAxisWidget(QWidget *parent = 0);

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

    inline QseAbstractMetricProvider *metricProvider() const;
    void setMetricProvider(QseAbstractMetricProvider *provider);

private slots:
    void provider_destroyed();

protected:
    virtual void endModifyTextFont(const QFont &font);
    virtual void endModifyMetricSize(int size);
    virtual void endModifyMetricProvider(QseAbstractMetricProvider *provider);

protected:
    QseAbstractMetricProvider *m_provider;
    QImage m_cache;
    QBrush m_background;
    QPen m_metricPen;
    QPen m_textPen;
    QFont m_textFont;
    int m_metricSize;
};

const QPen &QseAbstractAxisWidget::metricPen() const
{
    return m_metricPen;
}

const QPen &QseAbstractAxisWidget::textPen() const
{
    return m_textPen;
}

const QBrush &QseAbstractAxisWidget::background() const
{
    return m_background;
}

const QFont &QseAbstractAxisWidget::textFont() const
{
    return m_textFont;
}

int QseAbstractAxisWidget::metricSize() const
{
    return m_metricSize;
}

inline QseAbstractMetricProvider *QseAbstractAxisWidget::metricProvider() const
{
    return m_provider;
}


#endif // QSEABSTRACTAXISWIDGET_H
