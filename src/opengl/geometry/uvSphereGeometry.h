#ifndef UVSPHEREGEOMETRY_H
#define UVSPHEREGEOMETRY_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <opengl/version.h>

#include <opengl/shader.h>


class UvSphereGeometry
{
public:
//    UvSphereGeometry(float radius, uint nbSlices = 10);

//    void setup();
    static void initializeGL();
    static void draw(const Shader & shader, const glm::vec3 & position, float radius);
    static void draw();


private:
    static QOpenGLFunctionsCore * m_fun;
//    = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

//    ~UvSphereGeometry();

//    float m_radius;
//    uint m_nbSlices;
//    uint m_nbRings;
//    std::vector<glm::vec3> m_vertices;
//    std::vector<glm::vec3> m_normals;
//    std::vector<uint> m_indices;

//    uint m_vbo;
    static uint m_vao;
    static uint m_nbIndices;
//    uint m_ebo;
//    uint m_nbo;

};

#endif // UVSPHEREGEOMETRY_H
