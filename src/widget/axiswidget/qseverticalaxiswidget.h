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
#ifndef QSEVERTICALAXISWIDGET_H
#define QSEVERTICALAXISWIDGET_H

#include "qseabstractaxiswidget.h"


class QseVerticalAxisWidget : public QseAbstractAxisWidget
{
    Q_OBJECT
    Q_ENUMS(Alignment)
    Q_PROPERTY(Alignment alignment READ alignment WRITE setAlignment)
public:
    enum Alignment {
        AlignLeft       = 0x0001,
        AlignRight      = 0x0002,
        AlignHCenter    = 0x0004
    };

    explicit QseVerticalAxisWidget(QWidget *parent = 0);

    inline Alignment alignment() const;
    void setAlignment(Alignment alignment);

protected:
    void recalcProviderMinimumSize(QseAbstractMetricProvider *provider);
    void leftRightRender(QPainter *painter);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual QSize minimumSizeHint() const;

protected:
    virtual void endModifyTextFont(const QFont &font);
    virtual void endModifyMetricProvider(QseAbstractMetricProvider *provider);

private:
    QImage m_cache;
    Alignment m_alignment;
};

QseVerticalAxisWidget::Alignment QseVerticalAxisWidget::alignment() const
{
    return m_alignment;
}


#endif // QSEVERTICALAXISWIDGET_H
