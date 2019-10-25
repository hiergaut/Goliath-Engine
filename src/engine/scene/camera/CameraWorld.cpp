#include "CameraWorld.h"

#include <engine/scene/Scene.h>
#include <session/Session.h>

const float accuracyRotate = 0.01f;
const float accuracyMove = 0.001f;
const float accuracySlide = 1.0f;

//CameraWorld::CameraWorld()

//    : Camera(60.0f, glm::vec3(100.0f, 100.0f, 100.0f))
//    , m_target(glm::vec3(0.0f, 0.0f, 0.0f))
//{
//    m_type = WORLD;
//}

CameraWorld::CameraWorld(std::ifstream& file, glm::mat4 modelTransform)
    : CameraStrategy(modelTransform)
//    : CameraStrategy(file)
{
    Session::load(m_target, file);
    m_type = WORLD;
}

CameraWorld::CameraWorld(const glm::vec3& position, glm::vec3 target, glm::mat4 modelTransform)
    : CameraStrategy(modelTransform)
    , m_target(target)
//    : m_position { position }
//    , m_target { target }
{
    m_type = WORLD;

    m_modelTransform = glm::inverse(glm::lookAt(position, target, m_up));

    //        updateCameraVectors();
}

void CameraWorld::processMouseMovement(float xoffset, float yoffset)
{
    //    glm::vec3 v = m_position - m_target;
    //    glm::vec3 front = m_position - m_target;
    glm::vec3 front = glm::vec3(m_modelTransform[3]) - m_target;
    float dist = glm::length(front);
    front = glm::normalize(front);

    //        glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
    //    glm::vec3 up;
    glm::vec3 right;
    //    if (front.z > 0) {
    //    if (m_reverse) {
    //        //        right = -right;
    //        up = glm::vec3(0.0f, 0.0f, -1.0f);
    //        //        right = glm::cross(up, front);
    //        //    yoffset = -yoffset;
    //    } else {
    //        up = glm::vec3(0.0f, 0.0f, 1.0f);
    //    }
    //        if (m_reverse) {
    //            m_up = glm::vec3(0.0f, 0.0f, -1.0f);
    //            //            yoffset = -yoffset;
    //        } else {
    //            m_up = glm::vec3(0.0f, 0.0f, 1.0f);
    //        }

    right = glm::cross(front, m_up);

    if (!m_yUp) {
        if (glm::length(right) < 0.1f) {
            //        qDebug() << "fuck " << cpt++;
            //        if (!m_yUp) {
            m_reverse = !m_reverse;
            //        m_up = -m_up;
            updateUpAfterReverse();
            yoffset = 40.0f;
            if (m_reverse) {
                //            m_up = glm::vec3(0.0f, 0.0f, -1.0f);
                //            yoffset = -yoffset;
            } else {
                //            m_up = glm::vec3(0.0f, 0.0f, 1.0f);
                yoffset = -yoffset;
            }
            if (front.z < 0) {
                xoffset = glm::radians(180.0f) * 1.0f / accuracyRotate;
            }
            //        }
        }
    }

    //        qDebug() << glm::length(right);
    right = glm::normalize(right);
    //    if (m_reverse) {
    //        //        right = -right;

    //    } else {
    //        //        right = -right;
    //        //        yoffset = -yoffset;
    //    }
    if (m_yUp) {
        //        m_up = g
        m_yUp = false;
        m_reverse = yoffset > 0;
        //        if (m_reverse) {
        //            //            m_up = glm::vec3()
        //            m_up = glm::vec3(0.0f, 0.0f, -1.0f);
        //        } else {
        //            m_up = glm::vec3(0.0f, 0.0f, 1.0f);
        //            //            yoffset = 20.0f;
        //        }
        updateUpAfterReverse();
        yoffset = 40.0f * ((yoffset > 0) ? (1.0f) : (-1.0f));
    }

    //    glm::vec3 right = glm::cross(front, up);
    //    if (glm::length(xy) > 0.1) {
    glm::mat4 m(1.0);
    m = glm::rotate(m, -xoffset * accuracyRotate, m_up);
    m = glm::rotate(m, yoffset * accuracyRotate, right);

    front = m * glm::vec4(front, 1.0);
    glm::vec3 newPosition = front * dist + m_target;

    m_modelTransform = glm::inverse(glm::lookAt(newPosition, m_target, m_up));
    //    m_model. = front * dist + m_target;

    //    }

    //    qDebug() << "[CameraWorld]" << this << "processMouseMovement" << m_position.x << m_position.y << m_position.z;
}

void CameraWorld::processMouseScroll(float yoffset)
{
    //    glm::vec3 front = m_target - m_position;
    glm::vec4& translate = m_modelTransform[3];
    glm::vec3 position = glm::vec3(translate);
    glm::vec3 front = m_target - position;
    //    m_position += accuracyMove * front * yoffset;
    glm::vec3 newPosition = position += accuracyMove * front * yoffset;

    // question : optim
    translate.x = newPosition.x;
    translate.y = newPosition.y;
    translate.z = newPosition.z;
}

void CameraWorld::processSliding(float dx, float dy)
{
    glm::vec4& translate = m_modelTransform[3];

    glm::vec3 position = glm::vec3(translate);

    //    glm::vec3 front = m_target - m_position;
    glm::vec3 front = m_target - position;
    glm::vec3 right = glm::normalize(glm::cross(front, m_up));
    glm::vec3 up = glm::normalize(glm::cross(front, right));

    glm::vec3 slide = accuracySlide * (right * -dx + up * -dy);
    position += slide;
    m_target += slide;

    translate.x = position.x;
    translate.y = position.y;
    translate.z = position.z;
}

