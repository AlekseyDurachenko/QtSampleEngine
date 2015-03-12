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
#include "test_qsesppgeometry.h"
#include "qsesppgeometry.h"
#include <QDebug>


TestQseSppGeometry::TestQseSppGeometry(QObject *parent) : QObject(parent)
{
}

void TestQseSppGeometry::constructor()
{
    QseSppGeometry g(1, 2.0, 3, 4.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 2.0
            && g.samplesPerPixel()  == 3
            && g.height()           == 4.0);
}

void TestQseSppGeometry::setX()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g.setX(10);
    QVERIFY(g.x()                   == 10
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::setY()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g.setY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 10.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::setSamplesPerPixel()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);

    g.setSamplesPerPixel(-10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -10
            && g.height()           == 1.0);

    g.setSamplesPerPixel(-1);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);

    g.setSamplesPerPixel(0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == 2
            && g.height()           == 1.0);

    g.setSamplesPerPixel(1);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);

    g.setSamplesPerPixel(2);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == 2
            && g.height()           == 1.0);

    g.setSamplesPerPixel(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == 10
            && g.height()           == 1.0);}

void TestQseSppGeometry::setHeight()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g.setHeight(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 10.0);
}

void TestQseSppGeometry::addX()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.addX(10);
    QVERIFY(g.x()                   == 11
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::addY()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.addY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 11.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::addSamplesPerPixel()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.addSamplesPerPixel(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == 9
            && g.height()           == 1.0);

}

void TestQseSppGeometry::addHeight()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.addHeight(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 11.0);
}

void TestQseSppGeometry::replaceX()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.replaceX(10);
    QVERIFY(g.x()                   == 10
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::replaceY()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.replaceY(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 10.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 1.0);
}

void TestQseSppGeometry::replaceSamplePerPixel()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.replaceSamplesPerPixel(10);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == 10
            && g.height()           == 1.0);
}

void TestQseSppGeometry::replaceHeight()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    g = g.replaceHeight(10.0);
    QVERIFY(g.x()                   == 1
            && g.y()                == 1.0
            && g.samplesPerPixel()  == -1
            && g.height()           == 10.0);
}

void TestQseSppGeometry::toRealSamplesPerPixel()
{
    QseSppGeometry g(1, 1.0, -1, 1.0);
    QVERIFY(g.toRealSamplesPerPixel() == 1.0);
    g.setSamplesPerPixel(-2);
    QVERIFY(g.toRealSamplesPerPixel() == 0.5);
    g.setSamplesPerPixel(-4);
    QVERIFY(g.toRealSamplesPerPixel() == 0.25);
    g.setSamplesPerPixel(2);
    QVERIFY(g.toRealSamplesPerPixel() == 2.0);
    g.setSamplesPerPixel(4);
    QVERIFY(g.toRealSamplesPerPixel() == 4.0);
}

void TestQseSppGeometry::operator_eq()
{
    QseSppGeometry g_01(1, 1.0, -1, 1.0);
    QseSppGeometry g_02(2, 2.0, -2, 1.0);

    QVERIFY((g_01 == g_02) == false);
    QVERIFY((g_01 == g_01) == true);
}

void TestQseSppGeometry::operator_neq()
{
    QseSppGeometry g_01(1, 1.0, -1, 1.0);
    QseSppGeometry g_02(2, 2.0, -2, 1.0);

    QVERIFY((g_01 != g_02) == true);
    QVERIFY((g_01 != g_01) == false);
}

