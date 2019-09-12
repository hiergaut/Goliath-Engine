#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <opengl/BoundingBox.h>
//#include <engine/scene/model/Model.h>

class Light
{
public:
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;


    BoundingBox m_box;

public:

    enum Type {
        SUN,
        POINT,
        SPOT,
        AREA
    };

    Light();
    Light(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);

    void load(std::ifstream& file);
    void save(std::ofstream& file) const;

//    Light(const glm::vec3 position);

private:

//    Model
//    Model* m_cameraModel = nullptr;
};

#endif // LIGHT_H
