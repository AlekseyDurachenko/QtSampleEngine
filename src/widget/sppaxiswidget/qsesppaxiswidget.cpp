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
#include "qsesppaxiswidget.h"
#include "qseabstractsppmetricprovider.h"
#include <QPainter>


QseSppAxisWidget::QseSppAxisWidget(Orientation orientation, QWidget *parent) :
    QseAbstractSppWidget(parent)
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
    m_orientation = orientation;
}

void QseSppAxisWidget::setMetricPen(const QPen &pen)
{
    if (pen != m_metricPen)
    {
        m_metricPen = pen;
        setUpdatesEnabled(true);
    }
}

void QseSppAxisWidget::setTextPen(const QPen &pen)
{
    if (pen != m_textPen)
    {
        m_textPen = pen;
        setUpdatesEnabled(true);
    }
}

void QseSppAxisWidget::setBackground(const QBrush &brush)
{
    if (brush != m_background)
    {
        m_background = brush;
        setUpdatesEnabled(true);
    }
}

void QseSppAxisWidget::setTextFont(const QFont &font)
{
    if (font != m_textFont)
    {
        m_textFont = font;
        recalcProviderMinimumSize(m_provider);
        setUpdatesEnabled(true);
    }
}

void QseSppAxisWidget::setMetricSize(int size)
{
    if (size != m_metricSize)
    {
        m_metricSize = size;
        setUpdateOnce(true);
    }
}

void QseSppAxisWidget::setOrientation(Orientation orientation)
{
    if (m_orientation != orientation)
    {
        m_orientation = orientation;
        recalcProviderMinimumSize(m_provider);
        setUpdateOnce(true);
    }
}

void QseSppAxisWidget::setMetricProvider(QseAbstractSppMetricProvider *provider)
{
    if (m_provider)
        disconnect(m_provider, 0, this, 0);

    m_provider = provider;
    if (m_provider)
    {
        connect(m_provider, SIGNAL(changed()),
                this, SLOT(setUpdateOnce()));
        connect(m_provider, SIGNAL(destroyed()),
                this, SLOT(provider_destroyed()));
        recalcProviderMinimumSize(m_provider);
    }

    setUpdateOnce(true);
}

void QseSppAxisWidget::recalcProviderMinimumSize(
        QseAbstractSppMetricProvider *provider)
{
    if (provider)
    {
        if (m_orientation == Left || m_orientation == Right)
            provider->setMinimumStep(QFontMetrics(m_textFont).height() * 2.0);
        else
            provider->setMinimumStep(
                    QFontMetrics(m_textFont).width(
                            QString(provider->maximumTextLenght(), '0')));
    }
}

void QseSppAxisWidget::provider_destroyed()
{
    m_provider = 0;
}

void QseSppAxisWidget::paintEvent(QPaintEvent *)
{
    if (isUpdateOnce() || m_cache.size() != size())
    {
        // resize image, if needed
        if (size() != m_cache.size())
            m_cache = QImage(size(), QImage::Format_RGB32);

        // draw background
        QPainter imgPainter(&m_cache);
        imgPainter.fillRect(rect(), m_background);

        if (m_provider)
        {
            if (m_orientation == Top || m_orientation == Bottom)
                topDownRender(&imgPainter);
            else
                leftRightRender(&imgPainter);
        }

        setUpdateOnce(false);
    }

    QPainter painter(this);
    painter.drawImage(rect(), m_cache);
}

void QseSppAxisWidget::topDownRender(QPainter *painter)
{
    // fetch metric list
    QList<QseMetricItem> metricList = m_provider->create(geometry(), width());

    // calculate geometry of the metric for top or down postion of them
    int mpY1, mpY2, tpY;
    if (m_orientation == Top)
    {
        mpY1 = height() - m_metricSize;
        mpY2 = height();
        //tpY  = height() - 2;
        tpY  = height() - m_metricSize - 2;
    }
    else // m_orientation == Down
    {
        mpY1 = 0;
        mpY2 = m_metricSize;
        tpY  = height() - 2;
        // TOD_O: need to be corrected.
        //tpY  = QFontMetrics(m_textFont).height() - 2;
    }

    // draw only center and main metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList)
        if (metric.level() == 0 || metric.level() == 1)
            painter->drawLine(metric.offset(), mpY1, metric.offset(), mpY2);

    // draw the help text for the metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList)
        if (metric.level() == 0 || metric.level() == 1)
            painter->drawText(QPoint(metric.offset(), tpY), metric.text());
            //painter->drawText(QPoint(metric.offset()+2, tpY), metric.text());
}

void QseSppAxisWidget::leftRightRender(QPainter *painter)
{
    // fetch metric list
    QList<QseMetricItem> metricList = m_provider->create(geometry(), height());

    int mpX1, mpX2, mtX1, mtY1, mtW, mtH, flags;
    if (m_orientation == Left)
    {
        mpX1 = width() - m_metricSize;
        mpX2 = width();
        mtX1 = 0;
        mtY1 = - QFontMetrics(m_textFont).height()/2;
        mtW  = width() - m_metricSize;
        mtH  = QFontMetrics(m_textFont).height();
        flags= Qt::AlignRight|Qt::AlignVCenter;
    }
    else // m_orientation == Right
    {
        mpX1 = 0;
        mpX2 = m_metricSize;
        mtX1 = m_metricSize + 2;
        mtY1 = - QFontMetrics(m_textFont).height()/2;
        mtW  = width() - m_metricSize;
        mtH  = QFontMetrics(m_textFont).height();
        flags= Qt::AlignLeft|Qt::AlignVCenter;
    }

    // draw only center and main metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList)
        if (metric.level() == 0 || metric.level() == 1)
            painter->drawLine(mpX1, metric.offset(), mpX2, metric.offset());

    // draw the help text for the metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList)
        if (metric.level() == 0 || metric.level() == 1)
            painter->drawText(QRect(mtX1, metric.offset()+mtY1, mtW, mtH),
                              flags, metric.text());
}

QSize QseSppAxisWidget::minimumSizeHint() const
{
    if (m_orientation == Left || m_orientation == Right)
    {
        if (m_provider)
            return QSize(QFontMetrics(m_textFont).width(
                    QString(m_provider->maximumTextLenght(), '0'))
                         + m_metricSize + 2, 0);
        else
            return QSize(m_metricSize + 2, 0);
    }
    else
    {
        //int h1 = QFontMetrics(m_textFont).height() + 2;
        //int h2 = m_metricSize;
        //return QSize(0, ((h1 > h2) ? (h1) : (h2)));
        return QSize(0, QFontMetrics(m_textFont).height() + m_metricSize + 2);
    }
}
