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
#include "qsesppwidget.h"
#include "qsemonocolorsppcoverplot.h"
#include "qsesppcursorplot.h"
#include "qsecursor.h"
#include "qsesppselectionplot.h"
#include "qseselection.h"


CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    m_sppWidget = new QseSppWidget(this);
    m_monocolorCoverSppPlot = new QseMonocolorSppCoverPlot(this);

    m_cursor = new QseCursor(this);
    m_cursor->setAvailableRange(QseRange(0, 1000));
    m_sppCursorPlot = new QseSppCursorPlot(this);
    m_sppCursorPlot->setCursor(m_cursor);

    m_selection = new QseSelection(this);
    m_selection->setAvailableRange(QseRange(0, 1000));
    m_sppSelectionPlot = new QseSppSelectionPlot(this);
    m_sppSelectionPlot->setSelection(m_selection);

    QList<QseAbstractSppPlot *> preUncachedPlots;
    preUncachedPlots << m_monocolorCoverSppPlot;

    QList<QseAbstractSppPlot *> postUncachedPlots;
    postUncachedPlots << m_sppSelectionPlot;
    postUncachedPlots << m_sppCursorPlot;

    m_sppWidget->setPreUncachedPlot(preUncachedPlots);
    m_sppWidget->setPostUncachedPlot(postUncachedPlots);
    setCentralWidget(m_sppWidget);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_action_Test_moncolorplot_triggered()
{
    m_monocolorCoverSppPlot->setColor(Qt::black);
}

void CMainWindow::on_actionAdd_cursor_triggered()
{
    if (m_cursor->isNull())
        m_cursor->setIndex(10);
    else
        m_cursor->setIndex(m_cursor->index()+15);

    m_sppCursorPlot->setProperty("pen", QPen(QColor(Qt::red)));
}

void CMainWindow::on_actionTest_Selection_triggered()
{
    m_selection->setSelectedRange(QseRange(10, 100));
}
