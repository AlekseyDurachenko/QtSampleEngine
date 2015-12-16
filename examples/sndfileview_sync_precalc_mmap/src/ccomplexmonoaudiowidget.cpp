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
#include "qsehorizontalaxiswidget.h"
#include "qseverticalaxiswidget.h"
#include "qsesignallinearmetricprovider.h"
#include "qsetimemetricprovider.h"
#include "qseaxiscanvasplot.h"
#include "qsestandardhorizontalcontroller.h"
#include "qsestandardverticalcontroller.h"
#include "qsestandardhorizontalzoomcontroller.h"
#include "qsestandardverticalzoomcontroller.h"
#include "qsehorizontalshiftcontrollerproxy.h"
#include "qsecompositcontroller.h"
#include "csppsyncaudiowidget.h"
#include "csppsyncaudiolimiter.h"
#include "csppsyncpeakdatasource.h"


CComplexMonoAudioWidget::CComplexMonoAudioWidget(QWidget *parent)
    : QWidget(parent)
{
    m_audioWidget = new CSppSyncAudioWidget(this);

    m_timeScrollBar = new QScrollBar(Qt::Horizontal, this);
    connect(m_timeScrollBar, SIGNAL(valueChanged(int)),
            this, SLOT(scrollBar_valueChanged(int)));

    m_horizontalCtrl = new QseStandardHorizontalController(this);
    m_horizontalCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_horizontalCtrl->setMouseButtons(Qt::LeftButton);
    m_horizontalZoomCtrl = new QseStandardHorizontalZoomController(this);
    m_horizontalZoomCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_horizontalAxisZoomControllerProxy = new QseHorizontalShiftControllerProxy(this);
    m_horizontalAxisZoomControllerProxy->setController(m_horizontalZoomCtrl);
    m_horizontalCompositCtrl = new QseCompositController(this);
    QList<QseAbstractController *> hctrls;
    hctrls << m_horizontalCtrl;
    hctrls << m_horizontalAxisZoomControllerProxy;
    m_horizontalCompositCtrl->setControllers(hctrls);
    connect(m_horizontalCompositCtrl, SIGNAL(geometryChanged(QseGeometry)),
            m_audioWidget, SLOT(setGeometry(QseGeometry)));

    m_verticalCtrl = new QseStandardVerticalController(this);
    m_verticalCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_verticalCtrl->setMouseButtons(Qt::LeftButton);
    m_verticalZoomCtrl = new QseStandardVerticalZoomController(this);
    m_verticalZoomCtrl->setKeyboardModifiers(Qt::NoModifier);
    m_verticalCompositCtrl = new QseCompositController(this);
    QList<QseAbstractController *> vctrls;
    vctrls << m_verticalCtrl;
    vctrls << m_verticalZoomCtrl;
    m_verticalCompositCtrl->setControllers(vctrls);
    connect(m_verticalCompositCtrl, SIGNAL(geometryChanged(QseGeometry)),
            m_audioWidget, SLOT(setGeometry(QseGeometry)));

    m_amplitudeProvider = new QseSignalLinearMetricProvider(this);
    m_timeProvider = new QseTimeMetricProvider(this);

    m_amplitudeAxis = new QseVerticalAxisWidget(this);
    m_amplitudeAxis->setAlignment(QseVerticalAxisWidget::AlignRight);
    m_amplitudeAxis->setMetricProvider(m_amplitudeProvider);
    m_amplitudeAxis->setController(m_verticalCompositCtrl);
    m_amplitudeAxis->setLimiter(m_audioWidget->limiter());

    m_timeAxis = new QseHorizontalAxisWidget(this);
    m_timeAxis->setAlignment(QseHorizontalAxisWidget::AlignBottom);
    m_timeAxis->setMetricProvider(m_timeProvider);
    m_timeAxis->setController(m_horizontalCompositCtrl);
    m_timeAxis->setLimiter(m_audioWidget->limiter());
    connect(m_timeAxis, SIGNAL(shiftChanged(int)),
            m_horizontalAxisZoomControllerProxy, SLOT(setShift(int)));

    m_audioWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_audioWidget->canvasPlot()->setVerticalMetricProvider(m_amplitudeProvider);
    m_audioWidget->canvasPlot()->setHorizontalMetricProvider(m_timeProvider);
    m_audioWidget->installEventFilter(this);
    connect(m_audioWidget, SIGNAL(geometryChanged(QseGeometry)),
            m_amplitudeAxis, SLOT(setGeometry(QseGeometry)));
    connect(m_audioWidget, SIGNAL(geometryChanged(QseGeometry)),
            m_timeAxis, SLOT(setGeometry(QseGeometry)));
    connect(m_audioWidget->dataSource(), SIGNAL(dataChanged()),
            this, SLOT(dataSource_dataChanged()));
    connect(m_audioWidget, SIGNAL(geometryChanged(QseGeometry)),
            this, SLOT(audioWidget_geometryChanged(QseGeometry)));

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
    const QseGeometry &geometry)
{
    m_timeScrollBar->blockSignals(true);
    const qint64 maxIndex = m_audioWidget->dataSource()->maxIndex();
    const qint64 minIndex = m_audioWidget->dataSource()->minIndex();
    if (geometry.spp() < 0) {
        m_timeScrollBar->setRange(minIndex, maxIndex);
        m_timeScrollBar->setValue(geometry.x());
    }
    else {
        m_timeScrollBar->setRange(minIndex / geometry.spp(),
                                  maxIndex / geometry.spp());
        m_timeScrollBar->setValue(geometry.x() / geometry.spp());
    }
    m_timeScrollBar->blockSignals(false);
}

void CComplexMonoAudioWidget::scrollBar_valueChanged(int value)
{
    QseGeometry geometry = m_audioWidget->geometry();
    if (geometry.spp() > 0)
        geometry.setX(geometry.spp()*value);
    else
        geometry.setX(value);

    m_audioWidget->setGeometry(geometry);
}

bool CComplexMonoAudioWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Move) {
        QMoveEvent *moveEvent = static_cast<QMoveEvent *>(event);
        const QPoint timeAxisZeroPos = moveEvent->pos() - m_timeAxis->pos();
        m_timeAxis->setShift(timeAxisZeroPos.x());
    }

    return QObject::eventFilter(obj, event);
}
