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
#ifndef CSPPASYNCAUDIOWIDGET_H
#define CSPPASYNCAUDIOWIDGET_H

#include <QWidget>
#include "qsesppwidget.h"
class QsePosition;
class QseSelection;
class QseSppPositionPlot;
class QseSppSelectionPlot;
class QseSppSignalCanvasPlot;
class QseSppAsyncSignalPlot;
class QseSppAxisCoverPlot;
class QseSppAudacityController;
class CSppAsyncPeakDataSource;
class CSppAsyncAudioLimiter;
class QseSppWidget;
class QseSppSignalLinearPlotDelegate;

class CSppAsyncAudioWidget : public QseSppWidget
{
    Q_OBJECT
public:
    explicit CSppAsyncAudioWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline QsePosition *playPosition() const;
    inline QsePosition *cursorPosition() const;
    inline QseSelection *selection() const;
    inline QseSppAxisCoverPlot *coverPlot() const;
    inline QseSppAsyncSignalPlot *signalPlot() const;
    inline QseSppAudacityController *controller() const;
    inline CSppAsyncPeakDataSource *dataSource() const;
    inline CSppAsyncAudioLimiter *limiter() const;
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
    QseSppSignalCanvasPlot *m_signalCanvasPlot;
    QseSppAsyncSignalPlot *m_signalPlot;
    QseSppSignalLinearPlotDelegate *m_plotDelegate;

    QseSppAudacityController *m_controller;

    CSppAsyncAudioLimiter *m_limiter;
    CSppAsyncPeakDataSource *m_dataSource;

    QseSppWidget *m_sppWidget;
};

QsePosition *CSppAsyncAudioWidget::playPosition() const
{
    return m_playPosition;
}

QsePosition *CSppAsyncAudioWidget::cursorPosition() const
{
    return m_cursorPosition;
}

QseSelection *CSppAsyncAudioWidget::selection() const
{
    return m_selection;
}

QseSppAxisCoverPlot *CSppAsyncAudioWidget::coverPlot() const
{
    return m_coverPlot;
}

QseSppAsyncSignalPlot *CSppAsyncAudioWidget::signalPlot() const
{
    return m_signalPlot;
}

QseSppAudacityController *CSppAsyncAudioWidget::controller() const
{
    return m_controller;
}

CSppAsyncPeakDataSource *CSppAsyncAudioWidget::dataSource() const
{
    return m_dataSource;
}

CSppAsyncAudioLimiter *CSppAsyncAudioWidget::limiter() const
{
    return m_limiter;
}


#endif // CSPPASYNCAUDIOWIDGET_H
