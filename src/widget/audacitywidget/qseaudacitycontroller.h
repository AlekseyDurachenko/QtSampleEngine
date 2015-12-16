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
#ifndef QSEAUDACITYCONTROLLER_H
#define QSEAUDACITYCONTROLLER_H

#include "qseabstractcontroller.h"
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
class QseAudacityController : public QseAbstractController
{
    Q_OBJECT
public:
    explicit QseAudacityController(QObject *parent = 0);

    inline QsePosition *position();
    void setPosition(QsePosition *position);

    inline QseSelection *selection();
    void setSelection(QseSelection *selection);

    virtual void mouseMoveEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mousePressEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void mouseReleaseEvent(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    virtual void wheelEvent(QWheelEvent *event, const QRect &rect, const QseGeometry &geometry);

signals:
    void playClicked(qint64 index);

private slots:
    void position_destroyed();
    void selection_destroyed();

private:
    void startSelection(QMouseEvent *event, const QRect &rect, const QseGeometry &geometry);
    void extendSelection(QMouseEvent *event, const QseGeometry &geometry);
    void changeSelection(QMouseEvent *event, const QseGeometry &geometry);
    void endSelection();
    void clickPlayPosition(QMouseEvent *event, const QseGeometry &geometry);
    void horizontalZoom(QWheelEvent *event, const QseGeometry &geometry);
    void horizontalScroll(QWheelEvent *event, const QseGeometry &geometry);
    void updateCursor(int x, const QRect &rect, const QseGeometry &geometry);

private:
    QsePosition *m_position;
    QseSelection *m_selection;
    // true  -- ready to change the selection
    // false -- not ready to change the selection
    bool m_isSelectionAction;
    qint64 m_otherSample;
};

QsePosition *QseAudacityController::position()
{
    return m_position;
}

QseSelection *QseAudacityController::selection()
{
    return m_selection;
}


#endif // QSEAUDACITYCONTROLLER_H
