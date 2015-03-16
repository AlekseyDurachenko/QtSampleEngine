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
#ifndef QSEABSTRACTPEAKREPLY_H
#define QSEABSTRACTPEAKREPLY_H

#include <QObject>
#include "qsepeakarray.h"


class QseAbstractPeakReply : public QObject
{
    Q_OBJECT
public:
    explicit QseAbstractPeakReply(QObject *parent = 0);

    inline int width() const;
    inline const QsePeakArray &peaks() const;
signals:
    void finished();
protected:
    void setWidth(int width);
    void setPeakArray(const QsePeakArray &peaks);
private:
    int m_width;
    QsePeakArray m_peaks;
};

int QseAbstractPeakReply::width() const
{
    return m_width;
}

const QsePeakArray &QseAbstractPeakReply::peaks() const
{
    return m_peaks;
}


#endif // QSEABSTRACTPEAKREPLY_H
