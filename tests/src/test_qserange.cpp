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
#include "test_qserange.h"
#include "qserange.h"
#include <QDebug>


TestQseRange::TestQseRange(QObject *parent) : QObject(parent)
{
}

void TestQseRange::constructor()
{
    {
        QseRange range;
        QVERIFY(range.first()       == -1
                && range.last()     == -1
                && range.isNull()   == true);
    }

    {
        QseRange range(-1, 1);
        QVERIFY(range.first()       == -1
                && range.last()     == -1
                && range.isNull()   == true);
    }

    {
        QseRange range(1, -1);
        QVERIFY(range.first()       == -1
                && range.last()     == -1
                && range.isNull()   == true);
    }

    {
        QseRange range(10, 1);
        QVERIFY(range.first()       == 1
                && range.last()     == 10
                && range.isNull()   == false);
    }

    {
        QseRange range(1, 10);
        QVERIFY(range.first()       == 1
                && range.last()     == 10
                && range.isNull()   == false);
    }

}

void TestQseRange::setFirst()
{
    {
        QseRange range;
        range.setFirst(10);
        QVERIFY(range.first()       == 10
                && range.last()     == 10
                && range.isNull()   == false);
    }

    {
        QseRange range(1, 20);
        range.setFirst(10);
        QVERIFY(range.first()       == 10
                && range.last()     == 20
                && range.isNull()   == false);
    }
}

void TestQseRange::setLast()
{
    {
        QseRange range;
        range.setLast(10);
        QVERIFY(range.first()       == 10
                && range.last()     == 10
                && range.isNull()   == false);
    }

    {
        QseRange range(1, 20);
        range.setLast(40);
        QVERIFY(range.first()       == 1
                && range.last()     == 40
                && range.isNull()   == false);
    }
}

void TestQseRange::replaceFirst()
{
    {
        QseRange range;
        range = range.replaceFirst(2);
        QVERIFY(range.first()       == -1
                && range.last()     == -1
                && range.isNull()   == true);
    }

    {
        QseRange range(1, 20);
        range = range.replaceFirst(2);
        QVERIFY(range.first()       == 2
                && range.last()     == 20
                && range.isNull()   == false);
    }

}

void TestQseRange::replaseLast()
{
    {
        QseRange range;
        range = range.replaceLast(2);
        QVERIFY(range.first()       == -1
                && range.last()     == -1
                && range.isNull()   == true);
    }

    {
        QseRange range(1, 20);
        range = range.replaceLast(2);
        QVERIFY(range.first()       == 1
                && range.last()     == 2
                && range.isNull()   == false);
    }

}

void TestQseRange::operator_eq()
{
    QseRange null;
    QseRange val_v1(1, 20);
    QseRange val_v2(9, 20);

    QVERIFY((null == null) == true);
    QVERIFY((val_v1 == val_v1) == true);
    QVERIFY((val_v1 == val_v2) == false);
    QVERIFY((val_v1 == null) == false);
}

void TestQseRange::operator_neq()
{
    QseRange null;
    QseRange val_v1(1, 20);
    QseRange val_v2(9, 20);

    QVERIFY((null != null) == false);
    QVERIFY((val_v1 != val_v1) == false);
    QVERIFY((val_v1 != val_v2) == true);
    QVERIFY((val_v1 != null) == true);
}
