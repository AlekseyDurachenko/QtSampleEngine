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
#ifndef QSEWIDGET_H
#define QSEWIDGET_H

#include "qseabstractwidget.h"
class QseAbstractPlot;


class QseWidget : public QseAbstractWidget
{
    Q_OBJECT
public:
    explicit QseWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline const QList<QseAbstractPlot *> &preUncachedPlots() const;
    void setPreUncachedPlots(const QList<QseAbstractPlot *> &plots);

    inline const QList<QseAbstractPlot *> &cachedPlots() const;
    void setCachedPlots(const QList<QseAbstractPlot *> &plots);

    inline const QList<QseAbstractPlot *> &postUncachedPlots() const;
    void setPostUncachedPlots(const QList<QseAbstractPlot *> &plots);

private slots:
    void preUncachedPlots_destroyed(QObject *obj);
    void cachedPlots_destroyed(QObject *obj);
    void postUncachedPlots_destroyed(QObject *obj);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList<QImage> m_caches;
    QList<QseAbstractPlot *> m_preUncachedPlots;
    QList<QseAbstractPlot *> m_cachedPlots;
    QList<QseAbstractPlot *> m_postUncachedPlots;
};

const QList<QseAbstractPlot *> &QseWidget::preUncachedPlots() const
{
    return m_preUncachedPlots;
}

const QList<QseAbstractPlot *> &QseWidget::cachedPlots() const
{
    return m_cachedPlots;
}

const QList<QseAbstractPlot *> &QseWidget::postUncachedPlots() const
{
    return m_postUncachedPlots;
}


#endif // QSEWIDGET_H
