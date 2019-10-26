
#include "CameraFps.h"
#include <QDateTime>
#include <QDebug>
#include <glm/glm.hpp>
//#include <QThread>
#include <session/Session.h>

//CameraFps::CameraFps(glm::vec3 position, glm::vec3 target)
//    : Camera(position)
//{
//#include <thread>

//}
const float accuracyRotate = 0.1f;
const float accuracyMove = 0.5f;
//const float accuracySlide = 0.05f;
const float accuracyZoom = 0.05f;

//void autoRefreshMoving(glm::mat4 & m_modelTransform, glm::vec3 & m_front, glm::vec3 & m_right, float & frontDir, float & sideDir )
//void CameraFps::autoRefreshMoving()
//{
//    uint period = 10;
//    for (uint i = 0; i < 20; ++i) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(period));
//        //                m_lastTime += 100;

//        glm::vec3 position = glm::vec3(m_modelTransform[3]);
////        glm::vec3
//        float velocity = accuracyMove * period;
//        glm::vec3 newPosition = position + (m_front * frontDir + m_right * sideDir) * velocity;
//        // question : [3][3] 1 or 0 ?
//        m_modelTransform[3] = glm::vec4(newPosition, m_modelTransform[3][3]);
//        //                ProcessKeyboard();
//    }
//}

CameraFps::CameraFps(std::ifstream &file, Model &model, float &fov)
//CameraFps::CameraFps(std::ifstream& file, glm::mat4 & modelTransform, float& fov)
//    : CameraStrategy(modelTransform)
    : CameraStrategy(model)
    , m_fov(fov)
{
    //    Session::load(m_view, file);

    m_type = FPS;
    ////    Camera::load(file);

    //    float data[2];
    //    file.read(reinterpret_cast<char*>(data), sizeof(data));
    Session::load(m_yaw, file);
    Session::load(m_pitch, file);

    //    m_yaw = data[0];
    //    m_pitch = data[1];

    updateCameraVectors();
    //    m_lastTime = QDateTime::currentMSecsSinceEpoch();

    //    timer = new QTimer();
    //    connect(timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
}

//CameraFps::CameraFps(MainWindow3dView* view, glm::mat4 & modelTransform)
//    : CameraStrategy(modelTransform)
//    , m_view(view)
//{ //    m_fov = ZOOM;
//    m_type = FPS;

//    //    m_position = position;
//    //    m_worldUp = up;
//    //    m_yaw = yaw;
//    //    m_pitch = pitch;
//    //    m_center = QPoint(view->width() /2, view->height() / 2);

//    //    m_center = view->mapToGlobal(QPoint(view->width() / 2, view->height() / 2));
//    m_lastTime = QDateTime::currentMSecsSinceEpoch();

//    //    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
//    //    QCursor::setPos(m_center);
//    //    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);
//    //    m_view->setMouseTracking(true);
//    //    m_view->centralWidget()->setMouseTracking(true);
//    //    m_view->setCursor(Qt::BlankCursor);
//    //    updateView();
//}

//CameraFps::CameraFps(const glm::vec3& position, float yaw, float pitch, MainWindow3dView* view, glm::mat4 & modelTransform, float& fov)
CameraFps::CameraFps(const glm::vec3 &position, float yaw, float pitch, MainWindow3dView *view, Model &model, float &fov)
    : CameraStrategy(model)
    , m_view(view)
    , m_fov(fov)
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

    //    updateView();
    //    m_center = m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2));
    //    QCursor::setPos(m_center);
    //    m_centerLocal = QPoint(m_view->width() / 2, m_view->height() / 2);
    //    m_view->setMouseTracking(true);
    //    m_view->centralWidget()->setMouseTracking(true);
    //    m_view->setCursor(Qt::BlankCursor);
    //    m_view->setMouseTracking(true);
    updateCameraVectors();
    //    m_lastTime = QDateTime::currentMSecsSinceEpoch();
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

//void CameraFps::load(std::ifstream &file)
//{
////    Camera::load(file);

//    float data[2];
//    file.read(reinterpret_cast<char*>(data), sizeof(data));

//    m_yaw = data[0];
//    m_pitch = data[1];

//    updateCameraVectors();
//}

void CameraFps::save(std::ofstream& file)
{
    //    CameraStrategy::save(file);

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
//glm::mat4 CameraFps::viewMatrix() const
//{
//    ProcessKeyboard();

//    //    return glm::lookAt(m_position, m_position + m_front, m_up);
//    return glm::inverse(m_modelTransform);
//}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraFps::ProcessKeyboard() const
{
//    qDebug() << "procces keyboard";

    uint64_t currentTime = QDateTime::currentMSecsSinceEpoch();
    uint64_t deltaTime = currentTime - m_lastTime;
    if (deltaTime == 0)
        return;
    //    qDebug() << "delta time = " << deltaTime << ", current time = " << currentTime << ", last time = " << m_lastTime;
    //    qDebug() << "delta time = " << deltaTime;
    m_lastTime = currentTime;

    glm::vec3 position = glm::vec3(m_model.transform()[3]);
    float velocity = accuracyMove * deltaTime;
    glm::vec3 newPosition = position + (m_front * frontDir + m_right * sideDir) * velocity;
    // question : [3][3] 1 or 0 ?
    glm::mat4 model = m_model.transform();
    model[3] = glm::vec4(newPosition, m_model.transform()[3][3]);

    m_model.setTransform(model);

    //    m_modelTransform = glm::inverse(glm::lookAt(newPosition, newPosition + m_front, m_up));

    //    glm::vec4& translate = m_modelTransform[3];
    //    translate.x = newPosition.x;
    //    translate.y = newPosition.y;
    //    translate.z = newPosition.z;

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

    glm::vec3 position = m_model.transform()[3];
//    m_modelTransform = glm::inverse(glm::lookAt(position, position + m_front, m_up));
    m_model.setTransform(glm::inverse(glm::lookAt(position, position + m_front, m_up)));
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
    CameraStrategy::keyPressEvent(event);

    //    qDebug() << "keyPressEvent";
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

    default:
        m_view->m_timer->stop();
        return;
    }

    if (!event->isAutoRepeat()) {
        m_lastTime = QDateTime::currentMSecsSinceEpoch();
        m_view->m_timer->start(10);
    }
    //        ProcessKeyboard();
    //    } else {
    //        m_lastTime = QDateTime::currentMSecsSinceEpoch();
    //        //            uint period = 24; // millisecond
    //        //        std::thread t(autoRefreshMoving, m_modelTransform, m_front, m_right, frontDir, sideDir);
    ////        std::thread(&CameraFps::autoRefreshMoving, this);
    //    }
}

void CameraFps::keyReleaseEvent(QKeyEvent* event)
{
    CameraStrategy::keyReleaseEvent(event);

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
    CameraStrategy::mousePressEvent(event);

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
    CameraStrategy::mouseMoveEvent(event);

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

void CameraFps::setTarget(const glm::vec3 &target)
{
//    m_target = target;

}

//void CameraFps::setDefault()
//{

//}

void CameraFps::setFront(const glm::vec3& front)
{
    m_yaw = glm::degrees(atan2f(front.y, front.x));
    m_pitch = glm::degrees(asinf(front.z));

    updateCameraVectors();
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

glm::vec3 CameraFps::target() const
{
    glm::vec3 m_position = glm::vec3(m_model.transform()[3]);
    return m_position + 200.0f * m_front;
}
