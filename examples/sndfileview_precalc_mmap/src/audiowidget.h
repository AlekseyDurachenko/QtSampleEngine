// Copyright 2015-2016, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H


#include <QWidget>
#include "qsewidget.h"
class QsePosition;
class QseSelection;
class QsePositionPlot;
class QseSelectionPlot;
class QseSignalCanvasPlot;
class QseSignalPlot;
class QseAxisCanvasPlot;
class QseAudacityController;
class SignalDataSource;
class AudioLimiter;
class QseWidget;
class QseSignalLinearPlotDelegate;


class AudioWidget : public QseWidget
{
    Q_OBJECT
public:
    explicit AudioWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);

    inline QsePosition *playPosition() const;
    inline QsePosition *cursorPosition() const;
    inline QseSelection *selection() const;
    inline QseAxisCanvasPlot *canvasPlot() const;
    inline QseSignalCanvasPlot *signalCanvasPlot() const;
    inline QseSignalPlot *signalPlot() const;
    inline QseAudacityController *controller() const;
    inline SignalDataSource *dataSource() const;
    inline AudioLimiter *limiter() const;

private slots:
    void dataSource_dataChanged();

private:
    QsePosition *m_playPosition;
    QsePositionPlot *m_playPositionPlot;

    QsePosition *m_cursorPosition;
    QsePositionPlot *m_cursorPositionPlot;

    QseSelection *m_selection;
    QseSelectionPlot *m_selectionPlot;

    QseAxisCanvasPlot *m_canvasPlot;
    QseSignalCanvasPlot *m_signalCanvasPlot;
    QseSignalPlot *m_signalPlot;
    QseSignalLinearPlotDelegate *m_plotDelegate;

    QseAudacityController *m_controller;

    AudioLimiter *m_limiter;
    SignalDataSource *m_dataSource;

    QseWidget *m_sppWidget;
};

QsePosition *AudioWidget::playPosition() const
{
    return m_playPosition;
}

QsePosition *AudioWidget::cursorPosition() const
{
    return m_cursorPosition;
}

QseSelection *AudioWidget::selection() const
{
    return m_selection;
}

QseAxisCanvasPlot *AudioWidget::canvasPlot() const
{
    return m_canvasPlot;
}

QseSignalCanvasPlot *AudioWidget::signalCanvasPlot() const
{
    return m_signalCanvasPlot;
}

QseSignalPlot *AudioWidget::signalPlot() const
{
    return m_signalPlot;
}

QseAudacityController *AudioWidget::controller() const
{
    return m_controller;
}

SignalDataSource *AudioWidget::dataSource() const
{
    return m_dataSource;
}

AudioLimiter *AudioWidget::limiter() const
{
    return m_limiter;
}


#endif // AUDIOWIDGET_H
