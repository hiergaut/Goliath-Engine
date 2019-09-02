#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    const glm::vec3 m_source;
    const glm::vec3 m_direction;

    const glm::vec3 m_invDir;
    const int m_sign[3];

public:
    Ray(const glm::vec3 & source, const glm::vec3 & direction);

private:
};

#endif // RAY_H
