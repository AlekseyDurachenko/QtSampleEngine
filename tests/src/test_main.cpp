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
#include <QtTest>
#include "test_qserange.h"
#include "test_qseposition.h"
#include "test_qseselection.h"
#include "test_qsesppgeometry.h"
#include "test_qsespwgeometry.h"
#include "test_qsepeakarray.h"


int main(int argc, char *argv[])
{
    if (QTest::qExec(new TestQseRange, argc, argv))
        return -1;
    if (QTest::qExec(new TestQsePosition, argc, argv))
        return -1;
    if (QTest::qExec(new TestQseSelection, argc, argv))
        return -1;
    if (QTest::qExec(new TestQseSppGeometry, argc, argv))
        return -1;
    if (QTest::qExec(new TestQseSpwGeometry, argc, argv))
        return -1;
    if (QTest::qExec(new TestQsePeakArray, argc, argv))
        return -1;

    return 0;
}
