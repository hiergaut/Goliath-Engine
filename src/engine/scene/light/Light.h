#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <opengl/BoundingBox.h>
//#include <engine/scene/model/Model.h>
//#include <engine/scene/Object.h>

class Light
{
public:
//    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;


//    BoundingBox m_box;

public:

    enum Type {
        SUN,
        POINT,
        SPOT,
        AREA
    };

//    Light() = default;
    Light(const glm::vec3 ambient = 0.5f * glm::vec3(1.0f), const glm::vec3 diffuse = glm::vec3(1.0f), const glm::vec3 specular = glm::vec3(1.0f));

    void load(std::ifstream& file);
    void save(std::ofstream& file) const;

//    Light(const glm::vec3 position);

private:

//    Model
//    Model* m_cameraModel = nullptr;
};

#endif // LIGHT_H
