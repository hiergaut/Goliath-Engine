#include "CameraWorld.h"

CameraWorld::CameraWorld(glm::vec3 position, glm::vec3 target)
    : m_position { position }
    , m_target { target }
{

    //        updateCameraVectors();
}

glm::mat4 CameraWorld::getViewMatrix() const
{
    return glm::lookAt(m_position, m_target, glm::vec3(0, 0, 1));
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

float CameraWorld::getFov() const
{
    return m_fov;
}

void CameraWorld::load(std::ifstream& file)
{
    //    qDebug() << "[CameraWorld]" << this << "load" << m_position.x << m_position.y << m_position.z;
    float data[7];
    //        size_t size;
    //        size = sizeof(m_position);
    file.read(reinterpret_cast<char*>(&data), sizeof(data));

    m_position = glm::make_vec3(data);
    m_target = glm::make_vec3(&data[3]);
    m_fov = data[6];

    //    qDebug() << "[CAMERA WORLD] load" << this;
    //    qDebug() << m_position.x << m_position.y << m_position.z;
    //    qDebug() << m_target.x << m_target.y << m_target.z;
    //    qDebug() << m_fov;
}
void CameraWorld::save(std::ofstream& file)
{
    //    qDebug() << "[CameraWorld]" << this << "write" << m_position.x << m_position.y << m_position.z;
    //        m_position.x = 1.0f;
    //    glm::vec3 position = glm::vec3(-10, -10, -10);
    //        m_position.x = 1.0;
    //    qDebug() << "[CAMERA WORLD] write" << this;
    //    qDebug() << m_position.x << m_position.y << m_position.z;
    //    qDebug() << m_target.x << m_target.y << m_target.z;
    //    qDebug() << m_fov << "loaded";

    float data[7];
    std::memcpy(data, glm::value_ptr(m_position), 3 * sizeof(float));
    std::memcpy(&data[3], glm::value_ptr(m_target), 3 * sizeof(float));
    data[6] = m_fov;
    //        size_t size;
    //        size = sizeof(m_position);
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

glm::vec3 CameraWorld::getPosition() const
{
    return m_position;
}
