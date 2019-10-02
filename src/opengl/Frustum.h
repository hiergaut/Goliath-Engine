#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Plane.h"
#include <glm/glm.hpp>
#include <opengl/shader.h>

class Frustum
{
public:
    enum Type {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        Z_NEAR,
        Z_FAR
    };

    Plane m_planes[6];
    mutable bool m_hits[6];
//    Plane m_top;
//    Plane m_bottom;
//    Plane m_right;
//    Plane m_left;
//    Plane m_zNear;
//    Plane m_zFar;
//    float m_zNear;
//    float m_zFar;

    glm::vec3 m_ntl;
    glm::vec3 m_ntr;
    glm::vec3 m_nbl;
    glm::vec3 m_nbr;

    glm::vec3 m_ftl;
    glm::vec3 m_ftr;
    glm::vec3 m_fbl;
    glm::vec3 m_fbr;

    Frustum(const glm::mat4 & viewProjectionMatrix);
    Frustum();
    bool encompass(const glm::vec3 & vertex) const;
    Frustum(const glm::vec3 &source, const glm::vec3 &front, const glm::vec3 &right, const glm::vec3 &up, float zNear, float zFar, float fov, float ratio);


    void draw(const Shader &shader) const;
};

#endif // FRUSTUM_H
