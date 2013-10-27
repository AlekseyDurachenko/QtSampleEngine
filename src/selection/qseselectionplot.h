// Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#ifndef QSESELECTIONPLOT_H
#define QSESELECTIONPLOT_H

#include <QObject>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include "qseabstractplot.h"
#include "qsegeometry.h"
#include "qseselection.h"

/*! \brief The QseSelection class shows the selected range of the sound
 *
 *  This class draws the opacity box
 */
class QseSelectionPlot : public QseAbstractPlot
{
    Q_OBJECT
public:
    explicit QseSelectionPlot(QObject *parent = 0);

    inline const QBrush &brush() const;
    inline qreal opacity() const;
    void setBrush(const QBrush &brush);
    void setOpacity(qreal opacity);
    void setSelection(QseSelection *selection);

    /*! Before drawing the result widget, we want to know, this cursor
     *  visible or not. Why? because it can be useful for optimize
     *  the the drawing the result widget
     */
    bool isVisible(const QRect &rect, const QseGeometry &geometry);
    void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);
signals:
    /*! This signal emited when one of the waveform parameters is changed,
     *  after this signal, we should update the widget which show the
     *  selection
     */
    void changed();
private slots:
    void selectionDestroyed(QObject*);
private:
    QseSelection *m_selection;
    QBrush m_brush;
    qreal m_opacity;
};


const QBrush &QseSelectionPlot::brush() const
{
    return m_brush;
}

qreal QseSelectionPlot::opacity() const
{
    return m_opacity;
}


#endif // QSESELECTION_H
