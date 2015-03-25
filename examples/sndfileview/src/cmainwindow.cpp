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
#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "ccomplexmonoaudiowidget.h"
#include "csppsyncaudiowidget.h"
#include "csppsyncpeakdatasource.h"


CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_monoAudioWidget = new CComplexMonoAudioWidget(this);
    setCentralWidget(m_monoAudioWidget);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_action_Test_moncolorplot_triggered()
{
    // TEMPORARY_START
    QVector<double> datasamples(100000);
    for (int i = 0; i < 100000; ++i)
        datasamples[i] = (qrand()%100000)/100000.0-0.5;
    // TEMPORARY_END

    m_monoAudioWidget->audioWidget()->dataSource()->setSamples(datasamples, 44100);


    //m_monocolorCoverSppPlot->setColor(Qt::black);
}
