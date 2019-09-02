#ifndef LINEGEOMETRY_H
#define LINEGEOMETRY_H

#include <opengl/version.h>
#include <glm/glm.hpp>
#include <opengl/shader.h>

class LineGeometry
{
public:
//    LineGeometry();
//    void updateShader(const MainWindow3dView & view) const;
    static void initializeGL();

static void draw(const glm::mat4 & modelMatrix, const Shader & shader, glm::vec3 source, glm::vec3 destination);
//    void drawLine(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const;

//    void setVP(const glm::mat4 & viewMatrix, const glm::mat4 &projectionMatrix) const;

private:

private:
    static QOpenGLFunctionsCore * m_fun;

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
//    std::vector<uint> m_indices;
//    std::vector<glm::uvec3> m_indices;
//    std::vector<glm::uvec2> m_indicesLine;
};

#endif // LINEGEOMETRY_H
