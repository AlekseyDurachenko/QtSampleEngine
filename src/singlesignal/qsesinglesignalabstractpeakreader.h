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
#ifndef QSESINGLESIGNALABSTRACTPEAKREADER_H
#define QSESINGLESIGNALABSTRACTPEAKREADER_H

#include <QObject>
#include "qsegeometry.h"

class QseSingleSignalAbstractPeakReader : public QObject
{
    Q_OBJECT
public:
    explicit QseSingleSignalAbstractPeakReader(QObject *parent = 0);

    virtual void abort() = 0;
    virtual int start(const QseGeometry &geometry, int width) = 0;

signals:
    void peakReaded(int id, const QseGeometry &geometry, QList<float> minimums, QList<float> maximums);

};

#endif // QSESINGLESIGNALABSTRACTPEAKREADER_H
