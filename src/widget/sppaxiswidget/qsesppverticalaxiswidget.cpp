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
#include "qsesppverticalaxiswidget.h"
#include "qseabstractsppmetricprovider.h"
#include <QPainter>


QseSppVerticalAxisWidget::QseSppVerticalAxisWidget(QWidget *parent) :
    QseAbstractSppAxisWidget(parent)
{
    m_alignment = AlignRight;
}

void QseSppVerticalAxisWidget::setAlignment(
        QseSppVerticalAxisWidget::Alignment alignment)
{
    if (m_alignment != alignment)
    {
        m_alignment = alignment;
        setUpdateOnce(true);
    }
}

void QseSppVerticalAxisWidget::recalcProviderMinimumSize(
        QseAbstractSppMetricProvider *provider)
{
    if (provider)
        provider->setMinimumStep(QFontMetrics(textFont()).height() * 2.0);
}

void QseSppVerticalAxisWidget::leftRightRender(QPainter *painter)
{
    if (!metricProvider())
        return;

    // fetch metric list
    QList<QseMetricItem> metricList = m_provider->create(geometry(), height());

    int mpX1, mpX2, mtX1, mtY1, mtW, mtH, flags;
    if (m_alignment == AlignRight)
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
            painter->drawLine(mpX1, metric.offset(),
                              mpX2, metric.offset());

    // draw the help text for the metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList)
        if (metric.level() == 0 || metric.level() == 1)
            painter->drawText(QRect(mtX1, metric.offset()+mtY1,
                                    mtW, mtH), flags, metric.text());
}

void QseSppVerticalAxisWidget::paintEvent(QPaintEvent */*event*/)
{
    if (isUpdateOnce() || m_cache.size() != size())
    {
        // resize image, if needed
        if (size() != m_cache.size())
            m_cache = QImage(size(), QImage::Format_RGB32);

        // draw background
        QPainter imgPainter(&m_cache);
        imgPainter.fillRect(rect(), background());

        if (metricProvider())
            leftRightRender(&imgPainter);

        setUpdateOnce(false);
    }

    QPainter painter(this);
    painter.drawImage(rect(), m_cache);
}

QSize QseSppVerticalAxisWidget::minimumSizeHint() const
{
    if (metricProvider()) switch (m_alignment)
    {
    case AlignLeft:
    case AlignRight:
        return QSize(QFontMetrics(textFont()).width(
                QString(m_provider->maximumTextLenght(), '0'))
                     + metricSize() + 2, 0);
    case AlignHCenter:
        return QSize(QFontMetrics(textFont()).width(
                QString(m_provider->maximumTextLenght(), '0'))
                     + metricSize()*2 + 4, 0);
    }

    return QseAbstractSppAxisWidget::minimumSizeHint();
}

void QseSppVerticalAxisWidget::endModifyTextFont(const QFont &/*font*/)
{
    recalcProviderMinimumSize(metricProvider());
}

void QseSppVerticalAxisWidget::endModifyMetricProvider(
        QseAbstractSppMetricProvider */*provider*/)
{
    recalcProviderMinimumSize(metricProvider());
}
