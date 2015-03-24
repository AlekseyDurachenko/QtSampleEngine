// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef CSPPSYNCAUDACITYWIDGET_H
#define CSPPSYNCAUDACITYWIDGET_H

#include <QWidget>
#include "qsesppwidget.h"
class QseCursor;
class QseSelection;
class QseSppCursorPlot;
class QseSppSelectionPlot;
class QseSppSyncSignalLinearPlot;
class QseSppAxisCoverPlot;
class QseSppAudacityController;
class CSppSyncDataSource;
class CSppLimiter;
class QseSppWidget;


class CSppSyncAudacityWidget : public QseSppWidget
{
    Q_OBJECT
public:
    explicit CSppSyncAudacityWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline QseCursor *playPosition() const;
    inline QseCursor *currentPosition() const;
    inline QseSelection *selection() const;
    inline QseSppAxisCoverPlot *coverPlot() const;
    inline QseSppSyncSignalLinearPlot *signalPlot() const;
    inline QseSppAudacityController *controller() const;
    inline CSppSyncDataSource *dataSource() const;
    inline CSppLimiter *limiter() const;
private:
    QseCursor *m_playPosition;
    QseSppCursorPlot *m_playPositionPlot;

    QseCursor *m_currentPosition;
    QseSppCursorPlot *m_currentPositionPlot;

    QseSelection *m_selection;
    QseSppSelectionPlot *m_selectionPlot;

    QseSppAxisCoverPlot *m_coverPlot;
    QseSppSyncSignalLinearPlot *m_signalPlot;

    QseSppAudacityController *m_controller;

    CSppLimiter *m_limiter;
    CSppSyncDataSource *m_dataSource;

    QseSppWidget *m_sppWidget;
};

QseCursor *CSppSyncAudacityWidget::playPosition() const
{
    return m_playPosition;
}

QseCursor *CSppSyncAudacityWidget::currentPosition() const
{
    return m_currentPosition;
}

QseSelection *CSppSyncAudacityWidget::selection() const
{
    return m_selection;
}

QseSppAxisCoverPlot *CSppSyncAudacityWidget::coverPlot() const
{
    return m_coverPlot;
}

QseSppSyncSignalLinearPlot *CSppSyncAudacityWidget::signalPlot() const
{
    return m_signalPlot;
}

QseSppAudacityController *CSppSyncAudacityWidget::controller() const
{
    return m_controller;
}

CSppSyncDataSource *CSppSyncAudacityWidget::dataSource() const
{
    return m_dataSource;
}

CSppLimiter *CSppSyncAudacityWidget::limiter() const
{
    return m_limiter;
}


#endif // CSPPSYNCAUDACITYWIDGET_H
