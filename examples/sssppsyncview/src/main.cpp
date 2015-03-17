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
#include <QApplication>
#include "cmainwindow.h"
#include "csppsyncdatasource.h"
#include <QDebug>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QVector<double> datasamples(1000);
    for (int i = 0; i < 1000; ++i)
        datasamples[i] = (qrand()%1000)/1000.0-0.5;
    CSppSyncDataSource *dataSource = new CSppSyncDataSource(datasamples);

    CMainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
