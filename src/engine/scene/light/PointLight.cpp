#include "PointLight.h"

//PointLight::PointLight()
//{

//}
#include <engine/scene/Scene.h>
#include <engine/scene/model/meshModel/MeshModel.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opengl/geometry/QuadGeometry.h>
#include <session/Session.h>

const uint SHADOW_SIZE = 1024;
//const uint SHADOW_SIZE = 8192;
//const uint SHADOW_SIZE = 16384;
const uint SHADOW_WIDTH = SHADOW_SIZE;
const uint SHADOW_HEIGHT = SHADOW_SIZE;
//const float NEAR_PLANE = 100.0f;
//const float FAR_PLANE = 5000.0f;

glm::vec3 PointLight::position(const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    return (worldTransform * m_model->transform() * localTransform)[3];
}

void PointLight::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    shader.setBool("userColor", true);
    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    Object::draw(shader, dotCloud, localTransform, worldTransform);
    //    shader.setVec4("color", glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
    shader.setBool("userColor", false);

    //        if (dotCloud) {
    if (m_selected) {
        if (shader.m_shade != Shader::Type::RENDERED) {

//            m_skyBoxShader->use();
//            shader.setBool("hasCube", true);
//            shader.setInt("skybox", 0);
//            shader.setVec3("cubeCenter", position(localTransform, worldTransform));
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthMap);
//            Object::draw(shader, dotCloud, localTransform, worldTransform);

//            shader.setBool("hasCube", false);

//            Object::draw(shader, dotCloud, localTransform, worldTransform);

            //            shader.setBool("hasTexture", true);
            //        shader.setBool("userColor", false);
            //        glPolygonMode(GL_FRONT, GL_FILL);

            //            for (uint i = 0; i < 6; ++i) {

//                            glm::mat4 local = localTransform;
//            //                //    local = glm::translate(local, glm::vec3(0.0f, 0.0f, 1.0f) * 100.0f);
//                            local = glm::scale(local, glm::vec3(1.0f) * 100.0f);
//            //                //    shader.use();
//                            shader.setMat4("model", worldTransform * m_model->transform() * local * m_viewMatrix[0]);
//            ////                shader.setMat4("model", m_model->transform() * m_viewMatrix[i] * local);
//            ////                shader.setMat4("model", worldTransform * m_model->transform() * local);

//                            glActiveTexture(GL_TEXTURE0);
//            //                //    shader.setBool("userColor", false);
//            //                //    shader.setVec4("color", glm::vec4(1.0f, 0, 0, 1));
//            //                //    shader.setBool("hasTexture", true);
//                            shader.setInt("texture_diffuse1", 0);
//            //                //                glBindTexture(GL_TEXTURE_2D, m_depthMap);
//                            glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthMap);
//                            QuadGeometry::draw();
//                            //    glActiveTexture(GL_TEXTURE0);
//            //            }
        }
    }
}

void PointLight::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    Object::draw(shader, localTransform, worldTransform);
}

PointLight::PointLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse,
    const glm::vec3 specular)
    : Light(ambient, diffuse, specular)
    //    , Object(g_resourcesPath + "models/sun/sun.obj")
    , Object(g_resourcesPath + "models/light/point/cube.obj")
//    , m_direction(direction)
//    , m_sphere(5000.0f)
{
    //    m_sphere = new UvSphereGeometry(100, 100);
    //    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

    //    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    //    glm::mat4 rotate = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f) + direction, glm::vec3(1.0f, 1.0f, 1.0f));

    //    modelMatrix = glm::lookAt(position + direction * 100.0f, position, glm::vec3(0.0f, 1.0f, 0.0f));
    //    modelMatrix = glm::translate(modelMatrix, position);
    //    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //    glm::vec3 up = glm::vec3
    //    m_model->m_transform = modelMatrix;
    setTransform(modelMatrix);
    //    m_model->setTransform(modelMatrix);
    //    updateBoundingBox();

    //    model = glm::rotate()
    initViewMatrix();
    initGL();

//    m_skyBoxShader = new Shader("skybox.vsh", "skybox.fsh");
//    m_skyBoxShader->use();
//    m_skyBoxShader->setInt("skybox", 0);
}

