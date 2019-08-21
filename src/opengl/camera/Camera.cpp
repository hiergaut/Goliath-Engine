#include "Camera.h"

//Camera::Camera()
//{

//}
#include <QDebug>

float Camera::accuracyRotate = 0.005f;
float Camera::accuracyMove = 0.001f;
float Camera::accuracySlide = 0.05f;


Camera::Camera(glm::vec3 position)
    : m_position(position)
{
}

void Camera::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;
    }
}

void Camera::keyReleaseEvent(QKeyEvent* event)
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

void Camera::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        //    } else if (event->button() == Qt::LeftButton) {
        //        qDebug() << this << "left clicked";
    }
}

void Camera::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = false;
    }
    event->ignore();
}

void Camera::mouseMoveEvent(QMouseEvent* event)
{
}

void Camera::wheelEvent(QWheelEvent* event)
{
}

float Camera::fov() const
{
    return m_fov;
}

const glm::vec3& Camera::position() const
{
    return m_position;
}