void CameraWorld::updateUpAfterReverse()
{

    if (m_reverse) {
        //            m_up = glm::vec3()
        m_up = glm::vec3(0.0f, 0.0f, -1.0f);
    } else {
        m_up = glm::vec3(0.0f, 0.0f, 1.0f);
        //            yoffset = 20.0f;
    }
}

//void CameraWorld::load(std::ifstream& file)
//{
//    Camera::load(file);
//    //    qDebug() << "[CameraWorld]" << this << "load" << m_position.x << m_position.y << m_position.z;
////    float data[3];
//    //        size_t size;
//    //        size = sizeof(m_position);
////    file.read(reinterpret_cast<char*>(&data), sizeof(data));

//    //    m_position = glm::make_vec3(data);
////    m_target = glm::make_vec3(data);
//    //    m_fov = data[6];

//    //    qDebug() << "[CAMERA WORLD] load" << this;
//    //    qDebug() << m_position.x << m_position.y << m_position.z;
//    //    qDebug() << m_target.x << m_target.y << m_target.z;
//    //    qDebug() << m_fov;
//    Session::load(m_target, file);
//}

void CameraWorld::save(std::ofstream& file)
{
//    CameraStrategy::save(file);
    //    qDebug() << "[CameraWorld]" << this << "write" << m_position.x << m_position.y << m_position.z;
    //        m_position.x = 1.0f;
    //    glm::vec3 position = glm::vec3(-10, -10, -10);
    //        m_position.x = 1.0;
    //    qDebug() << "[CAMERA WORLD] write" << this;
    //    qDebug() << m_position.x << m_position.y << m_position.z;
    //    qDebug() << m_target.x << m_target.y << m_target.z;
    //    qDebug() << m_fov << "loaded";

    //    float data[3];
    //    std::memcpy(data, glm::value_ptr(m_target), 3 * sizeof(float));
    //    //    std::memcpy(&data[3], glm::value_ptr(m_target), 3 * sizeof(float));
    //    //    data[6] = m_fov;
    //    //        size_t size;
    //    //        size = sizeof(m_position);
    //    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
    Session::save(m_target, file);
}

//glm::mat4 CameraWorld::viewMatrix() const
//{
//    //    if (m_reverse) {
//    //    return glm::lookAt(m_position, m_target, m_up);
//    if (m_selected) {
//        return glm::inverse(Scene::m_scene->m_worldTransform * m_model.m_transform * Scene::m_scene->m_localTransform);

//    } else {
//        return glm::inverse(m_model.m_transform);
//    }

//    //    } else {
//    //        return glm::lookAt(m_position, m_target, glm::vec3(0.0f, 0.0f, 1.0f));
//    //    }
//}

void CameraWorld::mousePressEvent(QMouseEvent* event)
{
    CameraStrategy::mousePressEvent(event);

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
    CameraStrategy::mouseMoveEvent(event);

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
    CameraStrategy::wheelEvent(event);

    float dy = event->delta();

    processMouseScroll(dy);
    //    updateProjection();
}

void CameraWorld::setTarget(const glm::vec3 &target)
{
    m_target = target;

    m_modelTransform = glm::inverse(glm::lookAt(glm::vec3(m_modelTransform[3]), m_target, m_up));
}

//void CameraWorld::setDefault()
//{

//    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
//}

glm::vec3 CameraWorld::target() const
{
    return m_target;
}

glm::vec3 CameraWorld::up() const
{
    glm::vec3 m_position = glm::vec3(m_modelTransform[3]);

    glm::vec3 front = glm::normalize(m_target - m_position);
    glm::vec3 up;
    //    if (m_reverse) {
    //        //        right = -right;
    //        up = glm::vec3(0.0f, 0.0f, -1.0f);
    //        //        right = glm::cross(up, front);
    //        //    yoffset = -yoffset;
    //    } else {
    //        up = glm::vec3(0.0f, 0.0f, 1.0f);
    //    }
    glm::vec3 right = glm::normalize(glm::cross(m_up, front));

    up = glm::normalize(glm::cross(front, right));
    return up;
}

glm::vec3 CameraWorld::right() const
{
    glm::vec3 m_position = glm::vec3(m_modelTransform[3]);

    glm::vec3 front = glm::normalize(m_target - m_position);
    //    glm::vec3 up;
    //    if (m_reverse) {
    //        //        right = -right;
    //        up = glm::vec3(0.0f, 0.0f, -1.0f);
    //        //        right = glm::cross(up, front);
    //        //    yoffset = -yoffset;
    //    } else {
    //        up = glm::vec3(0.0f, 0.0f, 1.0f);
    //    }
    glm::vec3 right = glm::normalize(glm::cross(m_up, front));
    return right;
}

glm::vec3 CameraWorld::front() const
{
    glm::vec3 m_position = glm::vec3(m_modelTransform[3]);

    glm::vec3 front = glm::normalize(m_target - m_position);
    return front;
}

void CameraWorld::setFront(const glm::vec3& front)
{
    glm::vec3 m_position = glm::vec3(m_modelTransform[3]);

    float dist = glm::length(m_target - m_position);

    m_position = m_target - front * dist;
    //    if (front.z < -0.5) {
    if (front == glm::vec3(0.0f, 0.0f, -1.0f)) {
        m_up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_yUp = true;
    } else {
        m_yUp = false;
        updateUpAfterReverse();
    }

    m_modelTransform = glm::inverse(glm::lookAt(m_position, m_target, m_up));
}
