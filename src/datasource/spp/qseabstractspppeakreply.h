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
#ifndef QSEABSTRACTSPPPEAKREPLY_H
#define QSEABSTRACTSPPPEAKREPLY_H

#include "qseabstractpeakreply.h"
#include "qsespppeakrequest.h"


class QseAbstractSppPeakReply : public QseAbstractPeakReply
{
    Q_OBJECT
public:
    explicit QseAbstractSppPeakReply(const QseSppPeakRequest &request,
                                     QObject *parent = 0);
signals:
    void aborted(const QseSppPeakRequest &request);
    void finished(const QsePeakArray &peaks, const QseSppPeakRequest &request);
protected:
    inline const QseSppPeakRequest &request() const;

    inline const QsePeakArray &peaks() const;
    void setPeaks(const QsePeakArray &peaks);
protected:
    virtual void doSuccess();
    virtual void doAbort();
private:
    QseSppPeakRequest m_request;
    QsePeakArray m_peaks;
};

const QseSppPeakRequest &QseAbstractSppPeakReply::request() const
{
    return m_request;
}

const QsePeakArray &QseAbstractSppPeakReply::peaks() const
{
    return m_peaks;
}


#endif // QSEABSTRACTSPPPEAKREPLY_H
