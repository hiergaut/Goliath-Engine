#include "BoundingBox.h"

#include <QDebug>
#include <limits>

#include <glm/gtc/matrix_transform.hpp>

const CubeGeometry* BoundingBox::m_cube = nullptr;

BoundingBox::BoundingBox()
{
    clear();

    m_cube = new CubeGeometry;
}

void BoundingBox::clear()
{
    float maxFloat = std::numeric_limits<float>::max();
    //    float maxFloat = 0.0f;
    //    float minFloat = std::numeric_limits<float>::min();
    //    float maxFloat = 10.0f;

    m_bounds[0] = glm::vec3(1.0f) * maxFloat;
    m_bounds[1] = -glm::vec3(1.0f) * maxFloat;
}

void BoundingBox::operator<<(const glm::vec3& position)
{
    m_bounds[0] = glm::min(m_bounds[0], position);
    m_bounds[1] = glm::max(m_bounds[1], position);
}

void BoundingBox::operator<<(const BoundingBox box)
{
    m_bounds[0] = glm::min(m_bounds[0], box.m_bounds[0]);
    m_bounds[1] = glm::max(m_bounds[1], box.m_bounds[1]);
}

//BoundingBox BoundingBox::operator *(glm::mat4 mat) const
//{
////    glm::vec3 m;
//    BoundingBox ret;

////    glm::vec3 diag = m_max - m_min;
//    for (glm::vec3 corner : corners(mat)) {
////        glm::vec3 pos = glm::vec4(corner, 1.0) * mat;
//        glm::vec3 pos = mat * glm::vec4(corner, 0.0);

//        ret << pos;

//    }

//    return ret;

//}

glm::vec3 BoundingBox::center() const
{
    //    return glm::vec3(0.0f);
    //    qDebug() << m_min.x << m_min.y << m_min.z;
    return (m_bounds[0] + m_bounds[1]) / 2.0f;
}

float BoundingBox::radius() const
{
    return glm::length(m_bounds[0] -m_bounds[1]) / 2.0f;

}

void BoundingBox::draw(const Shader& shader) const
{

    glm::mat4 modelMatrix(1.0f);
    glm::vec3 diag(m_bounds[1] - m_bounds[0]);
    modelMatrix = glm::translate(modelMatrix, center());
    modelMatrix = glm::scale(modelMatrix, diag);

    shader.use();
    shader.setMat4("model", modelMatrix);

    Q_ASSERT(m_cube != nullptr);
    m_cube->draw();
}

//bool BoundingBox::intersect(const Ray& ray) const
//{
//    float tmin = (m_min.x - ray.m_source.x) / ray.m_direction.x;
//    float tmax = (m_max.x - ray.m_source.x) / ray.m_direction.x;

//    if (tmin > tmax)
//        std::swap(tmin, tmax);

//    float tymin = (m_min.y - ray.m_source.y) / ray.m_direction.y;
//    float tymax = (m_max.y - ray.m_source.y) / ray.m_direction.y;

//    if (tymin > tymax)
//        std::swap(tymin, tymax);

//    if ((tmin > tymax) || (tymin > tmax))
//        return false;

//    if (tymin > tmin)
//        tmin = tymin;

//    if (tymax < tmax)
//        tmax = tymax;

//    float tzmin = (m_min.z - ray.m_source.z) / ray.m_direction.z;
//    float tzmax = (m_max.z - ray.m_source.z) / ray.m_direction.z;

//    if (tzmin > tzmax)
//        std::swap(tzmin, tzmax);

//    if ((tmin > tzmax) || (tzmin > tmax))
//        return false;

//    if (tzmin > tmin)
//        tmin = tzmin;

//    if (tzmax < tmax)
//        tmax = tzmax;

//    return true;
//}

bool BoundingBox::intersect(const Ray &r) const
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (m_bounds[r.m_sign[0]].x - r.m_source.x) * r.m_invDir.x;
    tmax = (m_bounds[1-r.m_sign[0]].x - r.m_source.x) * r.m_invDir.x;
    tymin = (m_bounds[r.m_sign[1]].y - r.m_source.y) * r.m_invDir.y;
    tymax = (m_bounds[1-r.m_sign[1]].y - r.m_source.y) * r.m_invDir.y;

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (m_bounds[r.m_sign[2]].z - r.m_source.z) * r.m_invDir.z;
    tzmax = (m_bounds[1-r.m_sign[2]].z - r.m_source.z) * r.m_invDir.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}

//std::vector<glm::vec3> BoundingBox::corners(glm::mat4 basis) const
//{
//    std::vector<glm::vec3> ret;
//    glm::vec3 diag(m_max - m_min);

//    ret.emplace_back(m_min);
//    ret.emplace_back(m_min + diag.x);
//    ret.emplace_back(m_min + diag.y);
//    ret.emplace_back(m_min + diag.z);

//    ret.emplace_back(m_max);
//    ret.emplace_back(m_max - diag.x);
//    ret.emplace_back(m_max - diag.y);
//    ret.emplace_back(m_max - diag.z);

//    for (glm::vec3 & v : ret) {
//        v = basis * glm::vec4(v, 0.0f);
//    }

//    return ret;
//}
