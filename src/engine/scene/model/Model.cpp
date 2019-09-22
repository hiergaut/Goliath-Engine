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
    : m_type(type)
    , m_transform(transform)
{

}

Model::Model(std::ifstream& file)
{
//    m_type = static_cast<Type>(Session::loadEnum(file));
    Session::load(m_transform, file);
}

void Model::save(std::ofstream& file) const
{
    Session::save(m_type, file);
    Session::save(m_transform, file);
}
