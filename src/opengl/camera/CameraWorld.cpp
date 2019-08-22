#include "CameraWorld.h"

CameraWorld::CameraWorld()
    :Camera(50.0f, glm::vec3(0.0f, 0.0f, 0.0f))
{
    m_type = WORLD;

}

CameraWorld::CameraWorld(float fov, glm::vec3 position, glm::vec3 target)
    : Camera(fov, position)
    //    : m_position { position }
    , m_target { target }
{
    m_type = WORLD;

    //        updateCameraVectors();
}

void CameraWorld::processMouseMovement(float xoffset, float yoffset)
{
    glm::vec3 v = m_position - m_target;
    float dist = glm::length(v);
    v = glm::normalize(v);
    glm::mat4 m(1.0);
    glm::vec3 xy = glm::cross(v, glm::vec3(0, 0, 1));
    //    if (glm::length(xy) > 0.1) {
    m = glm::rotate(m, -xoffset * accuracyRotate, glm::vec3(0, 0, 1));
    m = glm::rotate(m, yoffset * accuracyRotate, xy);

    v = m * glm::vec4(v, 1.0);
    m_position = v * dist + m_target;
    //    }

    //    qDebug() << "[CameraWorld]" << this << "processMouseMovement" << m_position.x << m_position.y << m_position.z;
}

void CameraWorld::processMouseScroll(float yoffset)
{
    glm::vec3 front = m_target - m_position;
    m_position += accuracyMove * front * yoffset;
}

void CameraWorld::processSliding(float dx, float dy)
{
    glm::vec3 front = m_target - m_position;
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 0, 1)));
    glm::vec3 up = glm::normalize(glm::cross(front, right));

    glm::vec3 slide = accuracySlide * (right * -dx + up * -dy);
    m_position += slide;
    m_target += slide;
}

void CameraWorld::load(std::ifstream& file)
{
    Camera::load(file);
    //    qDebug() << "[CameraWorld]" << this << "load" << m_position.x << m_position.y << m_position.z;
    float data[3];
    //        size_t size;
    //        size = sizeof(m_position);
    file.read(reinterpret_cast<char*>(&data), sizeof(data));

//    m_position = glm::make_vec3(data);
    m_target = glm::make_vec3(data);
//    m_fov = data[6];

    //    qDebug() << "[CAMERA WORLD] load" << this;
    //    qDebug() << m_position.x << m_position.y << m_position.z;
    //    qDebug() << m_target.x << m_target.y << m_target.z;
    //    qDebug() << m_fov;
}
void CameraWorld::save(std::ofstream& file)
{
    Camera::save(file);
    //    qDebug() << "[CameraWorld]" << this << "write" << m_position.x << m_position.y << m_position.z;
    //        m_position.x = 1.0f;
    //    glm::vec3 position = glm::vec3(-10, -10, -10);
    //        m_position.x = 1.0;
    //    qDebug() << "[CAMERA WORLD] write" << this;
    //    qDebug() << m_position.x << m_position.y << m_position.z;
    //    qDebug() << m_target.x << m_target.y << m_target.z;
    //    qDebug() << m_fov << "loaded";

    float data[3];
    std::memcpy(data, glm::value_ptr(m_target), 3 * sizeof(float));
//    std::memcpy(&data[3], glm::value_ptr(m_target), 3 * sizeof(float));
//    data[6] = m_fov;
    //        size_t size;
    //        size = sizeof(m_position);
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

glm::mat4 CameraWorld::viewMatrix() const
{
    return glm::lookAt(m_position, m_target, glm::vec3(0, 0, 1));
}

void CameraWorld::mousePressEvent(QMouseEvent *event)
{
    Camera::mousePressEvent(event);

        lastPos = event->pos();
}

//void CameraWorld::mouseReleaseEvent(QMouseEvent *event)
//{

//    if (event->button() == Qt::MiddleButton) {
//        m_middleClicked = false;
//    }
//}

void CameraWorld::mouseMoveEvent(QMouseEvent* event)
{
    Camera::mouseMoveEvent(event);

    if (m_middleClicked) {
        float dx = event->x() - lastPos.x();
        //    float dx = event->x();
        float dy = event->y() - lastPos.y();
        lastPos = event->pos();
        //    float dy = event->y();

        //    setCursorToCenter();
        //    qDebug() << dx << dy;
        if (m_shiftPressed) {
            processSliding(dx, dy);

        } else {
            processMouseMovement(dx, dy);
        }
    }
}

void CameraWorld::wheelEvent(QWheelEvent* event)
{
    Camera::wheelEvent(event);

    float dy = event->delta();

    processMouseScroll(dy);
    //    updateProjection();
}

glm::vec3 CameraWorld::target() const
{
    return m_target;
}
