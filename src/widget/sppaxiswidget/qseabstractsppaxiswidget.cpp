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
#include "qseabstractsppaxiswidget.h"
#include "qseabstractsppmetricprovider.h"


QseAbstractSppAxisWidget::QseAbstractSppAxisWidget(QWidget *parent)
    : QseAbstractSppWidget(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent);

    // by defult provider is not installed, and axis empty widget
    // with background only
    m_provider = 0;
    // default style values
    m_metricSize = 10;
    m_background = QPalette().brush(QPalette::Background);
    m_metricPen = QPen(Qt::black);
    m_textPen = QPen(Qt::black);
}

void QseAbstractSppAxisWidget::setMetricPen(const QPen &pen)
{
    if (pen != m_metricPen) {
        m_metricPen = pen;
        setUpdatesEnabled(true);
    }
}

void QseAbstractSppAxisWidget::setTextPen(const QPen &pen)
{
    if (pen != m_textPen) {
        m_textPen = pen;
        setUpdatesEnabled(true);
    }
}

void QseAbstractSppAxisWidget::setBackground(const QBrush &brush)
{
    if (brush != m_background) {
        m_background = brush;
        setUpdatesEnabled(true);
    }
}

void QseAbstractSppAxisWidget::setTextFont(const QFont &font)
{
    if (font != m_textFont) {
        m_textFont = font;
        endModifyTextFont(m_textFont);
        setUpdatesEnabled(true);
    }
}

void QseAbstractSppAxisWidget::setMetricSize(int size)
{
    if (size != m_metricSize) {
        m_metricSize = size;
        endModifyMetricSize(m_metricSize);
        setUpdateOnce(true);
    }
}

void QseAbstractSppAxisWidget::setMetricProvider(QseAbstractSppMetricProvider *provider)
{
    if (m_provider == provider)
        return;

    if (m_provider)
        disconnect(m_provider, 0, this, 0);

    m_provider = provider;
    if (m_provider) {
        connect(m_provider, SIGNAL(changed()),
                this, SLOT(setUpdateOnce()));
        connect(m_provider, SIGNAL(destroyed()),
                this, SLOT(provider_destroyed()));
    }

    endModifyMetricProvider(m_provider);
    setUpdateOnce(true);
}


void QseAbstractSppAxisWidget::provider_destroyed()
{
    m_provider = 0;
}

void QseAbstractSppAxisWidget::endModifyTextFont(const QFont &/*font*/)
{
}

void QseAbstractSppAxisWidget::endModifyMetricSize(int /*size*/)
{
}

void QseAbstractSppAxisWidget::endModifyMetricProvider(QseAbstractSppMetricProvider */*provider*/)
{
}
