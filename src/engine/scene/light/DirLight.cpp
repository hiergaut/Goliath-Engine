#include "DirLight.h"



DirLight::DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse,
                   const glm::vec3 specular, const glm::vec3 direction)
    : Light(ambient, diffuse, specular)
    , Object(g_resourcesPath + "models/sun/sun.obj")
//    , m_direction(direction)
//    , m_sphere(5000.0f)
{
//    m_sphere = new UvSphereGeometry(100, 100);
//    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

//    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    m_model.m_transform = modelMatrix;

//    model = glm::rotate()


}

DirLight::DirLight(std::ifstream &file)
    : Object(g_resourcesPath + "models/sun/sun.obj")
{
    Light::load(file);
    Session::load(m_model.m_transform, file);


//    Session::load(m_direction, file);

//    m_model = new Model(g_resourcesPath + "models/sun/sun.obj");

//    m_sun->m_transform = glm::inverse(glm::lookAt(m_position, m_position + direction, ))
//    glm::mat4 modelMatrix(1.0f);
//    modelMatrix = glm::translate(modelMatrix, m_position);
//    m_model->m_transform = modelMatrix;
//    model = glm::rotate()
}

//DirLight::~DirLight()
//{
////    delete m_sphere;

//}

//void DirLight::load(std::ifstream &file)
//{
//    Session::load(m_direction, file);

//}

void DirLight::save(std::ofstream &file) const
{
    Light::save(file);
    Session::save(m_model.m_transform, file);


//    Session::save(m_direction, file);

}

glm::vec3 DirLight::direction() const
{
//    glm::vec3 dir = glm::normalize(m_model.m_transform[0] + m_model.m_transform[1] + m_model.m_transform[2]);
    glm::vec3 sunUp = glm::vec3(m_model.m_transform * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    return sunUp;
//    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);

//    glm::vec3 right = glm::normalize(glm::cross(sunUp, up));

//    return dir;

}

//void DirLight::draw(const Shader &shader) const
//{

////    shader.setMat4("model", glm::mat4(1.0f));
////    m_sphere.draw(shader, glm::vec3(0.0f), 100.0f);
//    UvSphereGeometry::draw(shader, m_position, 100.0f);

//}
