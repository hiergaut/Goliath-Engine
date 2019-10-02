#include "Frustum.h"

//Frustum::Frustum()
//{

//}
#include <QDebug>
#include <opengl/geometry/LineGeometry.h>

Frustum::Frustum(const glm::mat4& vp)
{
    // column2 + column3
    m_planes[Z_NEAR].m_a = vp[2][0] + vp[3][0];
    m_planes[Z_NEAR].m_b = vp[2][1] + vp[3][1];
    m_planes[Z_NEAR].m_c = vp[2][2] + vp[3][2];
    m_planes[Z_NEAR].m_d = vp[2][3] + vp[3][3];

    // column3 - column2
    m_planes[Z_FAR].m_a = -vp[2][0] + vp[3][0];
    m_planes[Z_FAR].m_b = -vp[2][1] + vp[3][1];
    m_planes[Z_FAR].m_c = -vp[2][2] + vp[3][2];
    m_planes[Z_FAR].m_d = -vp[2][3] + vp[3][3];

    // column1 + column3
    m_planes[BOTTOM].m_a = vp[1][0] + vp[3][0];
    m_planes[BOTTOM].m_b = vp[1][1] + vp[3][1];
    m_planes[BOTTOM].m_c = vp[1][2] + vp[3][2];
    m_planes[BOTTOM].m_d = vp[1][3] + vp[3][3];

    // column3 - column1
    m_planes[TOP].m_a = -vp[1][0] + vp[3][0];
    m_planes[TOP].m_b = -vp[1][1] + vp[3][1];
    m_planes[TOP].m_c = -vp[1][2] + vp[3][2];
    m_planes[TOP].m_d = -vp[1][3] + vp[3][3];

    // column0 + column3
    m_planes[LEFT].m_a = vp[0][0] + vp[3][0];
    m_planes[LEFT].m_b = vp[0][1] + vp[3][1];
    m_planes[LEFT].m_c = vp[0][2] + vp[3][2];
    m_planes[LEFT].m_d = vp[0][3] + vp[3][3];

    // column3 - column0
    m_planes[RIGHT].m_a = -vp[0][0] + vp[3][0];
    m_planes[RIGHT].m_b = -vp[0][1] + vp[3][1];
    m_planes[RIGHT].m_c = -vp[0][2] + vp[3][2];
    m_planes[RIGHT].m_d = -vp[0][3] + vp[3][3];

    //    m_top.normalize();
    //    m_bottom.normalize();
    //    m_right.normalize();
    //    m_left.normalize();
    //    m_planes[Z_NEAR].normalize();
    //    m_zFar.normalize();
    for (uint i = 0; i < 6; ++i) {
        m_planes[i].normalize();
    }
}

Frustum::Frustum(const glm::vec3& source, const glm::vec3& front,
                 const glm::vec3& right, const glm::vec3& up, float zNear,
                 float zFar, float fov, float ratio)
{
    float halfHeightNearPlane = zNear * tanf(glm::radians(fov) * 0.5f);
    float halfWidthNearPlane = halfHeightNearPlane * ratio;
    m_ntl = source + front * zNear + up * halfHeightNearPlane + right * -halfWidthNearPlane;
    m_ntr = source + front * zNear + up * halfHeightNearPlane + right * halfWidthNearPlane;
    m_nbl = source + front * zNear + -up * halfHeightNearPlane + right * -halfWidthNearPlane;
    m_nbr = source + front * zNear + -up * halfHeightNearPlane + right * halfWidthNearPlane;

    float halfHeightFarPlane = zFar * tanf(glm::radians(fov) * 0.5f);
    float halfWidthFarPlane = halfHeightFarPlane * ratio;
    m_ftl = source + front * zFar + up * halfHeightFarPlane + right * -halfWidthFarPlane;
    m_ftr = source + front * zFar + up * halfHeightFarPlane + right * halfWidthFarPlane;
    m_fbl = source + front * zFar + -up * halfHeightFarPlane + right * -halfWidthFarPlane;
    m_fbr = source + front * zFar + -up * halfHeightFarPlane + right * halfWidthFarPlane;

//    glm::vec3 normalPlane = glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl));
//    float d = glm::dot(normalPlane, m_ntl);

    m_planes[TOP] = Plane(glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl)), m_ntl);
    m_planes[BOTTOM] = Plane(glm::normalize(glm::cross(m_fbl - m_nbl, m_nbr - m_nbl)), m_nbl);
    m_planes[RIGHT] = Plane(glm::normalize(glm::cross(m_nbr - m_ntr, m_ftr - m_ntr)), m_ntr);
    m_planes[LEFT] = Plane(glm::normalize(glm::cross(m_ftl - m_ntl, m_nbl - m_ntl)), m_ntl);
    m_planes[Z_NEAR] = Plane(glm::normalize(glm::cross(m_nbl - m_ntl, m_ntr - m_ntl)), m_ntl);
    m_planes[Z_FAR] = Plane(glm::normalize(glm::cross(m_ftr - m_ftl, m_fbl - m_ftl)), m_ftl);
//    m_planes[Z_FAR] = Plane(glm::normalize(glm::cross(m_ntr - m_ntl, m_ftl - m_ntl)), m_ntl);



//    for (uint i = 0; i < 6; ++i) {
//        m_planes[i].normalize();
    //    }
}

void Frustum::draw(const Shader & shader) const
{
    shader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    LineGeometry::draw(m_ntl, m_ntr);
    LineGeometry::draw(m_ntr, m_nbr);
    LineGeometry::draw(m_nbr, m_nbl);
    LineGeometry::draw(m_nbl, m_ntl);

    LineGeometry::draw(m_ftl, m_ftr);
    LineGeometry::draw(m_ftr, m_fbr);
    LineGeometry::draw(m_fbr, m_fbl);
    LineGeometry::draw(m_fbl, m_ftl);

    LineGeometry::draw(m_ntl, m_ftl);
    LineGeometry::draw(m_ntr, m_ftr);
    LineGeometry::draw(m_nbr, m_fbr);
    LineGeometry::draw(m_nbl, m_fbl);

    shader.setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    if (! m_hits[TOP]) {
        LineGeometry::draw(m_ntl, 0.5f * (m_ftr + m_ftl));
    }
    if (! m_hits[BOTTOM]) {
        LineGeometry::draw(m_nbl, 0.5f * (m_fbr + m_fbl));
    }
    if (! m_hits[LEFT]) {
        LineGeometry::draw(m_nbl, 0.5f * (m_ftl + m_fbl));
    }
    if (! m_hits[RIGHT]) {
        LineGeometry::draw(m_nbr, 0.5f *(m_ftr + m_fbr));
    }
    if (! m_hits[Z_NEAR]) {
        LineGeometry::draw(m_nbl, m_ntr);
    }
    if (! m_hits[Z_FAR]) {
        LineGeometry::draw(m_fbl, m_ftr);
    }
}

bool Frustum::encompass(const glm::vec3& vertex) const
{
    bool inside = true;
    for (uint i = 0; i < 6; ++i) {
        qDebug() << "encompass " << i << "distance " << m_planes[i].distance(vertex);
        if (m_planes[i].distance(vertex) > 0.0f) {
            inside = false;
            m_hits[i] = false;
//            return false;
        }
        else {
            m_hits[i] = true;
        }
    }
    return inside;
}

