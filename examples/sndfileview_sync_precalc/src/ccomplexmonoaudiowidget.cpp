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
#include "ccomplexmonoaudiowidget.h"
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMoveEvent>
#include <QDebug>
#include "qsespphorizontalaxiswidget.h"
#include "qsesppverticalaxiswidget.h"
#include "qsesppsignallinearamplmetricprovider.h"
#include "qsespptimemetricprovider.h"
#include "qsesppaxiscanvasplot.h"
#include "qsesppstandardhorizontalcontroller.h"
#include "qsesppstandardverticalcontroller.h"
#include "qsesppstandardhorizontalzoomcontroller.h"
#include "qsesppstandardverticalzoomcontroller.h"
#include "qsespphorizontalshiftcontrollerproxy.h"
#include "qsesppcompositcontroller.h"
#include "csppsyncaudiowidget.h"
#include "csppsyncaudiolimiter.h"
#include "csppsyncpeakdatasource.h"


CComplexMonoAudioWidget::CComplexMonoAudioWidget(QWidget *parent) :
    QWidget(parent)
{
    m_audioWidget = new CSppSyncAudioWidget(this);

    m_timeScrollBar = new QScrollBar(Qt::Horizontal, this);
    connect(m_timeScrollBar, SIGNAL(valueChanged(int)),
            this, SLOT(scrollBar_valueChanged(int)));

    m_horizontalCtrl = new QseSppStandardHorizontalController(this);
    m_horizontalCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_horizontalCtrl->setMouseButtons(Qt::LeftButton);
    m_horizontalZoomCtrl = new QseSppStandardHorizontalZoomController(this);
    m_horizontalZoomCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_horizontalAxisZoomControllerProxy = new QseSppHorizontalShiftControllerProxy(this);
    m_horizontalAxisZoomControllerProxy->setController(m_horizontalZoomCtrl);
    m_horizontalCompositCtrl = new QseSppCompositController(this);
    QList<QseAbstractSppController *> hctrls;
    hctrls << m_horizontalCtrl;
    hctrls << m_horizontalAxisZoomControllerProxy;
    m_horizontalCompositCtrl->setControllers(hctrls);
    connect(m_horizontalCompositCtrl, SIGNAL(geometryChanged(QseSppGeometry)),
            m_audioWidget, SLOT(setGeometry(QseSppGeometry)));

    m_verticalCtrl = new QseSppStandardVerticalController(this);
    m_verticalCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_verticalCtrl->setMouseButtons(Qt::LeftButton);
    m_verticalZoomCtrl = new QseSppStandardVerticalZoomController(this);
    m_verticalZoomCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_verticalCompositCtrl = new QseSppCompositController(this);
    QList<QseAbstractSppController *> vctrls;
    vctrls << m_verticalCtrl;
    vctrls << m_verticalZoomCtrl;
    m_verticalCompositCtrl->setControllers(vctrls);
    connect(m_verticalCompositCtrl, SIGNAL(geometryChanged(QseSppGeometry)),
            m_audioWidget, SLOT(setGeometry(QseSppGeometry)));

    m_amplitudeProvider = new QseSppSignalLinearAmplMetricProvider(this);
    m_timeProvider = new QseSppTimeMetricProvider(this);

    m_amplitudeAxis = new QseSppVerticalAxisWidget(this);
    m_amplitudeAxis->setAlignment(QseSppVerticalAxisWidget::AlignRight);
    m_amplitudeAxis->setMetricProvider(m_amplitudeProvider);
    m_amplitudeAxis->setController(m_verticalCompositCtrl);
    m_amplitudeAxis->setLimiter(m_audioWidget->limiter());

    m_timeAxis = new QseSppHorizontalAxisWidget(this);
    m_timeAxis->setAlignment(QseSppHorizontalAxisWidget::AlignBottom);
    m_timeAxis->setMetricProvider(m_timeProvider);
    m_timeAxis->setController(m_horizontalCompositCtrl);
    m_timeAxis->setLimiter(m_audioWidget->limiter());
    connect(m_timeAxis, SIGNAL(shiftChanged(int)),
            m_horizontalAxisZoomControllerProxy, SLOT(setShift(int)));

    m_audioWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_audioWidget->canvasPlot()->setVerticalMetricProvider(m_amplitudeProvider);
    m_audioWidget->canvasPlot()->setHorizontalMetricProvider(m_timeProvider);
    m_audioWidget->installEventFilter(this);
    connect(m_audioWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            m_amplitudeAxis, SLOT(setGeometry(QseSppGeometry)));
    connect(m_audioWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            m_timeAxis, SLOT(setGeometry(QseSppGeometry)));
    connect(m_audioWidget->dataSource(), SIGNAL(dataChanged()),
            this, SLOT(dataSource_dataChanged()));
    connect(m_audioWidget, SIGNAL(geometryChanged(QseSppGeometry)),
            this, SLOT(audioWidget_geometryChanged(QseSppGeometry)));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);
    hbox->addWidget(m_amplitudeAxis);
    hbox->addWidget(m_audioWidget);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->addWidget(m_timeAxis);
    vbox->addLayout(hbox);
    vbox->addWidget(m_timeScrollBar);

    setLayout(vbox);
}

CComplexMonoAudioWidget::~CComplexMonoAudioWidget()
{
}

void CComplexMonoAudioWidget::dataSource_dataChanged()
{
    m_timeProvider->setSampleRate(m_audioWidget->dataSource()->sampleRate());
    audioWidget_geometryChanged(m_audioWidget->geometry());
}

void CComplexMonoAudioWidget::audioWidget_geometryChanged(
        const QseSppGeometry &geometry)
{
    m_timeScrollBar->blockSignals(true);
    const qint64 maxIndex = m_audioWidget->dataSource()->maxIndex();
    const qint64 minIndex = m_audioWidget->dataSource()->minIndex();
    if (geometry.samplesPerPixel() < 0)
    {
        m_timeScrollBar->setRange(minIndex, maxIndex);
        m_timeScrollBar->setValue(geometry.x());
    }
    else
    {
        m_timeScrollBar->setRange(minIndex/geometry.samplesPerPixel(),
                                  maxIndex/geometry.samplesPerPixel());
        m_timeScrollBar->setValue(geometry.x()/geometry.samplesPerPixel());
    }
    m_timeScrollBar->blockSignals(false);
}

void CComplexMonoAudioWidget::scrollBar_valueChanged(int value)
{
    QseSppGeometry geometry = m_audioWidget->geometry();
    if (geometry.samplesPerPixel() > 0)
        geometry.setX(geometry.samplesPerPixel()*value);
    else
        geometry.setX(value);

    m_audioWidget->setGeometry(geometry);
}

bool CComplexMonoAudioWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Move)
    {
        QMoveEvent *moveEvent = static_cast<QMoveEvent *>(event);
        const QPoint timeAxisZeroPos = moveEvent->pos()-m_timeAxis->pos();
        m_timeAxis->setShift(timeAxisZeroPos.x());
    }

    return QObject::eventFilter(obj, event);
}
