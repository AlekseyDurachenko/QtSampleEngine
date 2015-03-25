// Copyright 2013-2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef QSESPPAUDACITYCONTROLLER_H
#define QSESPPAUDACITYCONTROLLER_H

#include "qseabstractsppcontroller.h"
class QsePosition;
class QseSelection;


// The key combination:
// ctrl+LeftButton - emit playClicked()
// ctrl+wheel - horizontal zoom
// wheel + shift - scroll the signal
// LeftButton+Move - selection
// shift + LeftButtonClick - expand selecton,
// if not exists then expand from cursor
// LeftButtonClick - set cursor
// if selection is exists cursor not exists, and otherwise
class QseSppAudacityController : public QseAbstractSppController
{
    Q_OBJECT
public:
    explicit QseSppAudacityController(QObject *parent = 0);

    inline QsePosition *position();
    void setPosition(QsePosition *position);

    inline QseSelection *selection();
    void setSelection(QseSelection *selection);

    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect,
                                const QseSppGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect,
                                 const QseSppGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect,
                                   const QseSppGeometry &geometry);
    virtual void wheelEvent(QWheelEvent *event, const QRect &rect,
                            const QseSppGeometry &geometry);
signals:
    void playClicked(qint64 index);
private slots:
    void position_destroyed();
    void selection_destroyed();
private:
    void startSelection(QMouseEvent *event, const QRect &rect,
                        const QseSppGeometry &geometry);
    void extendSelection(QMouseEvent *event, const QseSppGeometry &geometry);
    void changeSelection(QMouseEvent *event, const QseSppGeometry &geometry);
    void endSelection();
    void clickPlayPosition(QMouseEvent *event, const QseSppGeometry &geometry);
    void horizontalZoom(QWheelEvent *event, const QseSppGeometry &geometry);
    void horizontalScroll(QWheelEvent *event, const QseSppGeometry &geometry);
    void updateCursor(int x, const QRect &rect, const QseSppGeometry &geometry);
private:
    QsePosition *m_position;
    QseSelection *m_selection;
    // true  -- ready to change the selection
    // false -- not ready to change the selection
    bool m_isSelectionAction;
    qint64 m_otherSample;
};

QsePosition *QseSppAudacityController::position()
{
    return m_position;
}

QseSelection *QseSppAudacityController::selection()
{
    return m_selection;
}


#endif // QSESPPAUDACITYCONTROLLER_H
