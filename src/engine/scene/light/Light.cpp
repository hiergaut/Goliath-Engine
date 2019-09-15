#include "Light.h"

#include <session/Session.h>
//Light::Light()
//{

//}

//Light::Light()
//{

//}

Light::Light(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular)
//    : m_position(position)
    : m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular)
{

    //    m_cameraModel = new Model(g_resourcesPath + "models/camera/camera.obj");
}

void Light::load(std::ifstream &file)
{
//    Session::load(m_position, file);
    Session::load(m_ambient, file);
    Session::load(m_diffuse, file);
    Session::load(m_specular, file);


}

void Light::save(std::ofstream &file) const
{
//    Session::save(m_position, file);
    Session::save(m_ambient, file);
    Session::save(m_diffuse, file);
    Session::save(m_specular, file);


}

//Light::Light(const glm::vec3 position)
//    : m_position(position)
//{


//}
