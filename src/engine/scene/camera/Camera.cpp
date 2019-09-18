#include "Camera.h"

//Camera::Camera()
//{

//}
#include <QDebug>
#include <engine/scene/Scene.h>
#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/gtc/type_ptr.hpp>
#include <session/Session.h>

//static const Model * cameraModel = Scene::m_scene->m_cameraModel;

//Camera::Camera(float fov, const glm::vec3& position)
Camera::Camera(float fov)
    //    : m_target(target)
    //        : Object(std::move(MeshModel(g_resourcesPath + "models/camera/camera.obj")))
    : Object(g_resourcesPath + "models/camera/camera.obj")
    //    : Object(g_resourcesPath + "models/camera/camera.obj")
    , m_fov(fov)
//    , m_position(position)
{
    //    m_model.m_transform = transform;
    m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model->m_transform);
}

Camera::Camera(std::ifstream& file)
    //    : Object(g_resourcesPath + "models/camera/camera.obj")
    : Object(g_resourcesPath + "models/camera/camera.obj")
{
    //    Camera::Type type;

    Session::load(m_fov, file);
    //    Session::load(m_position, file);
    Session::load(m_model->m_transform, file);
    //    Session::load(m_model.m_transform, file);

    CameraStrategy::Type type;
    //    Session::loadEnum(file);
    type = static_cast<CameraStrategy::Type>(Session::loadEnum(file));
    switch (type) {
    case CameraStrategy::WORLD:
        m_cameraStrategy = new CameraWorld(file, m_model->m_transform);
        break;

    case CameraStrategy::FPS:
        m_cameraStrategy = new CameraFps(file, m_model->m_transform, m_fov);
        break;
    }
}

void Camera::save(std::ofstream& file)
{
    //    float data[4];

    //    Session::saveEnum(m_type, file);

    //    std::memcpy(data, glm::value_ptr(m_position), 3 * sizeof(float));
    //    data[3] = m_fov;

    //    file.write(reinterpret_cast<const char*>(&data), sizeof (data));
    Session::save(m_fov, file);
    //    Session::save(m_position, file);
    Session::save(m_model->m_transform, file);

    Session::saveEnum(m_cameraStrategy->m_type, file);
    //    Session::save(m_cameraStrategy, file);
    m_cameraStrategy->save(file);
    //    Session::save(m_target, file);
}

//void Camera::load(std::ifstream &file)
//{
//    float data[4];
//    file.read(reinterpret_cast<char*>(&data), sizeof (data));

//    m_position = glm::make_vec3(data);
//    m_fov = data[3];

////    Session::load(m_target, file);

//}
void Camera::setDefault()
{
    m_fov = 60.0f;

    //    m_cameraStrategy->setDefault();
    //    m_position = glm::vec3(200.0f, -200.0f, 200.0f);
    //    delete m_cameraStrategy;
    //    m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model.m_transform);
    switch (m_cameraStrategy->m_type) {
    case CameraStrategy::WORLD:
        m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model->m_transform);
        //        CameraWorld * cameraWorld = static_cast<CameraWorld*>(m_cameraStrategy);
        //        cameraWorld->m_target = glm::vec3(0.0f);
        break;

    case CameraStrategy::FPS:
        break;
    }
}

glm::mat4 Camera::viewMatrix()
{
    // question : return mat4 &&
    if (m_selected) {
        return glm::inverse(Scene::m_scene->m_worldTransform * m_model->m_transform * Scene::m_scene->m_localTransform);

    } else {
        return glm::inverse(m_model->m_transform);
    }
}

//void Camera::switchStrategy()
//{
//    glm::vec3 pos = position();
//    glm::vec3 target_ = target();

//    //        float fov = m_fov;

//}

void Camera::prepareHierarchy(ulong frameTime) const
{
    //    m_model.m_transform = glm::inverse(viewMatrix());
    m_model->prepareHierarchy(frameTime);
}

void Camera::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    m_model.draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
    m_model->draw(shader, dotCloud, localTransform, worldTransform);
    //    Scene::m_camera.d
    //    Scene::m_scene->m_cameraModel->draw(shader, dotCloud, localTransform, worldTransform);
    //    qDebug() << "draw camera";
    //    cameraModel->draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
}

void Camera::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model->draw(shader, localTransform, worldTransform);
    //    cameraModel->draw(shader, localTransform, worldTransform);
}

void Camera::updateBoundingBox() const
{
    //    m_model.m_transform = glm::inverse(viewMatrix());
    m_model->updateBoundingBox();
    //    Scene::m_scene
    //    cameraModel->updateBoundingBox(m_box);
}

void Camera::drawBoundingBox(const Shader& shader) const
{
    m_model->drawBoundingBox(shader);
    //    Scene::m_cameraModel->draw(shader, localTransform, worldTransform);
    //    cameraModel->drawBoundingBox(shader);
}

//void Camera::setDefault()
//{

//}

void Camera::setTarget(const glm::vec3& target)
{
    m_cameraStrategy->setTarget(target);

    //    m_cameraStrategy->setDefault();
    //    m_position = glm::vec3(200.0f, -200.0f, 200.0f);
    //    delete m_cameraStrategy;
    //    m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model.m_transform);
    //    switch (m_cameraStrategy->m_type) {
    //    case CameraStrategy::WORLD:
    //        static_cast<CameraWorld*>(m_cameraStrategy)->m_target = target;
    ////        cameraWorld->m_target = glm::vec3(0.0f);
    //        break;

    //    case CameraStrategy::FPS:
    //        break;

    //    }
    //}
}

void Camera::setFront(const glm::vec3& front)
{
    m_cameraStrategy->setFront(front);
}

glm::vec3 Camera::front() const
{
    return m_cameraStrategy->front();
}

glm::vec3 Camera::right() const
{
    return m_cameraStrategy->right();
}

glm::vec3 Camera::up() const
{
    return m_cameraStrategy->up();
}

glm::vec3 Camera::target() const
{
    return m_cameraStrategy->target();
}

const glm::vec3 Camera::position() const
{
    return m_model->m_transform[3];
}
