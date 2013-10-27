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
#include "qseselection.h"

QseSelection::QseSelection(QObject *parent) :
    QObject(parent)
{
    m_maximum = m_left = m_right = -1;
}

void QseSelection::setMaximum(qint64 maximum)
{
    m_maximum = maximum;
    setSelection(m_left, m_right);
}

void QseSelection::setSelection(qint64 left, qint64 right)
{
    if (left < -1)
        left = -1;
    else if (left > m_maximum)
        left = m_maximum;

    if (right < -1)
        right = -1;
    else if (right > m_maximum)
        right = m_maximum;

    if (left > right)
        qSwap(left, right);

    if (m_left != left || m_right != right)
    {
        m_left = left;
        m_right = right;
        emit changed();
    }
}

void QseSelection::reset()
{
    setSelection(-1, -1);
}
