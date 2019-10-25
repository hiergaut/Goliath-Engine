#include "CameraStrategy.h"

//#include <session/Session.h>

//CameraStrategy::CameraStrategy()
//{

//}

//Camera::Camera(Camera *camera)
//    : m_fov(camera->m_fov)
//    , m_position(camera->m_position)
//{
//}

//void CameraStrategy::save(std::ofstream &file)
//{

//}

CameraStrategy::CameraStrategy(glm::mat4 modelTransform)
    : m_modelTransform(modelTransform)
{

}

void CameraStrategy::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;
    }
}

void CameraStrategy::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = false;
        //        qDebug() << "shift pressed";
        break;
        //    case Qt::Key_Up:
        //    case Qt::Key_Comma:
        //    case Qt::Key_Down:
        //    case Qt::Key_O:
        //        frontDir = 0;
        //        break;

        //    case Qt::Key_Left:
        //    case Qt::Key_A:
        //    case Qt::Key_Right:
        //    case Qt::Key_E:
        //        sideDir = 0;
        //        break;
    }
}

void CameraStrategy::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        //    } else if (event->button() == Qt::LeftButton) {
        //        qDebug() << this << "left clicked";
    }
}

void CameraStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = false;
    }
    //    event->ignore();
}

void CameraStrategy::mouseMoveEvent(QMouseEvent* event)
{
}

void CameraStrategy::wheelEvent(QWheelEvent* event)
{
}

void CameraStrategy::focusInEvent(QFocusEvent* event)
{
    m_shiftPressed = false;
}

void CameraStrategy::resizeEvent(QResizeEvent* event)
{
}

