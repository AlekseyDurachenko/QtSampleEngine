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
#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include <QMainWindow>
class CComplexMonoAudioWidget;


namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    virtual ~CMainWindow();

private slots:
    void on_action_Open_triggered();
    void on_action_Quit_triggered();
    void openSoundFile(const QString &fileName);

private:
    bool readSoundFile(const QString &fileName, float **data, qint64 *count, double *sampleRage);

private:
    Ui::CMainWindow *ui;
    CComplexMonoAudioWidget *m_monoAudioWidget;
};


#endif // CMAINWINDOW_H