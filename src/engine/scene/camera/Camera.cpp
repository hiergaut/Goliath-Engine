#include "Camera.h"

//Camera::Camera()
//{

//}
#include <QDebug>
#include <engine/scene/Scene.h>
#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/gtc/type_ptr.hpp>
#include <session/Session.h>
#include <opengl/geometry/QuadGeometry.h>

//const uint SHADOW_SIZE = 1024;
//const uint SHADOW_SIZE = 2048;
const uint SHADOW_SIZE = 4096;
//const uint SHADOW_SIZE = 8192;
//const uint SHADOW_SIZE = 16384;
const uint SHADOW_WIDTH = SHADOW_SIZE;
const uint SHADOW_HEIGHT = SHADOW_SIZE;
//const float NEAR_PLANE = 100.0f;

//static const Model * cameraModel = Scene::m_scene->m_cameraModel;

//Camera::Camera(float fov, const glm::vec3& position)
Camera::Camera(float fov, uint id)
    //    : m_target(target)
    //        : Object(std::move(MeshModel(g_resourcesPath + "models/camera/camera.obj")))
    : Object(g_resourcesPath + "models/camera/camera.obj")
    //    : Object(g_resourcesPath + "models/camera/camera.obj")
    , m_fov(fov)
    , m_id(id)
//    , m_position(position)
{
    m_type = Object::Type::CAMERA;
    //    m_model.m_transform = transform;
    m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model->getTransform(), m_id, *m_model);
//    m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), *m_model, m_id);

//    updateBoundingBox();
    initGL();
}

Camera::Camera(std::ifstream& file, uint id)
    //    : Object(g_resourcesPath + "models/camera/camera.obj")
    : Object(g_resourcesPath + "models/camera/camera.obj")
    , m_id(id)
{
    m_type = Object::Type::CAMERA;
    //    Camera::Type type;

    Session::load(m_fov, file);
    //    Session::load(m_position, file);
    glm::mat4 transform;
    Session::load(transform, file);
    setTransform(std::move(transform));
    //    Session::load(m_model.m_transform, file);

    CameraStrategy::Type type;
    //    Session::loadEnum(file);
    type = static_cast<CameraStrategy::Type>(Session::loadEnum(file));
    switch (type) {
    case CameraStrategy::WORLD:
        m_cameraStrategy = new CameraWorld(file, m_model->getTransform(), m_id, *m_model);
//        m_cameraStrategy = new CameraWorld(file, *m_model, m_id);
        break;

    case CameraStrategy::FPS:
        m_cameraStrategy = new CameraFps(file, m_model->getTransform(), m_id, m_fov, *m_model);
//        m_cameraStrategy = new CameraFps(file, *m_model, m_id, m_fov);
        break;
    }

    Session::load(m_torchEnable, file);

    initGL();
//    updateBoundingBox();
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
    Session::save(m_model->transform(), file);

    Session::saveEnum(m_cameraStrategy->m_type, file);
    //    Session::save(m_cameraStrategy, file);
    m_cameraStrategy->save(file);
    //    Session::save(m_target, file);
    Session::save(m_torchEnable, file);
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
        m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), m_model->getTransform(), m_id, *m_model);
//        m_cameraStrategy = new CameraWorld(glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f), *m_model, m_id);
        //        CameraWorld * cameraWorld = static_cast<CameraWorld*>(m_cameraStrategy);
        //        cameraWorld->m_target = glm::vec3(0.0f);
        break;

    case CameraStrategy::FPS:
        break;
    }
}

glm::mat4 Camera::viewMatrix() const
{
    // question : return mat4 &&
    if (m_selected) {
        return glm::inverse(Scene::m_scene->m_worldTransform * m_model->transform() * Scene::m_scene->m_localTransform);

    } else {
        return glm::inverse(m_model->transform());
    }
}

