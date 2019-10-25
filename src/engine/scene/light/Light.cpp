#include "Light.h"

#include <session/Session.h>
//#include <opengl/geometry/QuadGeometry.h>
//#include <engine/scene/Scene.h>
//Light::Light()
//{

//}

//Light::Light()
//{

//}


Light::Light(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular)
    //    : m_position(position)
    : m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular)
{
//    m_nearPlane = 1.0f;
//    m_farPlane = 7.5f;

//    initGL();
    //    m_cameraModel = new Model(g_resourcesPath + "models/camera/camera.obj");
}

void Light::load(std::ifstream& file)
{
    //    Session::load(m_position, file);
    Session::load(m_ambient, file);
    Session::load(m_diffuse, file);
    Session::load(m_specular, file);

//    initGL();
}

void Light::save(std::ofstream& file) const
{
    //    Session::save(m_position, file);
    Session::save(m_ambient, file);
    Session::save(m_diffuse, file);
    Session::save(m_specular, file);
}

//Light::Light(const glm::vec3 position)
//    : m_position(position)
//{

//}

//void Light::updateShadowMap()
//{
//}

//Shader& Light::depthShader()

//void Light::showDepth()
//{
//    glViewport(1500, 600, 400, 400);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    glClearColor(0.0f, 1.0f, 0.0f, 0.5f);

//    // render Depth map to quad for visual debugging
//    // ---------------------------------------------
//    m_debugDepthQuad->use();
////    m_debugDepthQuad->setInt("depthMap", 0);
//    m_debugDepthQuad->setFloat("near_plane", NEAR_PLANE);
//    m_debugDepthQuad->setFloat("far_plane", FAR_PLANE);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_depthMap);
////    renderQuad();
//    QuadGeometry::draw();
//}

//void Light::renderQuad()
//{
//    if (quadVAO == 0)
//    {
//        float quadVertices[] = {
//            // positions        // texture Coords
//            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//        };
//        // setup plane VAO
//        m_fun->glGenVertexArrays(1, &quadVAO);
//        m_fun->glGenBuffers(1, &quadVBO);
//        m_fun->glBindVertexArray(quadVAO);
//        m_fun->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        m_fun->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        m_fun->glEnableVertexAttribArray(0);
//        m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        m_fun->glEnableVertexAttribArray(1);
//        m_fun->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    }
//    m_fun->glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    m_fun->glBindVertexArray(0);
//}

