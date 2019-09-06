#ifndef AXISGEOMETRY_H
#define AXISGEOMETRY_H

#include <glm/glm.hpp>
#include <opengl/shader.h>
#include <opengl/version.h>


class AxisGeometry
{
public:
//    AxisGeometry();
    static void initializeGL();

    static void draw(const glm::mat4& modelMatrix, const Shader& shader);
    //    void drawLine(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const;

    //    void setVP(const glm::mat4 & viewMatrix, const glm::mat4 &projectionMatrix) const;

private:
    static QOpenGLFunctionsCore* m_fun;

    //    UvSphereGeometry m_sphere;

    static uint m_vao;
    //    uint m_vao2;

    //    uint m_vbo;
    //    uint m_ebo;
    //    uint m_ebo2;
    //    uint m_nbo;

    //    Shader * m_shader;

    //    std::vector<glm::vec3> m_vertices;
    //    std::vector<glm::vec3> m_normals;
};

#endif // AXISGEOMETRY_H
