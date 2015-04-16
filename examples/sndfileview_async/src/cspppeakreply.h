// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef CSPPPEAKREPLY_H
#define CSPPPEAKREPLY_H

#include "qseabstractspppeakreply.h"


class CSppPeakReply : public QseAbstractSppPeakReply
{
    Q_OBJECT
public:
    explicit CSppPeakReply(const QVector<double> &samples,
                           const QseSppPeakRequest &request,
                           QObject *parent = 0);
protected:
    virtual void algorithm();
private:
    QsePeakArray readPeaks(const QseSppPeakRequest &req);
    QsePeakArray readAsLines(qint64 first, qint64 pps, int width);
    QsePeakArray readAsPeaks(qint64 first, qint64 spp, int width,
                             bool rightAligh = false);
private:
    QVector<double> m_samples;
};


#endif // CSPPPEAKREPLY_H
