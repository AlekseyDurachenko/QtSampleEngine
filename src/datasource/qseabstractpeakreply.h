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

    inline bool isAborted() const;
    inline bool isWorking() const;
    void abort();
public slots:
    void start();
private slots:
    void slot_started();
protected:
    virtual void doSuccess() = 0;
    virtual void doAbort() = 0;
    virtual void doAlgorithm() = 0;
private:
    volatile bool m_isAborted;
    volatile bool m_isWorking;
};

bool QseAbstractPeakReply::isAborted() const
{
    return m_isAborted;
}

bool QseAbstractPeakReply::isWorking() const
{
    return m_isWorking;
}


#endif // QSEABSTRACTPEAKREPLY_H
