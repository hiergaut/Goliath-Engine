#ifndef SCREENQUADGEOMETRY_H
#define SCREENQUADGEOMETRY_H

#include <glm/glm.hpp>
#include <vector>
#include <opengl/version.h>

#include <opengl/shader.h>


class ScreenQuadGeometry
{
public:
//    ScreenQuadGeometry();

    static void initializeGL();

    static void draw();

//    void initializeGL();

private:
//    void init();

private:
    static QOpenGLFunctionsCore * m_fun;
//    std::vector<glm::vec3> m_vertices;
//    std::vector<glm::vec3> m_normals;

//    std::vector<glm::uvec2> m_indices;

    static uint m_vao;
//    uint m_vbo;
//    uint m_nbo;
};

#endif // SCREENQUADGEOMETRY_H
