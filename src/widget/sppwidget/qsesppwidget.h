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
#ifndef QSESSSPPWIDGET_H
#define QSESSSPPWIDGET_H

#include "qseabstractsppwidget.h"
class QseAbstractSppPlot;


class QseSppWidget : public QseAbstractSppWidget
{
    Q_OBJECT
public:
    explicit QseSppWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline const QList<QseAbstractSppPlot *> &preUncachedPlot() const;
    void setPreUncachedPlot(const QList<QseAbstractSppPlot *> &plots);

    inline const QList<QseAbstractSppPlot *> &cachedPlot() const;
    void setCachedPlot(const QList<QseAbstractSppPlot *> &plots);

    inline const QList<QseAbstractSppPlot *> &postUncachedPlot() const;
    void setPostUncachedPlot(const QList<QseAbstractSppPlot *> &plots);
private slots:
    void preUncachedPlots_destroyed(QObject *obj);
    void cachedPlots_destroyed(QObject *obj);
    void postUncachedPlots_destroyed(QObject *obj);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QList<QImage> m_caches;
    QList<QseAbstractSppPlot *> m_preUncachedPlots;
    QList<QseAbstractSppPlot *> m_cachedPlots;
    QList<QseAbstractSppPlot *> m_postUncachedPlots;
};

const QList<QseAbstractSppPlot *> &QseSppWidget::preUncachedPlot() const
{
    return m_preUncachedPlots;
}

const QList<QseAbstractSppPlot *> &QseSppWidget::cachedPlot() const
{
    return m_cachedPlots;
}

const QList<QseAbstractSppPlot *> &QseSppWidget::postUncachedPlot() const
{
    return m_postUncachedPlots;
}


#endif // QSESSSPPWIDGET_H
