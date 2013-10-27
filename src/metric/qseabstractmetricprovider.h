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
#ifndef QSEABSTRACTMETRICPROVIDER_H
#define QSEABSTRACTMETRICPROVIDER_H


#include <QObject>
#include <QList>
#include <QFont>
#include "qsemetricitem.h"
#include "qsegeometry.h"

/*! \brief The QseAbstractMetricProvider class provides the metric model
 *
 * This is abstract class for the metric providers, they should generate the
 * list of the metric items wich contains the information for metric wich
 * should be drawed.
 */
class QseAbstractMetricProvider : public QObject
{
    Q_OBJECT
public:
    QseAbstractMetricProvider(QObject *parent = 0);
    virtual ~QseAbstractMetricProvider() {}

    /*! \brief minimumStep shows the minimum step between metrics
     */
    inline int minimumStep() const;

    /*! \brief setMinimumStep set the minimum step between metrics
     */
    void setMinimumStep(int step);

    /*! \brief maximumTextLenght the maximum text lenght
     */
    virtual int maximumTextLenght() const = 0;

    /*! \brief create creates the metric points
     *
     * \param offset the offset from the corrdinate 0 (zero) in units
     * \param unitPerPixel the coefficient wich shows how many units placed at the one pixel
     * \param minStep the minimum step between main (level 1) metrics
     * \param size the width/height of the widget
     */
    virtual QList<QseMetricItem> create(const QseGeometry &geometry, int size) const = 0;
signals:
    /*! \brief indicates that representation of the metric is changed
     *
     * sometimes, when we change the model of the metric view logic,
     * we should repaint it on the cover and/or widget for apply
     * the changes, in this case we emit the signal and connected
     * object MUST recall the data-provide method create()
     */
    void changed();
protected:
    int m_minimumStep;
};


inline int QseAbstractMetricProvider::minimumStep() const
{
    return m_minimumStep;
}


#endif // QSEABSTRACTMETRICPROVIDER_H
