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
#include "test_qseselection.h"
#include "qseselection.h"
#include <QSharedPointer>
#include <QDebug>


TestQseSelection::TestQseSelection(QObject *parent)
    : QObject(parent)
{
}

void TestQseSelection::setAvailableRange()
{
    QSharedPointer<QseSelection> selection = QSharedPointer<QseSelection>(new QseSelection);

    selection->setAvailableRange(QseRange(10, 20));
    QVERIFY(selection->availableRange() == QseRange(10, 20));

    selection->setAvailableRange(QseRange());
    QVERIFY(selection->availableRange().isNull());
}

void TestQseSelection::setSelectedRange()
{
    QSharedPointer<QseSelection> selection = QSharedPointer<QseSelection>(new QseSelection);

    selection->setAvailableRange(QseRange());
    selection->setSelectedRange(QseRange());
    QVERIFY(selection->selectedRange().isNull());
    selection->setSelectedRange(QseRange(0, 10));
    QVERIFY(selection->selectedRange().isNull());

    selection->setAvailableRange(QseRange(10, 99));
    selection->setSelectedRange(QseRange());
    QVERIFY(selection->selectedRange().isNull());
    selection->setSelectedRange(QseRange(10, 40));
    QVERIFY(selection->selectedRange() == QseRange(10, 40));
    selection->setSelectedRange(QseRange(0, 40));
    QVERIFY(selection->selectedRange() == QseRange(10, 40));
    selection->setSelectedRange(QseRange(20, 200));
    QVERIFY(selection->selectedRange() == QseRange(20, 99));
    selection->setSelectedRange(QseRange(0, 200));
    QVERIFY(selection->selectedRange() == QseRange(10, 99));
}

void TestQseSelection::resetAvailableRange()
{
    QSharedPointer<QseSelection> selection = QSharedPointer<QseSelection>(new QseSelection);

    selection->setAvailableRange(QseRange(10, 99));
    selection->setSelectedRange(QseRange(0, 100));
    selection->resetAvailableRange();
    QVERIFY(selection->availableRange().isNull()
            && selection->selectedRange().isNull());
}

void TestQseSelection::resetSelectedRange()
{
    QSharedPointer<QseSelection> selection = QSharedPointer<QseSelection>(new QseSelection);

    selection->setAvailableRange(QseRange(10, 99));
    selection->setSelectedRange(QseRange(0, 100));
    selection->resetSelectedRange();
    QVERIFY(selection->availableRange() == QseRange(10, 99)
            && selection->selectedRange().isNull());
}
