#ifndef DIRLIGHT_H
#define DIRLIGHT_H

#include "Light.h"
#include <opengl/shader.h>
#include <opengl/geometry/uvSphereGeometry.h>

#include <engine/scene/model/Model.h>

class DirLight : public Light
{
public:
    glm::vec3 m_direction;

    Model* m_model = nullptr;

public:
    DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 direction);
    DirLight(std::ifstream &file);
    ~DirLight();

//    void load(std::ifstream& file);
    void save(std::ofstream& file) const;
//    void draw(const Shader & shader) const;

private:
//    UvSphereGeometry m_sphere;
};

#endif // DIRLIGHT_H
