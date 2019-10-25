#include "DirLight.h"

#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opengl/geometry/QuadGeometry.h>
#include <session/Session.h>
#include <engine/scene/Scene.h>

const uint SHADOW_WIDTH = 1024;
const uint SHADOW_HEIGHT = 1024;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 10000.0f;

glm::vec3 DirLight::pos(const glm::mat4& localTransform, const glm::mat4& worldTransform)
{
    return (worldTransform * m_model->m_transform * localTransform)[3];
}

void DirLight::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Object::draw(shader, dotCloud, localTransform, worldTransform);

    glm::mat4 local = localTransform;
//    local = glm::translate(local, glm::vec3(0.0f, 0.0f, 1.0f) * 100.0f);
    local = glm::scale(local, glm::vec3(1.0f) * 1000.0f);
//    shader.use();
    shader.setMat4("model", worldTransform * m_model->m_transform * local);

    glActiveTexture(GL_TEXTURE0);
//    shader.setBool("userColor", false);
//    shader.setVec4("color", glm::vec4(1.0f, 0, 0, 1));
//    shader.setBool("hasTexture", true);
    shader.setInt("texture_diffuse1", 0);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);
    QuadGeometry::draw();
//    glActiveTexture(GL_TEXTURE0);
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

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //    glm::vec3 up = glm::vec3
    m_model->m_transform = modelMatrix;


    //    model = glm::rotate()
    initGL();
}

DirLight::DirLight(std::ifstream& file)
    //    : Object(g_resourcesPath + "models/sun/sun.obj")
    : Object(g_resourcesPath + "models/sun/sun.obj")
{
    Light::load(file);
    Session::load(m_model->m_transform, file);

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    m_fun->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_simpleDepthShader = new Shader("shadow/shadow_mapping_depth.vsh", "shadow/shadow_mapping_depth.fsh");

//    m_debugDepthQuad = new Shader("shadow/debug_quad.vsh", "shadow/debug_quad.fsh");
//    m_debugDepthQuad->use();
//    m_debugDepthQuad->setInt("depthMap", 0);
}

Shader &DirLight::depthShader(const glm::mat4 &localTransform, const glm::mat4 &worldTransform)
{
//    glViewport(200, 200, 100, 100);
//    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
//    glClear(GL_DEPTH_BUFFER_BIT);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float radius = 5000.0f;

    BoundingBox box = Scene::m_scene->m_box;

//    float nearPlane = Scene::m_scene

    lightProjection = glm::ortho(-radius, radius, -radius, radius, NEAR_PLANE, FAR_PLANE);
//    lightView = glm::lookAt(glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//    lightView = glm::lookAt(pos(localTransform, worldTransform), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightView = viewMatrix();
    lightSpaceMatrix = lightProjection * lightView;

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

void DirLight::save(std::ofstream& file) const
{
    Light::save(file);
    Session::save(m_model->m_transform, file);

    //    Session::save(m_direction, file);
}

glm::vec3 DirLight::direction(const glm::mat4& localTransform) const
{
    //    glm::vec3 dir = glm::normalize(m_model.m_transform[0] + m_model.m_transform[1] + m_model.m_transform[2]);
    glm::vec3 sunUp = glm::vec3(m_model->m_transform * localTransform * -glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
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

glm::mat4 DirLight::viewMatrix()
{
    // question : return mat4 &&
    if (m_selected) {
        return glm::inverse(Scene::m_scene->m_worldTransform * m_model->m_transform * Scene::m_scene->m_localTransform);

    } else {
        return glm::inverse(m_model->m_transform);
    }
}
