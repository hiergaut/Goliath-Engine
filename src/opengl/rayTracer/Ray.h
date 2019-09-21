#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include <vector>

class Ray {
public:
    const glm::vec3 m_source;
    const glm::vec3 m_direction;

    const glm::vec3 m_invDir;
    const int m_sign[3];

    const float m_length;
    const bool m_hit = false;

    static const float MAX_RAY_LENGTH;

//    const glm::vec3 m_vertices[3];
    const std::vector<glm::vec3> m_triangles;

    //{glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)};

public:
    Ray(const glm::vec3& source, const glm::vec3& direction, float length = MAX_RAY_LENGTH,
        std::vector<glm::vec3> && triangles = std::vector<glm::vec3>());
//        const glm::vec3& v0 = glm::vec3(-1.0f, 0.0f, 0.0f),
//        const glm::vec3& v1 = glm::vec3(1.0f, 0.0f, 0.0f),
//        const glm::vec3& v2 = glm::vec3(0.0f, 1.0f, 0.0f));

    bool intersect(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t) const;
    bool intersect(const glm::vec3& v0) const;

private:
};

#endif // RAY_H