glm::vec3 Camera::direction(const glm::mat4 &localTransform) const
{
    //    glm::vec3 dir = glm::normalize(m_model.m_transform[0] + m_model.m_transform[1] + m_model.m_transform[2]);
    glm::vec3 sunUp = glm::vec3(transform() * localTransform * -glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    //    return glm::normalize(sunUp);
    return sunUp;
    //    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

    //    glm::vec3 right = glm::normalize(glm::cross(sunUp, up));

}

glm::vec3 Camera::position(const glm::mat4 &localTransform, const glm::mat4 &worldTransform) const
{
    return (worldTransform * m_model->transform() * localTransform)[3];


}

//void Camera::switchStrategy()
//{
//    glm::vec3 pos = position();
//    glm::vec3 target_ = target();

//    //        float fov = m_fov;

//}

//void Camera::prepareHierarchy(ulong frameTime) const
void Camera::prepareHierarchy(ulong frameTime, const glm::mat4 &localPoseTransform, const glm::mat4 &worldPoseTransform) const
{
    //    m_model.m_transform = glm::inverse(viewMatrix());
    m_model->prepareHierarchy(frameTime, localPoseTransform, worldPoseTransform);
}

void Camera::draw(const Shader& shader, bool dotCloud, const Frustum &frustum, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    m_model.draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
    if (m_torchEnable) {
            shader.setBool("userColor", true);
            shader.setVec4("color", glm::vec4(1.0f));
    }
    Object::draw(shader, dotCloud, frustum, localTransform, worldTransform);
    if (m_torchEnable) {
            shader.setBool("userColor", false);
//            shader.setVec4("color", glm::vec4(1.0f));
    }
//    m_model->draw(shader, dotCloud, localTransform, worldTransform);
    //    Scene::m_camera.d
    //    Scene::m_scene->m_cameraModel->draw(shader, dotCloud, localTransform, worldTransform);
    //    qDebug() << "draw camera";
    //    cameraModel->draw(shader, dotCloud, localTransform, glm::inverse(viewMatrix()) * worldTransform);
    if (shader.m_shade == Shader::Type::DEPTH) {
        //        shader.setBool("userColor", false);
        //        glPolygonMode(GL_FRONT, GL_FILL);
        glm::mat4 local = localTransform;
        //    local = glm::translate(local, glm::vec3(0.0f, 0.0f, 1.0f) * 100.0f);
        local = glm::scale(local, glm::vec3(1.0f) * 50.0f);
        //    shader.use();
        shader.setMat4("model", worldTransform * m_model->transform() * local);

        //    shader.setBool("userColor", false);
        //    shader.setVec4("color", glm::vec4(1.0f, 0, 0, 1));
//        shader.setBool("has_texture_diffuse", true);
//        shader.setInt("texture_diffuse", 5);
        shader.setBool("hasDepthMap", true);
        shader.setInt("depthMap", 20);
        glActiveTexture(GL_TEXTURE20);
        glBindTexture(GL_TEXTURE_2D, m_depthMap);
        QuadGeometry::draw();
//        shader.setBool("has_texture_diffuse", false);
        shader.setBool("hasDepthMap", false);
//        shader.setBool("hasTexture", false);
        //    glActiveTexture(GL_TEXTURE0);
    }
}

void Camera::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model->draw(shader, localTransform, worldTransform);
    //    cameraModel->draw(shader, localTransform, worldTransform);
}

void Camera::updateBoundingBox() const
{
//    updateBoundingBox();
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

void Camera::initGL()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    m_fun->glGenFramebuffers(1, &m_depthFbo);

    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    m_fun->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    //        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    glEnable(GL_CULL_FACE);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_simpleDepthShader = new Shader("shadow/dirlight_shadow_depth.vsh", "shadow/dirlight_shadow_depth.fsh");

    //    m_debugDepthQuad = new Shader("shadow/debug_quad.vsh", "shadow/debug_quad.fsh");
    //    m_debugDepthQuad->use();
    //    m_debugDepthQuad->setInt("depthMap", 0);
}


Shader& Camera::depthShader(const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    glViewport(200, 200, 100, 100);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    //    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glm::mat4 lightSpaceMatrix;
    //    float radius = 5000.0f;

    m_simpleDepthShader->use();
    m_simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix(localTransform));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    //    glViewport(100, 100, 200, 200);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, woodTexture);
    //    renderScene(simpleDepthShader);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return *m_simpleDepthShader;
}


//void Camera::updateNearestPointLights()
//{

//}

glm::mat4 Camera::lightSpaceMatrix(const glm::mat4& localTransform) const
{
//    glm::mat4 lightProjection, lightView;
//    BoundingBox box = Scene::m_scene->m_box;

//    //        float dist = glm::length(box.center() - pos(localTransform));
//    //    float near = dist - box.radius();
//    //    float far = dist + box.radius();
//    const glm::vec3& center = box.center();
//    const float& radius = box.radius();

//    const glm::vec3& dir = direction(localTransform);
//    //        glm::vec3 p = pos(localTransform, worldTransform);

//    //        float dist = glm::length(pos(localTransform) - center);

//    ///

//    lightProjection = glm::ortho(-radius, radius, -radius, radius, 10.0f, 2.0f * radius);
//    //        lightView = glm::lookAt(pos(localTransform), center, glm::vec3(0.0, 1.0, 0.0));
//    //    lightView = viewMatrix();
//    //    lightView = glm::lookAt(center -dir * dist, center, glm::vec3(0.0f, 1.0f, 0.0f));
//    lightView = glm::lookAt(center - dir * radius, center, glm::vec3(0.0f, 1.0f, 0.0f));
//    return lightProjection * lightView;
    //    return lightProjection * lightView;
    float near_plane = 100.0f;
    float far_plane = 2000.0f;
    glm::mat4 projection = glm::perspective(glm::radians(40.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    return projection * viewMatrix();

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

//const glm::vec3 Camera::position() const
//{
//    return m_model->transform()[3];
//}

uint Camera::depthMap() const
{
    return m_depthMap;
}
