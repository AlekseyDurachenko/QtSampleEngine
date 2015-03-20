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
#ifndef QSEABSTRACTSPPSTANDARDCONTROLLER_H
#define QSEABSTRACTSPPSTANDARDCONTROLLER_H

#include "qseabstractsppcontroller.h"


class QseAbstractSppStandardController : public QseAbstractSppController
{
    Q_OBJECT
public:
    explicit QseAbstractSppStandardController(QObject *parent = 0);

    inline const Qt::MouseButtons &mouseButtons() const;
    void setMouseButtons(Qt::MouseButtons mouseButtons);

    inline const Qt::KeyboardModifiers &keyboardModifiers() const;
    void setKeyboardModifiers(Qt::KeyboardModifiers keyboardModifiers);
private:
    Qt::MouseButtons m_mouseButtons;
    Qt::KeyboardModifiers m_keyboardModifiers;
};

const Qt::MouseButtons &QseAbstractSppStandardController::mouseButtons() const
{
    return m_mouseButtons;
}

const Qt::KeyboardModifiers &QseAbstractSppStandardController::keyboardModifiers() const
{
    return m_keyboardModifiers;
}


#endif // QSEABSTRACTSPPSTANDARDCONTROLLER_H
