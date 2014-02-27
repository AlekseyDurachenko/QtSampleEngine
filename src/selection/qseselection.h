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
#ifndef QSESELECTION_H
#define QSESELECTION_H

#include <QObject>

class QseSelection : public QObject
{
    Q_OBJECT
public:
    explicit QseSelection(QObject *parent = 0);    
    /*! \retval true if left() or right() is "-1" or left() == right()
     *  \retval false oterwise
     */
    inline bool isNull() const;
    inline qint64 left() const;
    inline qint64 right() const;
    inline qint64 count() const;
    inline qint64 maximum() const;
signals:    
    void changed();
public slots:
    void setMaximum(qint64 maximum);
    void setSelection(qint64 left, qint64 right);
    /*! This method is equal to setSelection(-1, -1)
     */
    void reset();
private:
    qint64 m_index, m_maximum, m_left, m_right;
};


bool QseSelection::isNull() const
{
    return (m_left == -1 || m_right == -1 || m_left == m_right);
}

qint64 QseSelection::left() const
{
    return m_left;
}

qint64 QseSelection::right() const
{
    return m_right;
}

qint64 QseSelection::count() const
{
    if (isNull())
    {
        return 0;
    }
    else
    {
        return m_right - m_left;
    }
}

qint64 QseSelection::maximum() const
{
    return m_maximum;
}


#endif // QSESELECTION_H
