
#include "CameraFps.h"
#include <QDateTime>
#include <QDebug>
#include <glm/glm.hpp>
//#include <QThread>

//CameraFps::CameraFps(glm::vec3 position, glm::vec3 target)
//    : Camera(position)
//{

//}
const float accuracyRotate = 0.1f;
const float accuracyMove = 1.0f;
//const float accuracySlide = 0.05f;
const float accuracyZoom = 0.05;


CameraFps::CameraFps(MainWindow3dView * view)
    : Camera(50.0f, glm::vec3(0.0f, 0.0f, 0.0f))
    , m_view(view)
{   //    m_fov = ZOOM;
    m_type = FPS;

    //    m_position = position;
    //    m_worldUp = up;
    //    m_yaw = yaw;
    //    m_pitch = pitch;
    //    m_center = QPoint(view->width() /2, view->height() / 2);

    //    m_center = view->mapToGlobal(QPoint(view->width() / 2, view->height() / 2));
    m_lastTime = QDateTime::currentMSecsSinceEpoch();

//    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
//    QCursor::setPos(m_center);
//    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);
//    m_view->setMouseTracking(true);
//    m_view->centralWidget()->setMouseTracking(true);
//    m_view->setCursor(Qt::BlankCursor);
//    updateView();

}

CameraFps::CameraFps(float fov, const glm::vec3 &position, float yaw, float pitch, MainWindow3dView* view)
    : Camera(fov, position)
    , m_view(view)
    , m_yaw(yaw)
    , m_pitch(pitch)

//    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
//    , MovementSpeed(SPEED)
//    , MouseSensitivity(SENSITIVITY)
//    , m_fov(ZOOM)
{
    //        initializeOpenGLFunctions();
    //    m_fov = ZOOM;
    m_type = FPS;

    //    m_position = position;
    //    m_worldUp = up;
    //    m_yaw = yaw;
    //    m_pitch = pitch;
    //    m_center = QPoint(view->width() /2, view->height() / 2);

    //    m_center = view->mapToGlobal(QPoint(view->width() / 2, view->height() / 2));
    m_lastTime = QDateTime::currentMSecsSinceEpoch();

//    updateView();
//    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
//    QCursor::setPos(m_center);
//    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);
//    m_view->setMouseTracking(true);
//    m_view->centralWidget()->setMouseTracking(true);
//    m_view->setCursor(Qt::BlankCursor);
    //    m_view->setMouseTracking(true);
    updateCameraVectors();
}

//CameraFps::CameraFps(CameraWorld *camera, MainWindow3dView * view)
//    :Camera(camera)
//{
//    m_type = FPS;

//    glm::vec3 front = glm::normalize(camera->target() - camera->position());

////    m_yaw = glm::degrees(cosf(front.x /(sqrtf(front.x * front.x + front.z * front.z))));
//    m_yaw = atanf(front.y / front.x);
//    m_pitch =asinf(front.z);

//    updateCameraVectors();

//    m_center = view->mapToGlobal(QPoint(view->width() / 2, view->height() / 2));
//    m_lastTime = QDateTime::currentMSecsSinceEpoch();

//    delete camera;
//}

CameraFps::~CameraFps()
{
//    m_view->setMouseTracking(false);
//    m_view->centralWidget()->setMouseTracking(false);
    //    m_view->setCursor(Qt::BlankCursor);
//    m_view->setCursor(Qt::ArrowCursor);

    trackingOff();
}

void CameraFps::load(std::ifstream &file)
{
    Camera::load(file);

    float data[2];
    file.read(reinterpret_cast<char*>(data), sizeof(data));

    m_yaw = data[0];
    m_pitch = data[1];

    updateCameraVectors();
}

