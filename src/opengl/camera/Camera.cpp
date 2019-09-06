#include "Camera.h"

//Camera::Camera()
//{

//}
#include <QDebug>
#include <glm/gtc/type_ptr.hpp>

float Camera::accuracyRotate = 0.01f;
float Camera::accuracyMove = 0.001f;
float Camera::accuracySlide = 0.05f;


Camera::Camera(float fov, glm::vec3 position)
    : m_fov(fov)
    , m_position(position)
{
}

void Camera::load(std::ifstream &file)
{
    float data[4];
    file.read(reinterpret_cast<char*>(&data), sizeof (data));

    m_position = glm::make_vec3(data);
    m_fov = data[3];

}

void Camera::save(std::ofstream &file)
{
    float data[4];

    std::memcpy(data, glm::value_ptr(m_position), 3 * sizeof(float));
    data[3] = m_fov;

    file.write(reinterpret_cast<const char*>(&data), sizeof (data));

}

//Camera::Camera(Camera *camera)
//    : m_fov(camera->m_fov)
//    , m_position(camera->m_position)
//{
//}

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
//    event->ignore();
}

void Camera::mouseMoveEvent(QMouseEvent* event)
{
}

void Camera::wheelEvent(QWheelEvent* event)
{
}

void Camera::focusInEvent(QFocusEvent *event)
{
    m_shiftPressed = false;

}

void Camera::resizeEvent(QResizeEvent *event)
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
