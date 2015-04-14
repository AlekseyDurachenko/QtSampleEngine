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
#ifndef CCOMPLEXMONOAUDIOWIDGET_H
#define CCOMPLEXMONOAUDIOWIDGET_H

#include <QWidget>
#include "qsesppgeometry.h"
class QScrollBar;
class CSppSyncAudioWidget;
class QseSppSignalLinearAmplMetricProvider;
class QseSppTimeMetricProvider;
class QseSppStandardHorizontalController;
class QseSppStandardVerticalController;
class QseSppStandardHorizontalZoomController;
class QseSppStandardVerticalZoomController;
class QseSppCompositController;
class QseSppHorizontalShiftControllerProxy;
class QseSppHorizontalAxisWidget;
class QseSppVerticalAxisWidget;


class CComplexMonoAudioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CComplexMonoAudioWidget(QWidget *parent = 0);
    virtual ~CComplexMonoAudioWidget();
    inline CSppSyncAudioWidget *audioWidget() const;
private slots:
    void dataSource_dataChanged();
    void audioWidget_geometryChanged(const QseSppGeometry &geometry);
    void scrollBar_valueChanged(int value);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    CSppSyncAudioWidget *m_audioWidget;
    QseSppVerticalAxisWidget *m_amplitudeAxis;
    QseSppHorizontalAxisWidget *m_timeAxis;
    QseSppSignalLinearAmplMetricProvider *m_amplitudeProvider;
    QseSppTimeMetricProvider *m_timeProvider;
    QScrollBar *m_timeScrollBar;
    QseSppStandardHorizontalController *m_horizontalCtrl;
    QseSppStandardVerticalController *m_verticalCtrl;
    QseSppStandardHorizontalZoomController *m_horizontalZoomCtrl;
    QseSppStandardVerticalZoomController *m_verticalZoomCtrl;
    QseSppCompositController *m_horizontalCompositCtrl;
    QseSppCompositController *m_verticalCompositCtrl;
    QseSppHorizontalShiftControllerProxy *m_horizontalAxisZoomControllerProxy;
};

CSppSyncAudioWidget *CComplexMonoAudioWidget::audioWidget() const
{
    return m_audioWidget;
}


#endif // CCOMPLEXMONOAUDIOWIDGET_H
