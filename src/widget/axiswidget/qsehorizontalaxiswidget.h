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
#ifndef QSEHORIZONTALAXISWIDGET_H
#define QSEHORIZONTALAXISWIDGET_H

#include "qseabstractaxiswidget.h"


class QseHorizontalAxisWidget : public QseAbstractAxisWidget
{
    Q_OBJECT
    Q_ENUMS(Alignment)
    Q_PROPERTY(Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(int shift READ shift WRITE setShift)
public:
    enum Alignment {
        AlignTop    = 0x0020,
        AlignBottom = 0x0040,
        AlignVCenter = 0x0080
    };

    explicit QseHorizontalAxisWidget(QWidget *parent = 0);

    inline Alignment alignment() const;
    void setAlignment(Alignment alignment);

    inline int shift() const;

signals:
    void shiftChanged(int value);

public slots:
    void setShift(int shift);

protected:
    void recalcProviderMinimumSize(QseAbstractMetricProvider *provider);
    void topDownRender(QPainter *painter);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual QSize minimumSizeHint() const;

protected:
    virtual void endModifyTextFont(const QFont &font);
    virtual void endModifyMetricProvider(QseAbstractMetricProvider *provider);

private:
    QImage m_cache;
    Alignment m_alignment;
    int m_shift;
};

QseHorizontalAxisWidget::Alignment QseHorizontalAxisWidget::alignment() const
{
    return m_alignment;
}

int QseHorizontalAxisWidget::shift() const
{
    return m_shift;
}


#endif // QSEHORIZONTALAXISWIDGET_H
