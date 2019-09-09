#include "DirLight.h"



DirLight::DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 direction)
    : Light(position, ambient, diffuse, specular)
    , m_direction(direction)
//    , m_sphere(5000.0f)
{
//    m_sphere = new UvSphereGeometry(100, 100);

}

DirLight::~DirLight()
{
//    delete m_sphere;

}

void DirLight::draw(const Shader &shader) const
{

//    shader.setMat4("model", glm::mat4(1.0f));
//    m_sphere.draw(shader, glm::vec3(0.0f), 100.0f);
    UvSphereGeometry::draw(shader, glm::vec3(0.0f), 100.0f);

}
