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
#include "test_qseposition.h"
#include "qseposition.h"
#include <QSharedPointer>
#include <QDebug>


TestQsePosition::TestQsePosition(QObject *parent) : QObject(parent)
{
}

void TestQsePosition::setAvailableRange()
{
    QSharedPointer<QsePosition> cursor
            = QSharedPointer<QsePosition>(new QsePosition);

    cursor->setAvailableRange(QseRange(10, 20));
    QVERIFY(cursor->availableRange() == QseRange(10, 20));

    cursor->setAvailableRange(QseRange());
    QVERIFY(cursor->availableRange().isNull());
}

void TestQsePosition::setIndex()
{
    QSharedPointer<QsePosition> cursor
            = QSharedPointer<QsePosition>(new QsePosition);

    cursor->setAvailableRange(QseRange(0, 20));
    cursor->setIndex(0);
    QVERIFY(cursor->index() == 0);
    cursor->setIndex(10);
    QVERIFY(cursor->index() == 10);
    cursor->setIndex(20);
    QVERIFY(cursor->index() == 20);
    cursor->setIndex(-5);
    QVERIFY(cursor->index() == 0);
    cursor->setIndex(25);
    QVERIFY(cursor->index() == 20);

    cursor->resetAvailableRange();
    QVERIFY(cursor->isNull() == true);
    cursor->setIndex(5);
    QVERIFY(cursor->isNull() == true);
    cursor->setIndex(-5);
    QVERIFY(cursor->isNull() == true);
}

void TestQsePosition::resetIndex()
{
    QSharedPointer<QsePosition> cursor
            = QSharedPointer<QsePosition>(new QsePosition);

    cursor->setAvailableRange(QseRange(0, 20));
    cursor->setIndex(10);
    cursor->resetIndex();
    QVERIFY(cursor->isNull() == true);
}

void TestQsePosition::resetAvailableRange()
{
    QSharedPointer<QsePosition> cursor
            = QSharedPointer<QsePosition>(new QsePosition);

    cursor->setAvailableRange(QseRange(0, 20));
    cursor->setIndex(10);
    cursor->resetAvailableRange();
    QVERIFY(cursor->isNull() == true && cursor->availableRange().isNull());
}
