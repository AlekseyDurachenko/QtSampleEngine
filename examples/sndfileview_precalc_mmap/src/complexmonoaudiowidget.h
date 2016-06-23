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
#ifndef COMPLEXMONOAUDIOWIDGET_H
#define COMPLEXMONOAUDIOWIDGET_H

#include <QWidget>
#include "qsegeometry.h"
class QScrollBar;
class AudioWidget;
class QseSignalLinearMetricProvider;
class QseTimeMetricProvider;
class QseStandardHorizontalController;
class QseStandardVerticalController;
class QseStandardHorizontalZoomController;
class QseStandardVerticalZoomController;
class QseCompositController;
class QseHorizontalShiftControllerProxy;
class QseHorizontalAxisWidget;
class QseVerticalAxisWidget;


class ComplexMonoAudioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComplexMonoAudioWidget(QWidget *parent = 0);
    virtual ~ComplexMonoAudioWidget();

    inline AudioWidget *audioWidget() const;

private slots:
    void dataSource_dataChanged();
    void audioWidget_geometryChanged(const QseGeometry &geometry);
    void scrollBar_valueChanged(int value);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    AudioWidget *m_audioWidget;
    QseVerticalAxisWidget *m_amplitudeAxis;
    QseHorizontalAxisWidget *m_timeAxis;
    QseSignalLinearMetricProvider *m_amplitudeProvider;
    QseTimeMetricProvider *m_timeProvider;
    QScrollBar *m_timeScrollBar;
    QseStandardHorizontalController *m_horizontalCtrl;
    QseStandardVerticalController *m_verticalCtrl;
    QseStandardHorizontalZoomController *m_horizontalZoomCtrl;
    QseStandardVerticalZoomController *m_verticalZoomCtrl;
    QseCompositController *m_horizontalCompositCtrl;
    QseCompositController *m_verticalCompositCtrl;
    QseHorizontalShiftControllerProxy *m_horizontalAxisZoomControllerProxy;
};

AudioWidget *ComplexMonoAudioWidget::audioWidget() const
{
    return m_audioWidget;
}


#endif // COMPLEXMONOAUDIOWIDGET_H
