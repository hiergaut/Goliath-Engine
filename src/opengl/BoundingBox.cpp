#include "BoundingBox.h"

#include <QDebug>
#include <limits>

#include <glm/gtc/matrix_transform.hpp>

const CubeGeometry * BoundingBox::m_cube = nullptr;

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

    m_min = glm::vec3(1.0f) * maxFloat;
    m_max = -glm::vec3(1.0f) * maxFloat;

}

void BoundingBox::operator <<(const glm::vec3 &position)
{
    m_min = glm::min(m_min, position);
    m_max = glm::max(m_max, position);
}

void BoundingBox::operator <<(const BoundingBox box)
{
    m_min = glm::min(m_min, box.m_min);
    m_max = glm::max(m_max, box.m_max);


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
    return (m_min + m_max) /2.0f;
}

void BoundingBox::draw(glm::mat4 modelMatrix, const Shader & shader) const
{

    glm::vec3 diag(m_max -m_min);
    modelMatrix = glm::translate(modelMatrix, center());
    modelMatrix = glm::scale(modelMatrix, diag);

    shader.use();
    shader.setMat4("model", modelMatrix);

    Q_ASSERT(m_cube != nullptr);
    m_cube->draw();
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
