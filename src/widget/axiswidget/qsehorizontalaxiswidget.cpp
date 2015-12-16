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
#include "qsehorizontalaxiswidget.h"
#include "qseabstractmetricprovider.h"
#include <QPainter>


QseHorizontalAxisWidget::QseHorizontalAxisWidget(QWidget *parent)
    : QseAbstractAxisWidget(parent)
{
    m_alignment = AlignBottom;
    m_shift = 0;
}

void QseHorizontalAxisWidget::setAlignment(QseHorizontalAxisWidget::Alignment alignment)
{
    if (m_alignment != alignment) {
        m_alignment = alignment;
        setUpdateOnce(true);
    }
}

void QseHorizontalAxisWidget::setShift(int shift)
{
    if (m_shift != shift) {
        m_shift = shift;
        setUpdateOnce(true);
        emit shiftChanged(m_shift);
    }
}

void QseHorizontalAxisWidget::recalcProviderMinimumSize(QseAbstractMetricProvider *provider)
{
    if (provider)
        provider->setMinimumStep(QFontMetrics(textFont()).width(QString(provider->maximumTextLenght(), '0')));
}

void QseHorizontalAxisWidget::topDownRender(QPainter *painter)
{
    // fetch metric list
    const QList<QseMetricItem> metricList = m_provider->create(geometry(), width());

    // calculate geometry of the metric for top or down postion of them
    int mpY1, mpY2, tpY;
    if (m_alignment == AlignBottom) {
        mpY1 = height() - m_metricSize;
        mpY2 = height();
        //tpY  = height() - 2;
        tpY  = height() - m_metricSize - 2;
    }
    else { // m_orientation == Down
        mpY1 = 0;
        mpY2 = m_metricSize;
        tpY  = height() - 2;
        // TOD_O: need to be corrected.
        //tpY  = QFontMetrics(m_textFont).height() - 2;
    }

    // draw only center and main metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList) {
        if (metric.level() == 0 || metric.level() == 1) {
            painter->drawLine(metric.offset() + shift(), mpY1,
                              metric.offset() + shift(), mpY2);
        }
    }

    // draw the help text for the metric
    painter->setPen(m_metricPen);
    foreach (const QseMetricItem &metric, metricList) {
        if (metric.level() == 0 || metric.level() == 1) {
            painter->drawText(QPoint(metric.offset() + shift(), tpY),
                              metric.text());
        }
    }
    //painter->drawText(QPoint(metric.offset()+2, tpY), metric.text());
}

void QseHorizontalAxisWidget::paintEvent(QPaintEvent */*event*/)
{
    if (isUpdateOnce() || m_cache.size() != size()) {
        // resize image, if needed
        if (size() != m_cache.size())
            m_cache = QImage(size(), QImage::Format_RGB32);

        // draw background
        QPainter imgPainter(&m_cache);
        imgPainter.fillRect(rect(), background());

        if (metricProvider())
            topDownRender(&imgPainter);

        setUpdateOnce(false);
    }

    QPainter painter(this);
    painter.drawImage(rect(), m_cache);
}

QSize QseHorizontalAxisWidget::minimumSizeHint() const
{
    if (metricProvider()) switch (m_alignment) {
        case AlignBottom:
        case AlignTop:
            return QSize(0, QFontMetrics(textFont()).height() + metricSize() + 2);
        case AlignVCenter:
            return QSize(0, QFontMetrics(textFont()).height() + metricSize() * 2 + 4);
        }

    return QseAbstractAxisWidget::minimumSizeHint();
}

void QseHorizontalAxisWidget::endModifyTextFont(const QFont &/*font*/)
{
    recalcProviderMinimumSize(metricProvider());
}

void QseHorizontalAxisWidget::endModifyMetricProvider(QseAbstractMetricProvider */*provider*/)
{
    recalcProviderMinimumSize(metricProvider());
}
