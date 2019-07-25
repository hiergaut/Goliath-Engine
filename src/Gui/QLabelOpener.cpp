#include "QLabelOpener.h"

#include <QDebug>
#include <QMouseEvent>

QLabelOpener::QLabelOpener(QWidget* parent)
    : QLabel(parent)
{
}

void QLabelOpener::mousePressEvent(QMouseEvent* ev)
{

//    qDebug() << this << ": mousePressEvent";

    m_posOnClick = ev->pos();
    m_pressed = true;
}

void QLabelOpener::mouseMoveEvent(QMouseEvent* ev)
{
    //    qDebug() << curPos;
    if (m_pressed) {
        QPoint curPos = ev->pos();
        if (qAbs(curPos.x() - m_posOnClick.x()) > 10) {
            emit addingNewHSplit(ev);
            m_pressed = false;
        } else if (qAbs(curPos.y() - m_posOnClick.y()) > 10) {
            emit addingNewVSplit(ev);
            m_pressed = false;
        }
    }
}
