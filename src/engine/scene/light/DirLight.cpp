#include "DirLight.h"

#include <engine/scene/Scene.h>
#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opengl/geometry/QuadGeometry.h>
#include <session/Session.h>

//const uint SHADOW_SIZE = 1024;
const uint SHADOW_SIZE = 8192;
const uint SHADOW_WIDTH = SHADOW_SIZE;
const uint SHADOW_HEIGHT = SHADOW_SIZE;
const float NEAR_PLANE = 100.0f;
const float FAR_PLANE = 5000.0f;

glm::vec3 DirLight::pos(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    return (worldTransform * m_model->transform() * localTransform)[3];
}

void DirLight::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Object::draw(shader, dotCloud, localTransform, worldTransform);

    if (m_selected) {
        glm::mat4 local = localTransform;
        //    local = glm::translate(local, glm::vec3(0.0f, 0.0f, 1.0f) * 100.0f);
        local = glm::scale(local, glm::vec3(1.0f) * 1000.0f);
        //    shader.use();
        shader.setMat4("model", worldTransform * m_model->transform() * local);

        glActiveTexture(GL_TEXTURE0);
        //    shader.setBool("userColor", false);
        //    shader.setVec4("color", glm::vec4(1.0f, 0, 0, 1));
        //    shader.setBool("hasTexture", true);
        shader.setInt("texture_diffuse1", 0);
        glBindTexture(GL_TEXTURE_2D, m_depthMap);
        QuadGeometry::draw();
        //    glActiveTexture(GL_TEXTURE0);
    }
}

void DirLight::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Object::draw(shader, localTransform, worldTransform);
}

DirLight::DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse,
    const glm::vec3 specular, const glm::vec3 direction)
    : Light(ambient, diffuse, specular)
    //    , Object(g_resourcesPath + "models/sun/sun.obj")
    , Object(g_resourcesPath + "models/sun/sun.obj")
//    , m_direction(direction)
//    , m_sphere(5000.0f)
{
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
    : Object(g_resourcesPath + "models/sun/sun.obj")
{
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

    m_simpleDepthShader = new Shader("shadow/shadow_mapping_depth.vsh", "shadow/shadow_mapping_depth.fsh");

    //    m_debugDepthQuad = new Shader("shadow/debug_quad.vsh", "shadow/debug_quad.fsh");
    //    m_debugDepthQuad->use();
    //    m_debugDepthQuad->setInt("depthMap", 0);
}

Shader& DirLight::depthShader(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    //    glViewport(200, 200, 100, 100);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    //    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float radius = 5000.0f;

    //    BoundingBox box = Scene::m_scene->m_box;
    //    float dist = glm::length(box.center() - pos(localTransform, worldTransform));
    //    float near = dist - box.radius();
    //    float far = dist + box.radius();

    ////    const glm::vec3 & dir = direction(localTransform);
    ///

    //    float min[3] = { 10e+9, 10e+9, 10e+9 };
    //    float max[3] = { -10e+9, -10e+9, -10e+9 };
    //    for (const glm::vec3& corner : box.corners(worldTransform * transform() * localTransform)) {
    ////                qDebug() << corner.r << corner.g << corner.b;
    ////        for (uint i = 0; i < 3; ++i) {
    //            min[0] = std::min(corner.x, min[0]);
    //            max[0] = std::max(corner.x, max[0]);
    //            min[1] = std::min(corner.y, min[1]);
    //            max[1] = std::max(corner.y, max[1]);
    //            min[2] = std::min(corner.z, min[2]);
    //            max[2] = std::max(corner.z, max[2]);
    ////        }
    //    }

    //    qDebug() << "---------------------------------";
    //    float nearPlane = Scene::m_scene
    //    for (uint i =0; i <3; ++i) {
    //        Q_ASSERT(min[i] < max[i]);
    //    }

    lightProjection = glm::ortho(-radius, radius, -radius, radius, NEAR_PLANE, FAR_PLANE);
    //    lightProjection = glm::ortho(-radius, radius, -radius, radius, near, far);
    //    qDebug() << "minx: " << min[0] << "maxx: " << max[0] << "diff: " << max[0] -min[0];
    //    qDebug() << "miny: " << min[1] << "maxy: " << max[1] << "diff: " << max[1] -min[1];
    //    qDebug() << "minz: " << min[2] << "maxz: " << max[2] << "diff: " << max[2] -min[2];
    //    lightProjection = glm::ortho(min[0], max[0], min[1], max[1], NEAR_PLANE, FAR_PLANE);
    //    lightProjection = glm::ortho(min[0], max[0], min[1], max[1], NEAR_PLANE, FAR_PLANE);
    //        lightView = glm::lookAt(glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    //    lightView = glm::lookAt(pos(localTransform, worldTransform), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightView = viewMatrix();
    //    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * (max[0] -min[0]) /2.0f);
    //    translate = glm::translate(translate, glm::vec3(0.0f, 1.0f, 0.0f) * (max[1] -min[1]) /2.0f);
    lightSpaceMatrix = lightProjection * lightView;
    //    lightSpaceMatrix = translate*  lightProjection * lightView;

    m_simpleDepthShader->use();
    m_simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

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

glm::mat4 DirLight::lightSpaceMatrix() const
{
    float radius = 5000.0f;
    glm::mat4 lightProjection = glm::ortho(-radius, radius, -radius, radius, NEAR_PLANE, FAR_PLANE);
    glm::mat4 lightView = viewMatrix();
    return lightProjection * lightView;
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
    glm::vec3 sunUp = glm::vec3(transform() * localTransform * -glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    return glm::normalize(sunUp);
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
