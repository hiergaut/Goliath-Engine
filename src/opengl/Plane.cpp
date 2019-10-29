#include "Plane.h"

//Plane::Plane()
//{

//}
//#include <glm/glm.hpp>


void Plane::normalize()
{
    float module = glm::sqrt(m_a * m_a + m_b * m_b + m_c * m_c);
    m_a /= module;
    m_b /= module;
    m_c /= module;
    m_d /= module;
}

float Plane::distance(const glm::vec3& vertex) const
{
//    return (m_a * vertex.x + m_b * vertex.y + m_c * vertex.z + m_d) / sqrtf(m_a * m_a + m_b * m_b + m_c * m_c);
    return (m_a * vertex.x + m_b * vertex.y + m_c * vertex.z + m_d);
}

Plane::Plane(const glm::vec3 &normal, const glm::vec3 &vertex)
{
    m_a = normal.x;
    m_b = normal.y;
    m_c = normal.z;

    m_d = glm::dot(normal, vertex);

    normalize();
}

void Plane::set(float a, float b, float c, float d)
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
}
