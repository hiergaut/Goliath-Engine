#include "BoundingBox.h"

#include <QDebug>
#include <limits>

#include <glm/gtc/matrix_transform.hpp>
BoundingBox::BoundingBox()
{
    clear();



}

void BoundingBox::clear()
{
    float maxFloat = std::numeric_limits<float>::max();
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

    m_cube.draw();
}
