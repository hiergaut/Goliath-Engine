#include "Camera.h"

//Camera::Camera()
//{

//}
#include <QDebug>
#include <engine/scene/Scene.h>
#include <glm/gtc/type_ptr.hpp>
#include <session/Session.h>

//static const Model * cameraModel = Scene::m_scene->m_cameraModel;

//Camera::Camera(float fov, const glm::vec3& position)
Camera::Camera(float fov)
    //    : m_target(target)
    //    : Object(std::move(Model(g_resourcesPath + "models/camera/camera.obj")))
    : Object(g_resourcesPath + "models/camera/camera.obj")
    , m_fov(fov)
//    , m_position(position)
{
//    m_model.m_transform = transform;
}

Camera::Camera(std::ifstream& file)
    : Object(g_resourcesPath + "models/camera/camera.obj")
{
    Session::load(m_fov, file);
//    Session::load(m_position, file);
    Session::load(m_model.m_transform, file);
//    Session::load(m_model.m_transform, file);
}

//void Camera::load(std::ifstream &file)
//{
//    float data[4];
//    file.read(reinterpret_cast<char*>(&data), sizeof (data));

//    m_position = glm::make_vec3(data);
//    m_fov = data[3];

////    Session::load(m_target, file);

//}

void Camera::save(std::ofstream& file)
{
    //    float data[4];

    //    std::memcpy(data, glm::value_ptr(m_position), 3 * sizeof(float));
    //    data[3] = m_fov;

    //    file.write(reinterpret_cast<const char*>(&data), sizeof (data));
    Session::save(m_fov, file);
//    Session::save(m_position, file);
    Session::save(m_model.m_transform, file);

    //    Session::save(m_target, file);
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

void Camera::focusInEvent(QFocusEvent* event)
{
    m_shiftPressed = false;
}

void Camera::resizeEvent(QResizeEvent* event)
{
}

void Camera::setDefault()
{
    m_fov = 60.0f;
//    m_position = glm::vec3(200.0f, -200.0f, 200.0f);
}

void Camera::prepareHierarchy(ulong frameTime) const
{
//    m_model.m_transform = glm::inverse(viewMatrix());
    m_model.prepareHierarchy(frameTime);

}

float Camera::fov() const
{
    return m_fov;
}

const glm::vec3 Camera::position() const
{
    return glm::vec3(m_model.m_transform[3]);
//    return m_position;
}

void Camera::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
//    m_model.draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
    m_model.draw(shader, dotCloud, localTransform,  worldTransform);
    //    Scene::m_camera.d
    //    Scene::m_scene->m_cameraModel->draw(shader, dotCloud, localTransform, worldTransform);
    //    qDebug() << "draw camera";
    //    cameraModel->draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
}

void Camera::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model.draw(shader, localTransform, worldTransform);
    //    cameraModel->draw(shader, localTransform, worldTransform);
}

void Camera::updateBoundingBox() const
{
//    m_model.m_transform = glm::inverse(viewMatrix());
    m_model.updateBoundingBox();
    //    Scene::m_scene
    //    cameraModel->updateBoundingBox(m_box);
}

void Camera::drawBoundingBox(const Shader& shader) const
{
    m_model.drawBoundingBox(shader);
    //    Scene::m_cameraModel->draw(shader, localTransform, worldTransform);
    //    cameraModel->drawBoundingBox(shader);
}
