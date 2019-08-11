#ifndef BONEGEOMETRY_H
#define BONEGEOMETRY_H

#include <opengl/version.h>
#include <glm/glm.hpp>
#include <opengl/shader.h>
//#include <opengl/geometry/uvSphereGeometry.h>
#include "uvSphereGeometry.h"

class BoneGeometry
{
public:
    BoneGeometry();

    void draw(glm::mat4 model, const Shader & shader, glm::vec3 source, glm::vec3 destination) const;

private:
    void setup();

private:
    QOpenGLFunctionsCore * m_fun;

    UvSphereGeometry m_sphere;

    uint m_vao;
    uint m_vbo;
    uint m_ebo;
    uint m_nbo;
//    Shader * m_shader;


    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
//    std::vector<uint> m_indices;
    std::vector<glm::uvec3> m_indices;
};

#endif // BONEGEOMETRY_H
