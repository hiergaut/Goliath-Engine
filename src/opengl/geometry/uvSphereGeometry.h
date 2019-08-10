#ifndef UVSPHEREGEOMETRY_H
#define UVSPHEREGEOMETRY_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <opengl/version.h>



class UvSphereGeometry
{
public:
    UvSphereGeometry(uint nbSlices);

//    void setup();
    void draw() const;


private:
    QOpenGLFunctionsCore * m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

//    ~UvSphereGeometry();

    uint m_nbSlices;
    uint m_nbRings;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<uint> m_indices;

    float m_radius = 10.0;
    uint m_vbo;
    uint m_vao;
    uint m_ebo;
    uint m_nbo;

};

#endif // UVSPHEREGEOMETRY_H