PointLight::PointLight(std::ifstream& file)
    //    : Object(g_resourcesPath + "models/sun/sun.obj")
    //    : Object(g_resourcesPath + "models/sun/sun.obj")
    : Object(g_resourcesPath + "models/light/point/cube.obj")
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
    initViewMatrix();
    initGL();
}

//PointLight::~PointLight()
//{
////    delete m_sphere;

//}

//void PointLight::load(std::ifstream &file)
//{
//    Session::load(m_direction, file);

//}

void PointLight::initGL()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    m_fun->glGenFramebuffers(1, &m_depthFbo);

    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthMap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
    //        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    m_fun->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    //        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    glEnable(GL_CULL_FACE);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //    m_simpleDepthShader = new Shader("shadow/dirlight_shadow_depth.vsh", "shadow/dirlight_shadow_depth.fsh");
    m_simpleDepthShader = new Shader("shadow/pointLight_shadows_depth.vsh", "shadow/pointLight_shadows_depth.fsh", "shadow/pointLight_shadows_depth.gsh");

    //    m_debugDepthQuad = new Shader("shadow/debug_quad.vsh", "shadow/debug_quad.fsh");
    //    m_debugDepthQuad->use();
    //    m_debugDepthQuad->setInt("depthMap", 0);
}

void PointLight::initViewMatrix()
{
    m_viewMatrix[0] = glm::lookAt(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    m_viewMatrix[1] = glm::lookAt(glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    m_viewMatrix[2] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_viewMatrix[3] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    m_viewMatrix[4] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    m_viewMatrix[5] = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
}

Shader& PointLight::depthShader(const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    //    glViewport(200, 200, 100, 100);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    //    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glm::mat4 lightSpaceMatrix;
    //    float radius = 5000.0f;

    //    m_simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix(localTransform));
    float near_plane = 1.0f;
    float far_plane = 5000.0f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    std::vector<glm::mat4> shadowTransforms;
    const glm::vec3& pos = position();
    for (uint i = 0; i < 6; ++i) {
        //        shadowTransforms.push_back(shadowProj * glm::translate(m_viewMatrix[i], pos));
        shadowTransforms.push_back(shadowProj * m_viewMatrix[i] * glm::translate(glm::mat4(1.0f), pos));
    }
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    //    shadowTransforms.push_back(shadowProj * glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    //    glViewport(100, 100, 200, 200);
    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);
    glClear(GL_DEPTH_BUFFER_BIT);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, woodTexture);
    //    renderScene(simpleDepthShader);
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_simpleDepthShader->use();
    for (unsigned int i = 0; i < 6; ++i)
        m_simpleDepthShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
    m_simpleDepthShader->setFloat("far_plane", far_plane);
    m_simpleDepthShader->setVec3("lightPos", pos);

    return *m_simpleDepthShader;
}

//glm::mat4 PointLight::lightSpaceMatrix(const glm::mat4& localTransform) const
//{
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
//    //    return lightProjection * lightView;
//}

void PointLight::save(std::ofstream& file) const
{
    Light::save(file);
    Session::save(transform(), file);

    //    Session::save(m_direction, file);
}

//glm::vec3 PointLight::direction(const glm::mat4& localTransform) const
//{
//    //    glm::vec3 dir = glm::normalize(m_model.m_transform[0] + m_model.m_transform[1] + m_model.m_transform[2]);
//    glm::vec3 sunUp = glm::vec3(transform() * localTransform * -glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
//    //    return glm::normalize(sunUp);
//    return sunUp;
//    //    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

//    //    glm::vec3 right = glm::normalize(glm::cross(sunUp, up));

//    //    return dir;
//}

//void PointLight::draw(const Shader &shader) const
//{

////    shader.setMat4("model", glm::mat4(1.0f));
////    m_sphere.draw(shader, glm::vec3(0.0f), 100.0f);
//    UvSphereGeometry::draw(shader, m_position, 100.0f);

//}

//glm::mat4 PointLight::viewMatrix() const
//{
//    //        return transform();
//    // question : return mat4 &&
//    if (m_selected) {
//        return glm::inverse(Scene::m_scene->m_worldTransform * transform() * Scene::m_scene->m_localTransform);
//        //        return transform();

//    } else {
//        return glm::inverse(transform());
//        //        return transform();
//    }
//}

uint PointLight::depthMap() const
{
    return m_depthMap;
}
