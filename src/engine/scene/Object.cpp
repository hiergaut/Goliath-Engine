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
