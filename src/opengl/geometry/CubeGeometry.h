#ifndef CUBEGEOMETRY_H
#define CUBEGEOMETRY_H

#include <glm/glm.hpp>
#include <vector>
#include <opengl/version.h>

#include <opengl/shader.h>

class CubeGeometry
{
public:
    CubeGeometry();

    void draw() const;

private:
    void setupGL();

private:
    QOpenGLFunctionsCore * m_fun;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;

    std::vector<glm::uvec2> m_indices;

    uint m_vao;
    uint m_vbo;
    uint m_nbo;
    uint m_ebo;

    Shader * m_shader;
};

#endif // CUBEGEOMETRY_H
