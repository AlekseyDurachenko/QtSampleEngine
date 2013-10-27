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
#ifndef QSECURSOR_H
#define QSECURSOR_H

#include <QObject>

class QseCursor : public QObject
{
    Q_OBJECT
public:
    explicit QseCursor(QObject *parent = 0);

    /*! \retval true if index() is "-1",
     *  \retval false oterwise
     */
    inline bool isNull() const;
    inline qint64 index() const;
    inline qint64 maximum() const;
signals:
    void changed();
public slots:
    void setMaximum(qint64 maximum);
    void setIndex(qint64 index);
    /*! This method is equal to setIndex(-1)
     */
    void reset();
private:
    qint64 m_index, m_maximum;
};


bool QseCursor::isNull() const
{
    return (m_index < 0);
}

qint64 QseCursor::index() const
{
    return m_index;
}

qint64 QseCursor::maximum() const
{
    return m_maximum;
}


#endif // QSECURSOR_H
