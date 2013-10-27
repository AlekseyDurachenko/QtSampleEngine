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
#ifndef QSEABSTRACTPLOT_H
#define QSEABSTRACTPLOT_H

#include <QObject>
#include <QPainter>
#include <QRect>
#include "qsegeometry.h"


class QseAbstractPlot : public QObject
{
    Q_OBJECT
public:
    explicit QseAbstractPlot(QObject *parent = 0);

    inline bool isUpdateOnce() const;

    virtual bool isVisible(const QRect &rect, const QseGeometry &geometry);
    virtual bool hasChanges(const QRect &rect, const QseGeometry &geometry);
    virtual void draw(QPainter *painter, const QRect &rect, const QseGeometry &geometry);
public slots:
    /*! This method set flag isUpdateOnce() to true, and emit changed()
     */
    void setUpdateOnce(bool need = true);
    /*! This method used for reset the cached values of the plotter,
     *  we should realize it in the children class
     */
    virtual void reset();
signals:
    void changed();
private:
    bool m_updateOnce;
};


bool QseAbstractPlot::isUpdateOnce() const
{
    return m_updateOnce;
}


#endif // QSEABSTRACTPLOT_H
