#include "Object.h"

//Object::Object()
//{

//}

//Object::Object(Model& model)
//    : m_model(model)
//{
//}

Object::Object(Model &&model) noexcept
    : m_model(std::move(model))
{

}

//Object::~Object()
//{
//    std::cout << "\033[35m";
//    std::cout << "[Object] '" << "' deleted " << this << std::endl;
//    std::cout << "\033[0m";


//}

Object::Object(const std::string &path)
    : m_model(path)
{

}

void Object::draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model.draw(shader, dotCloud, localTransform, worldTransform);
}

void Object::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model.draw(shader, localTransform, worldTransform);
}

void Object::updateBoundingBox() const
{
    m_model.updateBoundingBox();
}

void Object::drawBoundingBox(const Shader& shader) const
{
    m_model.drawBoundingBox(shader);
}