void TestQseSppGeometry::checkSampleIndexVisibility()
{
    QseSppGeometry g_01(   0, 1.0, -4, 1.0);
    QseSppGeometry g_02( 100, 1.0, -4, 1.0);
    QseSppGeometry g_03(   0, 1.0, -1, 1.0);
    QseSppGeometry g_04( 100, 1.0, -1, 1.0);
    QseSppGeometry g_05(   0, 1.0, 40, 1.0);
    QseSppGeometry g_06( 100, 1.0, 40, 1.0);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_01, 0, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_02, 0, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_03, 0, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_04, 0, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 0, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 0, 100) == false);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_01, 10, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_02, 10, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_03, 10, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_04, 10, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 10, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 10, 100) == false);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_01, 100, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_02, 100, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_03, 100, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_04, 100, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 100, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 100, 100) == true);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_01, 200, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_02, 200, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_03, 200, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_04, 200, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 200, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 200, 100) == true);


    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 3999, 100) == true);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 3999, 100) == true);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 4000, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 4000, 100) == true);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_05, 4100, 100) == false);
    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 4099, 100) == true);

    QVERIFY(QseSppGeometry::checkSampleIndexVisibility(g_06, 4100, 100) == false);
}

void TestQseSppGeometry::calcOffset()
{
    QseSppGeometry g_01(   0, 1.0, -4, 1.0);
    QseSppGeometry g_02( 100, 1.0, -4, 1.0);
    QseSppGeometry g_03(   0, 1.0, -1, 1.0);
    QseSppGeometry g_04( 100, 1.0, -1, 1.0);
    QseSppGeometry g_05(   0, 1.0, 40, 1.0);
    QseSppGeometry g_06( 100, 1.0, 40, 1.0);

    QVERIFY(QseSppGeometry::calcOffset(g_01, 0) == 0);
    QVERIFY(QseSppGeometry::calcOffset(g_02, 0) == -400);
    QVERIFY(QseSppGeometry::calcOffset(g_03, 0) == 0);
    QVERIFY(QseSppGeometry::calcOffset(g_04, 0) == -100);
    QVERIFY(QseSppGeometry::calcOffset(g_05, 0) == 0);
    QVERIFY(QseSppGeometry::calcOffset(g_06, 0) == -2);

    QVERIFY(QseSppGeometry::calcOffset(g_01, 10) == 40);
    QVERIFY(QseSppGeometry::calcOffset(g_02, 10) == -360);
    QVERIFY(QseSppGeometry::calcOffset(g_03, 10) == 10);
    QVERIFY(QseSppGeometry::calcOffset(g_04, 10) == -90);
    QVERIFY(QseSppGeometry::calcOffset(g_05, 10) == 0);
    QVERIFY(QseSppGeometry::calcOffset(g_06, 10) == -2);

    QVERIFY(QseSppGeometry::calcOffset(g_01, 1000) == 4000);
    QVERIFY(QseSppGeometry::calcOffset(g_02, 1000) == 3600);
    QVERIFY(QseSppGeometry::calcOffset(g_03, 1000) == 1000);
    QVERIFY(QseSppGeometry::calcOffset(g_04, 1000) == 900);
    QVERIFY(QseSppGeometry::calcOffset(g_05, 1000) == 25);
    QVERIFY(QseSppGeometry::calcOffset(g_06, 1000) == 22);
}

void TestQseSppGeometry::calcSampleIndex()
{
    QseSppGeometry g_01(   0, 1.0, -4, 1.0);
    QseSppGeometry g_02( 100, 1.0, -4, 1.0);
    QseSppGeometry g_03(   0, 1.0, -1, 1.0);
    QseSppGeometry g_04( 100, 1.0, -1, 1.0);
    QseSppGeometry g_05(   0, 1.0, 40, 1.0);
    QseSppGeometry g_06( 100, 1.0, 40, 1.0);

    QVERIFY(QseSppGeometry::calcSampleIndex(g_01, 0) == 0);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_02, 0) == 100);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_03, 0) == 0);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_04, 0) == 100);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_05, 0) == 0);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_06, 0) == 100);

    QVERIFY(QseSppGeometry::calcSampleIndex(g_01, 10) == 3);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_02, 10) == 103);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_03, 10) == 10);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_04, 10) == 110);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_05, 10) == 400);
    QVERIFY(QseSppGeometry::calcSampleIndex(g_06, 10) == 500);
}
