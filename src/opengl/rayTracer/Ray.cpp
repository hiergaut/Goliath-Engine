#include "Ray.h"

Ray::Ray(const glm::vec3 & source, const glm::vec3 & direction)
    : m_source(source)
    , m_direction(direction)
    , m_invDir(1.0f /direction)
    , m_sign{(m_invDir.x < 0), (m_invDir.y < 0), (m_invDir.z < 0)}
{
//    m_sign[0] = m_invDir < 0;
}
