#include "Ray.h"

#include <iostream>

Ray::Ray(const glm::vec3& source, const glm::vec3& direction)
    : m_source(source)
    , m_direction(direction)
    , m_invDir(1.0f / direction)
    , m_sign { (m_invDir.x < 0), (m_invDir.y < 0), (m_invDir.z < 0) }
{
    //    m_sign[0] = m_invDir < 0;
}

//bool Ray::intersect(
//    const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
//    float& t) const
//{
//    // compute plane's normal
//    glm::vec3 v0v1 = v1 - v0;
//    glm::vec3 v0v2 = v2 - v0;
//    // no need to normalize
//    glm::vec3 N = glm::cross(v0v1, v0v2); // N
////    float area2 = N.length();

//    // Step 1: finding P

//    // check if ray and plane are parallel ?
//    float NdotRayDirection = glm::dot(N, m_direction);
//    if (std::fabs(NdotRayDirection) < 0.001f) { // almost 0
//        std::cout << "parallel" << std::endl;
//        return false; // they are parallel so they don't intersect !
//    }

//    // compute d parameter using equation 2
//    float d = glm::dot(N, v0);

//    // compute t (equation 3)
//    t = (glm::dot(N, m_source) + d) / NdotRayDirection;
//    // check if the triangle is in behind the ray
//    if (t < 0) {
////        std::cout << "behind" << std::endl;
//        return false; // the triangle is behind
//    }

//    // compute the intersection point using equation 1
//    glm::vec3 P = m_source + t * m_direction;

//    // Step 2: inside-outside test
//    glm::vec3 C; // vector perpendicular to triangle's plane

//    // edge 0
//    glm::vec3 edge0 = v1 - v0;
//    glm::vec3 vp0 = P - v0;
//    C = glm::cross(edge0, vp0);
//    if (glm::dot(N, C) < 0) {
////        std::cout << "right v01" << std::endl;
//        return false; // P is on the right side
//    }

//    // edge 1
//    glm::vec3 edge1 = v2 - v1;
//    glm::vec3 vp1 = P - v1;
//    C = glm::cross(edge1, vp1);
//    if (glm::dot(N, C) < 0) {
////        std::cout << "right v12" << std::endl;
//        return false; // P is on the right side
//    }

//    // edge 2
//    glm::vec3 edge2 = v0 - v2;
//    glm::vec3 vp2 = P - v2;
//    C = glm::cross(edge2, vp2);
//    if (glm::dot(N, C) < 0) {
////        std::cout << "right v02" << std::endl;
//        return false; // P is on the right side;
//    }

//    return true; // this ray hits the triangle
//}


bool Ray::intersect(
    const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
    float& t) const
{
    const float EPSILON = 0.0000001f;
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = v1 - v0;
    edge2 = v2 - v0;
    h = glm::cross( m_direction, edge2);
    a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0f/a;
    s = m_source - v0;
    u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return false;
    q = glm::cross(s, edge1);
    v = f * glm::dot(m_direction, q);
    if (v < 0.0f || u + v > 1.0f)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    t = f * glm::dot(edge2, q);
    if (t > EPSILON) // ray intersection
    {
//        outIntersectionPoint = m_source + m_direction * t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}
