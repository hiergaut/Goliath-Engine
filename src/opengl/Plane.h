#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

class Plane
{
public:
    void normalize();
    float distance(const glm::vec3 & vertex) const;
    Plane(const glm::vec3 & normal, const glm::vec3 & vertex);
    Plane() {}

    void set(float a, float b, float c, float d);

//    float m_a;
//    float m_b;
//    float m_c;
//    float m_d;
    float m_abcd[4];
    //    Plane();
    static bool intersection(const Plane &plane, const Plane &plane2, const Plane &plane3, glm::vec3 &point);

    glm::vec3 normal() const;
//    float & operator()(uint i);
};

#endif // PLANE_H
