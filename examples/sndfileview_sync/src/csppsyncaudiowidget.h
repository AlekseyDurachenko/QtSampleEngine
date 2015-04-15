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
#ifndef CSPPSYNCAUDIOWIDGET_H
#define CSPPSYNCAUDIOWIDGET_H

#include <QWidget>
#include "qsesppwidget.h"
class QsePosition;
class QseSelection;
class QseSppPositionPlot;
class QseSppSelectionPlot;
class QseSppSyncSignalPlot;
class QseSppAxisCoverPlot;
class QseSppAudacityController;
class CSppSyncPeakDataSource;
class CSppSyncAudioLimiter;
class QseSppWidget;
class QseSppSignalLinearPlotDelegate;


class CSppSyncAudioWidget : public QseSppWidget
{
    Q_OBJECT
public:
    explicit CSppSyncAudioWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline QsePosition *playPosition() const;
    inline QsePosition *cursorPosition() const;
    inline QseSelection *selection() const;
    inline QseSppAxisCoverPlot *coverPlot() const;
    inline QseSppSyncSignalPlot *signalPlot() const;
    inline QseSppAudacityController *controller() const;
    inline CSppSyncPeakDataSource *dataSource() const;
    inline CSppSyncAudioLimiter *limiter() const;
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
    QseSppSyncSignalPlot *m_signalPlot;
    QseSppSignalLinearPlotDelegate *m_plotDelegate;

    QseSppAudacityController *m_controller;

    CSppSyncAudioLimiter *m_limiter;
    CSppSyncPeakDataSource *m_dataSource;

    QseSppWidget *m_sppWidget;
};

QsePosition *CSppSyncAudioWidget::playPosition() const
{
    return m_playPosition;
}

QsePosition *CSppSyncAudioWidget::cursorPosition() const
{
    return m_cursorPosition;
}

QseSelection *CSppSyncAudioWidget::selection() const
{
    return m_selection;
}

QseSppAxisCoverPlot *CSppSyncAudioWidget::coverPlot() const
{
    return m_coverPlot;
}

QseSppSyncSignalPlot *CSppSyncAudioWidget::signalPlot() const
{
    return m_signalPlot;
}

QseSppAudacityController *CSppSyncAudioWidget::controller() const
{
    return m_controller;
}

CSppSyncPeakDataSource *CSppSyncAudioWidget::dataSource() const
{
    return m_dataSource;
}

CSppSyncAudioLimiter *CSppSyncAudioWidget::limiter() const
{
    return m_limiter;
}


#endif // CSPPSYNCAUDIOWIDGET_H
