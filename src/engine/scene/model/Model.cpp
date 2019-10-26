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

void Model::setTransform(glm::mat4 &&transform)
{
    m_transform = std::move(transform);
    updateBoundingBox();
}

void Model::setTransform(const glm::mat4 &transform)
{
    m_transform = transform;
    updateBoundingBox();
}

void Model::save(std::ofstream& file) const
{
    Session::save(m_type, file);
    Session::save(m_transform, file);
}

//glm::mat4 &&Model::transform()
//{
//    return m_transform;
//}

const glm::mat4 &Model::transform() const
{
    return m_transform;
}

glm::mat4 &Model::getTransform()
{
    return m_transform;
}

const BoundingBox &Model::box() const
{
    return m_box;
}
