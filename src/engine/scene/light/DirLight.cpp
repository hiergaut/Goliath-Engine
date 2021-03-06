#include "DirLight.h"

#include <engine/scene/Scene.h>
#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opengl/geometry/QuadGeometry.h>
#include <session/Session.h>

//const uint SHADOW_SIZE = 1024;
//const uint SHADOW_SIZE = 4096;
const uint SHADOW_SIZE = 8192;
//const uint SHADOW_SIZE = 16384;
const uint SHADOW_WIDTH = SHADOW_SIZE;
const uint SHADOW_HEIGHT = SHADOW_SIZE;
//const float NEAR_PLANE = 100.0f;
//const float FAR_PLANE = 5000.0f;

glm::vec3 DirLight::pos(const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    return (worldTransform * m_model->transform() * localTransform)[3];
}

void DirLight::draw(const Shader& shader, bool dotCloud, const Frustum& frustum, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    shader.setBool("userColor", true);

    if (shader.m_shade != Shader::Type::RENDERED) {

        Object::draw(shader, dotCloud, frustum, localTransform, worldTransform);
    }

    //    if (dotCloud) {
    //    if (m_selected) {
    //        if (shader.m_shade != Shader::Type::RENDERED) {

    if (shader.m_shade == Shader::Type::DEPTH) {
        //        shader.setBool("userColor", false);
        //        glPolygonMode(GL_FRONT, GL_FILL);
        glm::mat4 local = localTransform;
        //    local = glm::translate(local, glm::vec3(0.0f, 0.0f, 1.0f) * 100.0f);
        local = glm::scale(local, glm::vec3(1.0f) * 1000.0f);
        //    shader.use();
        shader.setMat4("model", worldTransform * m_model->transform() * local);

        //            shader.setBool("userColor", true);
        //            shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        //        shader.setBool("hasTexture", true);
//        shader.setBool("hasCubeMap", false);

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

    //    }
    //    shader.setBool("userColor", false);
}

void DirLight::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Object::draw(shader, localTransform, worldTransform);
}


//void DirLight::prepareHierarchy(ulong frameTime) const
void DirLight::prepareHierarchy(ulong frameTime, const glm::mat4 &localPoseTransform, const glm::mat4 &worldPoseTransform) const
{
    if (m_blink) {
        //    m_coeffBlink = std::fmax(std::cos((std::fabs(frameTime) * 0.01f)) * 10.0f, 0.0f);
        const ulong period = 1000;
        m_coeffBlink = std::fmax(frameTime & period - period / 2, 0.0f) * 0.1f;
    } else {
        m_coeffBlink = 0.0f;
    }
    //    qDebug() << m_coeffBlink;
}

//void DirLight::setSelected(bool selected)
//{
//    Object::setSelected(selected);
//    Light::setSelected(selected);

//}

DirLight::DirLight(const glm::vec3 position, const glm::vec3 direction, const glm::vec3 ambient, const glm::vec3 diffuse,
    const glm::vec3 specular)
    : Light(ambient, diffuse, specular)
    //    , Object(g_resourcesPath + "models/sun/sun.obj")
    , Object(g_resourcesPath + "models/light/sun/sun.obj")
//    , m_direction(direction)
//    , m_sphere(5000.0f)
{
    Object::m_type = Object::Type::DIR_LIGHT;
    Light::m_type = Light::Type::SUN;

    m_bias = 0.001f;

    //    m_sphere = new UvSphereGeometry(100, 100);
    //    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

    //    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    glm::mat4 modelMatrix(1.0f);
    //    glm::mat4 rotate = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f) + direction, glm::vec3(1.0f, 1.0f, 1.0f));

    modelMatrix = glm::lookAt(position + direction * 100.0f, position, glm::vec3(0.0f, 1.0f, 0.0f));
    //    modelMatrix = glm::translate(modelMatrix, position);
    //    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //    glm::vec3 up = glm::vec3
    //    m_model->m_transform = modelMatrix;
    setTransform(modelMatrix);
    //    m_model->setTransform(modelMatrix);
    //    updateBoundingBox();

    //    model = glm::rotate()
    initGL();
}

DirLight::DirLight(std::ifstream& file)
    //    : Object(g_resourcesPath + "models/sun/sun.obj")
    : Object(g_resourcesPath + "models/light/sun/sun.obj")
{
    Object::m_type = Object::Type::DIR_LIGHT;
    Light::m_type = Light::Type::SUN;

    Light::load(file);
    glm::mat4 transform;
    Session::load(transform, file);

    setTransform(std::move(transform));
    //    Session::load(m_direction, file);

    //    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

    //    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    //    glm::mat4 modelMatrix(1.0f);
    //    modelMatrix = glm::translate(modelMatrix, m_position);
    //    m_model->m_transform = modelMatrix;
    //    model = glm::rotate()
    initGL();
}

