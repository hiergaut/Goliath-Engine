
#include "CameraFps.h"
#include <glm/glm.hpp>
#include <QDebug>

//CameraFps::CameraFps(glm::vec3 position, glm::vec3 target)
//    : Camera(position)
//{

//}

CameraFps::CameraFps(glm::vec3 position, float yaw, float pitch, MainWindow3dView* view)
    : Camera(position)
    , m_view(view)

//    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
//    , MovementSpeed(SPEED)
//    , MouseSensitivity(SENSITIVITY)
//    , m_fov(ZOOM)
{
    //        initializeOpenGLFunctions();
    //    m_fov = ZOOM;

    m_position = position;
    //    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
//    m_center = QPoint(view->width() /2, view->height() / 2);
    m_center = view->mapToGlobal(QPoint(view->width() /2, view->height() / 2));
    updateCameraVectors();
}
//// Constructor with scalar values
//CameraFps::CameraFps(float posX, float posY, float posZ, float yaw, float pitch)
//    : Camera(glm::vec3(posX, posY, posZ))

////    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
////    , MovementSpeed(SPEED)
////    , MouseSensitivity(SENSITIVITY)
////    , Zoom(ZOOM)
//{
////    m_fov = ZOOM;
//    //        initializeOpenGLFunctions();

//    m_position = glm::vec3(posX, posY, posZ);
////    m_worldUp = glm::vec3(upX, upY, upZ);
//    m_yaw = yaw;
//    m_pitch = pitch;
//    updateCameraVectors();
//}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 CameraFps::viewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraFps::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = SENSITIVITY * deltaTime;
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraFps::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    qDebug() << xoffset << yoffset;
    xoffset *= SPEED;
    yoffset *= SPEED;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraFps::ProcessMouseScroll(float yoffset)
{
    if (m_fov >= ZOOM_MAX && m_fov <= ZOOM_MIN)
        m_fov -= yoffset;
    if (m_fov <= ZOOM_MAX)
        m_fov = ZOOM_MAX;
    if (m_fov >= ZOOM_MIN)
        m_fov = ZOOM_MIN;
}

void CameraFps::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    front.z = sinf(glm::radians(m_pitch));
    front.y = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 0.0f, 1.0f))); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

void CameraFps::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->x() - m_centerLocal.x();
    float dy = event->y() - m_centerLocal.y();
//    m_center = event->pos();
//    m_lastPos = event->pos();
    QCursor::setPos(m_center);

    ProcessMouseMovement(-dx, -dy);

//    event->accept();
//    m_view->setCursorToCenter();
//    m_center = m_view->mapToGlobal(QPoint(m_view->width() /2, m_view->height() / 2));
//    QCursor::setPos(m_center);
//    QPoint glob = m_view->mapToGlobal(QPoint(m_view->width() /2, m_view->height() /2));
}

void CameraFps::mousePressEvent(QMouseEvent* event)
{
    m_lastPos = event->pos();
    m_center = m_view->mapToGlobal(QPoint(m_view->width() /2, m_view->height() / 2));
    m_centerLocal = QPoint(m_view->width() /2, m_view->height() / 2);
//            setMouseTracking(true);
    m_view->centralWidget()->setMouseTracking(true);
//    m_view->centralWidget()->setFocus();
}

void CameraFps::mouseReleaseEvent(QMouseEvent *event)
{
    m_view->setMouseTracking(true);

}
