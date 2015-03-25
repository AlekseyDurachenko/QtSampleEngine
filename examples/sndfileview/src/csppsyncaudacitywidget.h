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
class QsePosition;
class QseSelection;
class QseSppPositionPlot;
class QseSppSelectionPlot;
class QseSppSyncSignalLinearPlot;
class QseSppAxisCoverPlot;
class QseSppAudacityController;
class CSppSyncPeakDataSource;
class CSppSyncAudacityLimiter;
class QseSppWidget;


class CSppSyncAudacityWidget : public QseSppWidget
{
    Q_OBJECT
public:
    explicit CSppSyncAudacityWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline QsePosition *playPosition() const;
    inline QsePosition *cursorPosition() const;
    inline QseSelection *selection() const;
    inline QseSppAxisCoverPlot *coverPlot() const;
    inline QseSppSyncSignalLinearPlot *signalPlot() const;
    inline QseSppAudacityController *controller() const;
    inline CSppSyncPeakDataSource *dataSource() const;
    inline CSppSyncAudacityLimiter *limiter() const;
private slots:
    void dataSource_dataChanged();
private:
    QsePosition *m_playPosition;
    QseSppPositionPlot *m_playPositionPlot;

    QsePosition *m_cursorPosition;
    QseSppPositionPlot *m_cursorPositionPlot;

    QseSelection *m_selection;
    QseSppSelectionPlot *m_selectionPlot;

    QseSppAxisCoverPlot *m_coverPlot;
    QseSppSyncSignalLinearPlot *m_signalPlot;

    QseSppAudacityController *m_controller;

    CSppSyncAudacityLimiter *m_limiter;
    CSppSyncPeakDataSource *m_dataSource;

    QseSppWidget *m_sppWidget;
};

QsePosition *CSppSyncAudacityWidget::playPosition() const
{
    return m_playPosition;
}

QsePosition *CSppSyncAudacityWidget::cursorPosition() const
{
    return m_cursorPosition;
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

CSppSyncPeakDataSource *CSppSyncAudacityWidget::dataSource() const
{
    return m_dataSource;
}

CSppSyncAudacityLimiter *CSppSyncAudacityWidget::limiter() const
{
    return m_limiter;
}


#endif // CSPPSYNCAUDACITYWIDGET_H
