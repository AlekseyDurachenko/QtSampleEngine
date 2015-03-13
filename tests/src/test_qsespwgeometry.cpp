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
#include "test_qsespwgeometry.h"
#include "qsespwgeometry.h"
#include <QDebug>


TestQseSpwGeometry::TestQseSpwGeometry(QObject *parent) : QObject(parent)
{
}

void TestQseSpwGeometry::constructor()
{
    QseSpwGeometry g(1, 2.0, 3, 4.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 2.0
            && g.samplesPerWindow() == 3
            && g.height()           == 4.0);
}

void TestQseSpwGeometry::setX()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g.setX(10);
    QVERIFY(g.x()                   == 10
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::setY()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g.setY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 10.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::setSamplesPerWindow()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g.setSamplesPerWindow(0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
    g.setSamplesPerWindow(-10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
    g.setSamplesPerWindow(2);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 2
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::setHeight()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g.setHeight(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 10.0);
}

void TestQseSpwGeometry::addX()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.addX(10);
    QVERIFY(g.x()                   == 11
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::addY()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.addY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 11.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::addSamplesPerWindow()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.addSamplesPerWindow(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 11
            && g.height()           == 1.0);
    g = g.addSamplesPerWindow(-100);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::addHeight()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.addHeight(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 11.0);
}

void TestQseSpwGeometry::replaceX()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.replaceX(10);
    QVERIFY(g.x()                   == 10
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::replaceY()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.replaceY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 10.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::replaceSamplePerWindow()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.replaceSamplesPerWindow(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 10
            && g.height()           == 1.0);
    g = g.replaceSamplesPerWindow(-10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 1.0);
}

void TestQseSpwGeometry::replaceHeight()
{
    QseSpwGeometry g(1, 1.0, 1, 1.0);
    g = g.replaceHeight(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerWindow() == 1
            && g.height()           == 10.0);
}

void TestQseSpwGeometry::operator_eq()
{
    QseSpwGeometry g_01(1, 1.0, 1, 1.0);
    QseSpwGeometry g_02(2, 2.0, 2, 1.0);

    QVERIFY((g_01 == g_02) == false);
    QVERIFY((g_01 == g_01) == true);
}

void TestQseSpwGeometry::operator_neq()
{
    QseSpwGeometry g_01(1, 1.0, 1, 1.0);
    QseSpwGeometry g_02(2, 2.0, 2, 1.0);

    QVERIFY((g_01 != g_02) == true);
    QVERIFY((g_01 != g_01) == false);
}
