// Copyright (C) 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef TESTQSESPWGEOMETRY_H
#define TESTQSESPWGEOMETRY_H

#include <QObject>
#include <QtTest>


class TestQseSpwGeometry : public QObject
{
    Q_OBJECT
public:
    explicit TestQseSpwGeometry(QObject *parent = 0);
private slots:
    void constructor();
    void setX();
    void setY();
    void setSamplesPerWindow();
    void setHeight();
    void addX();
    void addY();
    void addSamplesPerWindow();
    void addHeight();
    void replaceX();
    void replaceY();
    void replaceSamplePerWindow();
    void replaceHeight();
    void operator_eq();
    void operator_neq();
};


#endif // TESTQSESPWGEOMETRY_H
