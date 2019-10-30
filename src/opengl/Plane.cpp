#include "Plane.h"

//Plane::Plane()
//{

//}
//#include <glm/glm.hpp>

void Plane::normalize()
{
    float module = glm::sqrt(m_abcd[0] * m_abcd[0] + m_abcd[1] * m_abcd[1] + m_abcd[2] * m_abcd[2]);
    m_abcd[0] /= module;
    m_abcd[1] /= module;
    m_abcd[2] /= module;
    m_abcd[3] /= module;
}

float Plane::distance(const glm::vec3& vertex) const
{
    //    return (m_abcd[0] * vertex.x + m_abcd[1] * vertex.y + m_abcd[2] * vertex.z + m_abcd[3]) / sqrtf(m_abcd[0] * m_abcd[0] + m_abcd[1] * m_abcd[1] + m_abcd[2] * m_abcd[2]);
    return (m_abcd[0] * vertex.x + m_abcd[1] * vertex.y + m_abcd[2] * vertex.z + m_abcd[3]);
}

Plane::Plane(const glm::vec3& normal, const glm::vec3& vertex)
{
    m_abcd[0] = normal.x;
    m_abcd[1] = normal.y;
    m_abcd[2] = normal.z;

    m_abcd[3] = glm::dot(normal, vertex);

    normalize();
}

void Plane::set(float a, float b, float c, float d)
{
    m_abcd[0] = a;
    m_abcd[1] = b;
    m_abcd[2] = c;
    m_abcd[3] = d;

    normalize();
}

bool Plane::intersection(const Plane& plane, const Plane& plane2, const Plane& plane3, glm::vec3 & point)
{
    glm::vec3 normal(plane.m_abcd[0], plane.m_abcd[1], plane.m_abcd[2]);
    glm::vec3 normal2(plane2.m_abcd[0], plane2.m_abcd[1], plane2.m_abcd[2]);
    glm::vec3 normal3(plane3.m_abcd[0], plane3.m_abcd[1], plane3.m_abcd[2]);
    glm::vec3 crossProduct;
    glm::vec3 crossProduct2;
    glm::vec3 crossProduct3;
//    glm::vec3 dotProduct;
//    float DotProduct2;
//    float DotProduct3;
    glm::vec3 intersectCoordinate;
    glm::vec3 num1, num2, num3;
    crossProduct = glm::cross(normal2, normal3);
    crossProduct2 = glm::cross(normal3, normal);
    crossProduct3 = glm::cross(normal, normal2);

    //X = 0;
    //Y = 0;
    //Z = 0;
    //dotProduct = D3DXPlaneDotCoord(plane, &glm::vec3(X,Y,Z));
    //DotProduct2 = D3DXPlaneDotCoord(plane2, &glm::vec3(X,Y,Z));
    //DotProduct3 = D3DXPlaneDotCoord(plane3, &glm::vec3(X,Y,Z));

//    float XPos;
//    float YPos;
//    float ZPos;

    float denom = glm::dot(normal, crossProduct);
    if (std::abs(denom) <= 1.0e-9f) {
        return false;
    }

    num1 = -(plane.m_abcd[3] * crossProduct);
    num2 = -(plane2.m_abcd[3] * crossProduct2);
    num3 = -(plane3.m_abcd[3] * crossProduct3);

    intersectCoordinate = (num1 + num2 + num3) / denom;

    point.x = intersectCoordinate.x;
    point.y = intersectCoordinate.y;
    point.z = intersectCoordinate.z;

    //XPos = (D3DXPlaneDotCoord(plane, &glm::vec3(X,Y,Z)));
    //YPos = (D3DXPlaneDotCoord(plane2, &glm::vec3(X,Y,Z)));
    //ZPos = (D3DXPlaneDotCoord(plane3, &glm::vec3(X,Y,Z)));
    //X = XPos;
    //Y = YPos;
    //Z = ZPos;
    //X *= -1;
    //Y *= -1;
    //Z *= -1.0f;

    return true;
}

glm::vec3 Plane::normal() const
{
    return glm::vec3(m_abcd[0], m_abcd[1], m_abcd[2]);
}

//float &Plane::operator()(uint i)
//{

//}
