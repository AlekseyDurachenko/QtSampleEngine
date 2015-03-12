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
#ifndef QSESELECTION_H
#define QSESELECTION_H

#include <QObject>
#include "qserange.h"


class QseSelection : public QObject
{
    Q_OBJECT
public:
    explicit QseSelection(QObject *parent = 0);

    inline bool isNull() const;
    inline const QseRange &availableRange() const;
    inline const QseRange &selectedRange() const;
signals:
    void changed();
public slots:
    void setAvailableRange(const QseRange &availableRange);
    void setSelectedRange(const QseRange &selectedRange);
    void resetAvailableRange();
    void resetSelectedRange();
private:
    QseRange m_availableRange;
    QseRange m_selectedRange;
};

/*! \retval true if left() or right() is "-1" or left() == right()
 *  \retval false oterwise
 */
bool QseSelection::isNull() const
{
    return m_selectedRange.isNull() || (m_selectedRange.count() == 0);
}


#endif // QSESELECTION_H
