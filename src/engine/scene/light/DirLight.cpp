#include "DirLight.h"



DirLight::DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse,
                   const glm::vec3 specular, const glm::vec3 direction)
    : Light(position, ambient, diffuse, specular)
    , m_direction(direction)
//    , m_sphere(5000.0f)
{
//    m_sphere = new UvSphereGeometry(100, 100);
    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

//    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    m_model->m_transform = modelMatrix;
//    model = glm::rotate()


}

DirLight::DirLight(std::ifstream &file)
{
    Light::load(file);

    Session::load(m_direction, file);

    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

//    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, m_position);
    m_model->m_transform = modelMatrix;
//    model = glm::rotate()
}

DirLight::~DirLight()
{
//    delete m_sphere;

}

//void DirLight::load(std::ifstream &file)
//{
//    Session::load(m_direction, file);

//}

void DirLight::save(std::ofstream &file) const
{
    Light::save(file);

    Session::save(m_direction, file);

}

//void DirLight::draw(const Shader &shader) const
//{

////    shader.setMat4("model", glm::mat4(1.0f));
////    m_sphere.draw(shader, glm::vec3(0.0f), 100.0f);
//    UvSphereGeometry::draw(shader, m_position, 100.0f);

//}
