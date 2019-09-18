#include "Model.h"
#include <session/Session.h>

//Model::Model()
//{

//}

//Model::Model(std::ifstream &file)
//{

//}

//Model::Model(const std::string &path)
//{

//}

Model::Model(const glm::mat4 &transform, Model::Type type)
    : m_transform(transform)
    , m_type(type)
{

}

Model::Model(std::ifstream& file)
{
    Session::load(m_transform, file);
    m_type = static_cast<Type>(Session::loadEnum(file));
}

void Model::save(std::ofstream& file)
{
    Session::save(m_transform, file);
    Session::save(m_type, file);
}
