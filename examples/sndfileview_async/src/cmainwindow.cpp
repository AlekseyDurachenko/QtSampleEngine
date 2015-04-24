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
#include <QFileDialog>
#include <QMessageBox>
#include <sndfile.h>
#include "ccomplexmonoaudiowidget.h"
#include "csppasyncaudiowidget.h"
#include "csppasyncpeakdatasource.h"


CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sound File View"));

    m_monoAudioWidget = new CComplexMonoAudioWidget(this);
    setCentralWidget(m_monoAudioWidget);

    QString fileName = QDir::homePath() + QDir::separator() + "example.wav";
    if (QFileInfo(fileName).exists())
        QMetaObject::invokeMethod(this, "openSoundFile", Qt::QueuedConnection,
                Q_ARG(QString, fileName));
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Sound File"), "", tr("Sound Files (* *.*)"));

    if (fileName.isEmpty())
        return;

    openSoundFile(fileName);
}

void CMainWindow::on_action_Quit_triggered()
{
    close();
}

void CMainWindow::openSoundFile(const QString &fileName)
{
    double sampleRate;
    QVector<double> data = readSoundFile(fileName, &sampleRate);
    //QVector<double> data(1000000);
    //for (int i = 0; i < 1000000; ++i)
    //    data[i] = i%1000/1000.0-0.5;

    if (data.isEmpty())
    {
        QMessageBox::critical(this, tr("Critical"),
                              tr("Sound format not support"));
    }
    else
    {
        setWindowTitle(fileName + tr(" - Sound File View"));

        m_monoAudioWidget->audioWidget()->dataSource()->setSamples(data, sampleRate);
        QseSppGeometry geometry;
        geometry.setHeight(2.6);
        if (data.count() > m_monoAudioWidget->audioWidget()->width()*2)
            geometry.setSamplesPerPixel(
                    data.count()/m_monoAudioWidget->audioWidget()->width());

        m_monoAudioWidget->audioWidget()->setGeometry(geometry);
    }
}


QVector<double> CMainWindow::readSoundFile(const QString &fileName,
        double *sampleRage)
{
    SNDFILE *infile;
    SF_INFO sfinfo;
    int readcount;

    if ((infile = sf_open(fileName.toLatin1().data(), SFM_READ, &sfinfo)))
    {
        if (sampleRage)
            *sampleRage = sfinfo.samplerate;

        double data[1024];

        QVector<double> result;
        result.reserve(sfinfo.frames);

        while ((readcount = sf_read_double(infile, data, 1024)))
            for (int i = 0; i < readcount; i += sfinfo.channels)
                result.push_back(data[i]);

        return result;
    }

    sf_close(infile);

    return QVector<double>();
}
