#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:

    enum Type {
        SUN,
        POINT,
        SPOT,
        AREA
    };

    Light();

private:
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};

#endif // LIGHT_H
