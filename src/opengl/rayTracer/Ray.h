#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    const glm::vec3 m_source;
    const glm::vec3 m_direction;

    const glm::vec3 m_invDir;
    const int m_sign[3];

    mutable float m_length;
    mutable bool m_hit = false;

    static const float MAX_RAY_LENGTH;

public:
    Ray(const glm::vec3 & source, const glm::vec3 & direction, float length = MAX_RAY_LENGTH);
    bool intersect(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, float &t) const;

private:
};

#endif // RAY_H
