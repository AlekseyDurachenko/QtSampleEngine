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
#ifndef QSEPOSITION_H
#define QSEPOSITION_H

#include <QObject>
#include "qserange.h"


class QsePosition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 index READ index WRITE setIndex
               RESET resetIndex)
    Q_PROPERTY(QseRange availableRange READ availableRange
               WRITE setAvailableRange RESET resetAvailableRange)
public:
    explicit QsePosition(QObject *parent = 0);

    inline bool isNull() const;
    inline qint64 index() const;
    inline const QseRange &availableRange() const;
signals:
    void indexChanged();
public slots:
    void setAvailableRange(const QseRange &range);
    void setIndex(qint64 index);
    void resetAvailableRange();
    void resetIndex();
private:
    qint64 m_index;
    QseRange m_availableRange;
};

/*! \retval true if index() is "-1",
 *  \retval false oterwise
 */
bool QsePosition::isNull() const
{
    return (m_index < 0);
}

qint64 QsePosition::index() const
{
    return m_index;
}

const QseRange &QsePosition::availableRange() const
{
    return m_availableRange;
}


#endif // QSEPOSITION_H