//DirLight::~DirLight()
//{
////    delete m_sphere;

//}

//void DirLight::load(std::ifstream &file)
//{
//    Session::load(m_direction, file);

//}

void DirLight::initGL()
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

Shader& DirLight::depthShader(const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    glViewport(200, 200, 100, 100);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    //    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glm::mat4 lightSpaceMatrix;
    //    float radius = 5000.0f;

    m_simpleDepthShader->use();
    m_simpleDepthShader->setMat4("lightSpaceMatrix", this->lightSpaceMatrix(localTransform));

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

bool DirLight::selected() const
{
    return Object::selected();
}

glm::mat4 DirLight::lightSpaceMatrix(const glm::mat4& localTransform) const
{
    glm::mat4 lightProjection, lightView;
    BoundingBox box = Scene::m_scene->m_box;

    //        float dist = glm::length(box.center() - pos(localTransform));
    //    float near = dist - box.radius();
    //    float far = dist + box.radius();
    const glm::vec3& center = box.center();
    const float& radius = box.radius();

    const glm::vec3& dir = direction(localTransform);
    //        glm::vec3 p = pos(localTransform, worldTransform);

    //        float dist = glm::length(pos(localTransform) - center);

//    const glm::vec3 & right = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
//    const glm::vec3 & up = glm::normalize(glm::cross(right, dir));

//    const glm::vec3 & min = box.m_bounds[0];
//    const glm::vec3 & max = box.m_bounds[1];

//    float yMax = std::max(glm::dot(up, min), glm::dot(up, max)) * 1.5f;
//    float yMin = std::min(glm::dot(up, min), glm::dot(up, max)) * 1.5f;
//    float xMax = std::max(glm::dot(right, min), glm::dot(right, max)) * 1.5f;
//    float xMin = std::min(glm::dot(right, min), glm::dot(right, max)) * 1.5f;
//    lightProjection = glm::ortho(xMin, xMax, yMin, yMax, 10.0f, 2.0f * radius);


    ///

    //    qDebug() << "radius " << radius;
    lightProjection = glm::ortho(-radius, radius, -radius, radius, 10.0f, 2.0f * radius);

    //    lightProjection = glm::ortho(-radius, radius, -radius, radius, 10.0f, 2.0f * radius);
    //        lightView = glm::lookAt(pos(localTransform), center, glm::vec3(0.0, 1.0, 0.0));
    //    lightView = viewMatrix();
    //    lightView = glm::lookAt(center -dir * dist, center, glm::vec3(0.0f, 1.0f, 0.0f));
    lightView = glm::lookAt(center - dir * radius, center, glm::vec3(0.0f, 1.0f, 0.0f));
    return lightProjection * lightView;
    //    return lightProjection * lightView;
}

void DirLight::save(std::ofstream& file) const
{
    Light::save(file);
    Session::save(transform(), file);

    //    Session::save(m_direction, file);
}

glm::vec3 DirLight::direction(const glm::mat4& localTransform) const
{
    //    glm::vec3 dir = glm::normalize(m_model.m_transform[0] + m_model.m_transform[1] + m_model.m_transform[2]);
    glm::vec3 sunUp = glm::normalize(glm::vec3(transform() * localTransform * -glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)));
    //    return glm::normalize(sunUp);
    m_coeffSunrise = glm::dot(sunUp, glm::vec3(0.0f, 0.0f, -1.0f));
    return sunUp;
    //    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

    //    glm::vec3 right = glm::normalize(glm::cross(sunUp, up));

    //    return dir;
}

//void DirLight::draw(const Shader &shader) const
//{

////    shader.setMat4("model", glm::mat4(1.0f));
////    m_sphere.draw(shader, glm::vec3(0.0f), 100.0f);
//    UvSphereGeometry::draw(shader, m_position, 100.0f);

//}

glm::mat4 DirLight::viewMatrix() const
{
    //        return transform();
    // question : return mat4 &&
    if (m_selected) {
        return glm::inverse(Scene::m_scene->m_worldTransform * transform() * Scene::m_scene->m_localTransform);
        //        return transform();

    } else {
        return glm::inverse(transform());
        //        return transform();
    }
}

uint DirLight::depthMap() const
{
    return m_depthMap;
}
