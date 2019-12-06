#ifndef TRIANGLEGEOMETRY_H
#define TRIANGLEGEOMETRY_H

#include <glm/glm.hpp>
#include <opengl/shader.h>
#include <opengl/version.h>


class TriangleGeometry
{
public:
//    TriangleGeometry();
    static void initializeGL();

    static void draw(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2);
    //    void drawLine(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const;

    //    void setVP(const glm::mat4 & viewMatrix, const glm::mat4 &projectionMatrix) const;

    static void draw(const std::vector<glm::vec3> &triangles);
private:
    static QOpenGLFunctionsCore* m_fun;

    //    UvSphereGeometry m_sphere;

    static uint m_vao;
    static uint m_vbo;

    static const uint MAX_TRIANGLES = 100000;
    //    uint m_vao2;
};

#endif // TRIANGLEGEOMETRY_H
