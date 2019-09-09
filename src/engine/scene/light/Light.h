#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

public:

    enum Type {
        SUN,
        POINT,
        SPOT,
        AREA
    };

    Light(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
//    Light(const glm::vec3 position);

private:
};

#endif // LIGHT_H
