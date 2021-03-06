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
#include "qsewidget.h"
#include <QPainter>
#include "qseabstractplot.h"


QseWidget::QseWidget(QWidget *parent, Qt::WindowFlags f)
    : QseAbstractWidget(parent, f)
{
    setMouseTracking(true);
    setAutoFillBackground(false);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void QseWidget::setPreUncachedPlots(const QList<QseAbstractPlot *> &plots)
{
    if (m_preUncachedPlots == plots)
        return;

    foreach (QseAbstractPlot *plot, m_preUncachedPlots)
        disconnect(plot, 0, this, 0);

    m_preUncachedPlots = plots;
    foreach (QseAbstractPlot *plot, m_preUncachedPlots) {
        connect(plot, SIGNAL(updateNeeded()), this, SLOT(update()));
        connect(plot, SIGNAL(destroyed(QObject *)),
                this, SLOT(preUncachedPlots_destroyed(QObject *)));
    }

    update();
}

void QseWidget::setCachedPlots(const QList<QseAbstractPlot *> &plots)
{
    if (m_cachedPlots == plots)
        return;

    foreach (QseAbstractPlot *plot, m_cachedPlots)
        disconnect(plot, 0, this, 0);

    m_cachedPlots = plots;
    foreach (QseAbstractPlot *plot, m_cachedPlots) {
        connect(plot, SIGNAL(updateNeeded()), this, SLOT(update()));
        connect(plot, SIGNAL(destroyed(QObject *)),
                this, SLOT(cachedPlots_destroyed(QObject *)));
    }

    m_caches.clear();
    for (int i = 0; i < m_cachedPlots.count(); ++i)
        m_caches.push_back(QImage());

    update();
}

void QseWidget::setPostUncachedPlots(const QList<QseAbstractPlot *> &plots)
{
    if (m_postUncachedPlots == plots)
        return;

    foreach (QseAbstractPlot *plot, m_postUncachedPlots)
        disconnect(plot, 0, this, 0);

    m_postUncachedPlots = plots;
    foreach (QseAbstractPlot *plot, m_postUncachedPlots) {
        connect(plot, SIGNAL(updateNeeded()), this, SLOT(update()));
        connect(plot, SIGNAL(destroyed(QObject *)),
                this, SLOT(postUncachedPlots_destroyed(QObject *)));
    }

    update();
}

void QseWidget::preUncachedPlots_destroyed(QObject *obj)
{
    m_preUncachedPlots.removeAll(qobject_cast<QseAbstractPlot *>(obj));
    update();
}

void QseWidget::cachedPlots_destroyed(QObject *obj)
{
    int index = m_cachedPlots.indexOf(qobject_cast<QseAbstractPlot *>(obj));
    m_cachedPlots.removeAt(index);
    m_caches.removeAt(index);
    update();
}

void QseWidget::postUncachedPlots_destroyed(QObject *obj)
{
    m_postUncachedPlots.removeAll(qobject_cast<QseAbstractPlot *>(obj));
    update();
}

void QseWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    foreach (QseAbstractPlot *plot, m_preUncachedPlots)
        plot->draw(&painter, rect(), geometry());

    for (int i = 0; i < m_cachedPlots.count(); ++i) {
        if (!m_cachedPlots.at(i)->hasChanges(rect(), geometry()))
            continue;

        if (m_caches.at(i).size() != rect().size())
            m_caches[i] = QImage(rect().size(),
                                 QImage::Format_ARGB32_Premultiplied);
        m_caches[i].fill(0);

        QPainter imgPainter(&m_caches[i]);
        m_cachedPlots[i]->draw(&imgPainter, rect(), geometry());
    }

    foreach (const QImage &image, m_caches)
        if (image.size() == rect().size())
            painter.drawImage(rect(), image);

    foreach (QseAbstractPlot *plot, m_postUncachedPlots)
        plot->draw(&painter, rect(), geometry());
}