void CameraFps::save(std::ofstream &file)
{
    Camera::save(file);

    float data[2];
    data[0] = m_yaw;
    data[1] = m_pitch;

    file.write(reinterpret_cast<const char*>(data), sizeof(data));

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
    ProcessKeyboard();
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraFps::ProcessKeyboard() const
{
    uint64_t currentTime = QDateTime::currentMSecsSinceEpoch();
    uint64_t deltaTime = currentTime - m_lastTime;
    if (deltaTime == 0)
        return;
    //    qDebug() << "delta time = " << deltaTime << ", current time = " << currentTime << ", last time = " << m_lastTime;
    //    qDebug() << "delta time = " << deltaTime;
    m_lastTime = currentTime;

    float velocity = accuracyMove * deltaTime;
    m_position += (m_front * frontDir + m_right * sideDir) * velocity;
    //    if (direction == FORWARD)
    //        m_position += m_front * velocity;
    //    if (direction == BACKWARD)
    //        m_position -= m_front * velocity;
    //    if (direction == LEFT)
    //        m_position -= m_right * velocity;
    //    if (direction == RIGHT)
    //        m_position += m_right * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraFps::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch /* = true */)
{
    //    qDebug() << xoffset << yoffset;
    xoffset *= accuracyRotate;
    yoffset *= accuracyRotate;

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
        m_fov -= yoffset * accuracyZoom;
    if (m_fov <= ZOOM_MAX)
        m_fov = ZOOM_MAX;
    if (m_fov >= ZOOM_MIN)
        m_fov = ZOOM_MIN;

    m_view->updateProjectionMatrix();
//    m_view->updatePersepectiveProjection();
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

void CameraFps::updateCenter()
{
    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);

}

//void CameraFps::updateView()
//{
//    QCursor::setPos(m_center);

//}

void CameraFps::trackingOn()
{
    m_view->setMouseTracking(true);
    m_view->centralWidget()->setMouseTracking(true);
    m_view->setCursor(Qt::CrossCursor);
}

void CameraFps::trackingOff()
{
    m_view->setMouseTracking(false);
    m_view->centralWidget()->setMouseTracking(false);
    m_view->setCursor(Qt::ArrowCursor);
}

void CameraFps::startFpsView()
{
    updateCenter();
    QCursor::setPos(m_center);
    trackingOn();
}

void CameraFps::keyPressEvent(QKeyEvent* event)
{
    Camera::keyPressEvent(event);

    switch (event->key()) {

    case Qt::Key_Escape:
        m_view->setMouseTracking(false);
        m_view->centralWidget()->setMouseTracking(false);
        m_view->setCursor(Qt::ArrowCursor);
        break;

    case Qt::Key_Up:
    case Qt::Key_Comma:
        //                        m_position += m_front * MOVE_SPEED;
        frontDir = 1;
        break;

    case Qt::Key_Down:
    case Qt::Key_O:

        frontDir = -1;
        //        cameraPos -= cameraFront * cameraSpeed;
        //                        m_position -= m_front * MOVE_SPEED;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        sideDir = -1;
        //                        m_position -= glm::normalize(glm::cross(m_front, m_up)) * MOVE_SPEED;
        break;

    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 1;
        //        m_position += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        //                        m_position += glm::normalize(glm::cross(m_front, m_up)) * MOVE_SPEED;
        break;
    }

    //    if (event->isAutoRepeat()) {
    //        ProcessKeyboard();
    //    } else {
    //        m_lastTime = QDateTime::currentMSecsSinceEpoch();
    //    }
}

void CameraFps::keyReleaseEvent(QKeyEvent* event)
{
    Camera::keyReleaseEvent(event);

    switch (event->key()) {
        //    case Qt::Key_Shift:
        //        m_shiftPressed = false;
        //        break;
    case Qt::Key_Up:
    case Qt::Key_Comma:
    case Qt::Key_Down:
    case Qt::Key_O:
        frontDir = 0;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 0;
        break;
    }
}

void CameraFps::mousePressEvent(QMouseEvent* event)
{
    Camera::mousePressEvent(event);

//    updateCenter();
//    QCursor::setPos(m_center);
//    trackingOn();
    startFpsView();

    //    m_lastPos = event->pos();
//    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
//    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);

    //    event->accept();
    //            setMouseTracking(true);
    //    m_view->centralWidget()->setMouseTracking(true);
    //    m_view->centralWidget()->setFocus();
    //    m_view->centralWidget()->setMouseTracking(true);
//    m_view->setMouseTracking(true);
//    m_view->centralWidget()->setMouseTracking(true);
//    m_view->setCursor(Qt::BlankCursor);
    //    m_view->setMouseTracking(true);
//    updateView();
//    trackingOn();
}

void CameraFps::mouseReleaseEvent(QMouseEvent* event)
{
    //    Camera::mouseReleaseEvent(event);
    //    m_view->setMouseTracking(true);
    //    m_view->centralWidget()->setMouseTracking(true);
}

void CameraFps::mouseMoveEvent(QMouseEvent* event)
{
    Camera::mouseMoveEvent(event);

    float dx = event->x() - m_centerLocal.x();
    float dy = event->y() - m_centerLocal.y();
    //    m_center = event->pos();
    //    m_lastPos = event->pos();
    if (dx != 0.0f || dx != 0.0f) {
        QCursor::setPos(m_center);

        ProcessMouseMovement(-dx, -dy);
    }
    //    event->accept();
    //    m_view->setCursorToCenter();
    //    m_center = m_view->mapToGlobal(QPoint(m_view->width() /2, m_view->height() / 2));
    //    QCursor::setPos(m_center);
    //    QPoint glob = m_view->mapToGlobal(QPoint(m_view->width() /2, m_view->height() /2));
}

void CameraFps::wheelEvent(QWheelEvent* event)
{
    //    qDebug() << event->delta();
    //    int dy = (event->delta() > 0) ? 1 : -1;
    ProcessMouseScroll(event->delta());
}

//void CameraFps::focusInEvent(QFocusEvent* event)
//{
//    Camera::focusInEvent(event);

//    qDebug() << "CameraFps::focusInEvent";

//    //    m_lastTime = QDateTime::currentMSecsSinceEpoch();
//    //    m_view->setMouseTracking(true);
//    //    m_view->centralWidget()->setMouseTracking(true);
//    //    m_view->setCursor(Qt::BlankCursor);
//    //    m_view->setMouseTracking(true);

//    //    qDebug() << "focus";
//}

void CameraFps::resizeEvent(QResizeEvent* event)
{
//    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
//    updateView();
    updateCenter();
}

glm::vec3 CameraFps::front() const
{
    return m_front;
}

glm::vec3 CameraFps::up() const
{
    return m_up;
}

glm::vec3 CameraFps::right() const
{
    return m_right;
}

void CameraFps::setFront(const glm::vec3 &front)
{
            m_yaw = glm::degrees(atan2f(front.y, front.x));
            m_pitch = glm::degrees(asinf(front.z));

            updateCameraVectors();
}

glm::vec3 CameraFps::target() const
{
        return m_position + 200.0f * m_front;
}
