#include "Object.h"

//Object::Object()
//{

//}

//Object::Object(Model& model)
//    : m_model(model)
//{
//}

//Object::Object(Model &&model) noexcept
//    : m_model(model)
//{

//}
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
#include <engine/scene/model/paramModel/surface/BSplineSurface.h>

Object::Object(std::ifstream& file)
//    : m_model(file)
//    : m_model(file)
//    : m_model(new Model(file))
{
    Model::Type type = static_cast<Model::Type>(Session::loadEnum(file));
    //    qDebug() << "type" << type;
    switch (type) {
    case Model::MESH:
        m_model = new MeshModel(file);
        break;

    case Model::PARAM_CURVE:
        //        m_model = new ParamModel(file);
        m_model = new BSplineCurve(file);
        //        Q_ASSERT(false);
        break;

    case Model::PARAM_SURFACE:
        m_model = new BSplineSurface(file);
        break;

    default:
        Q_ASSERT(false);
        break;
    }

//    updateBoundingBox();
}

Object::Object(const std::string& path)
    //    : m_model(path)
    //    : m_mod
    : m_model(new MeshModel(path))
{
//    updateBoundingBox();
}

Object::Object(Object&& object) noexcept
    : m_selected(std::move(object.m_selected))
    //    , *m_model(std::move(*object.m_model))
    , m_model(object.m_model)
{
    object.m_model = nullptr;

//    std::cout << "\033[33m";
//    std::cout << "[Object] " << &object << "  '" << m_model->name() << "' moved to " << this << std::endl;
//    std::cout << "\033[0m";
}

Object::Object(Model* model)
    : m_model(model)
{
}

void Object::save(std::ofstream& file) const
{
    //    Session::saveEnum(m_model->m_type, file);
    m_model->save(file);
}

Object::~Object()
{
//    std::cout << "\033[35m";
//    std::cout << "[Object] '" << this << "' deleted " << std::endl;
//    std::cout << "\033[0m";
    //    Q_ASSERT(m_model != nullptr);
    if (m_model != nullptr) {
        delete m_model;
    }
    //    std::cout << "\033[35m";
    //    std::cout << "[Object] '" << m_model << "' deleted " << this << std::endl;
    //    std::cout << "\033[0m";
}

//Object::~Object()
//{
//    std::cout << "\033[35m";
//    std::cout << "[Object] '" << "' deleted " << this << std::endl;
//    std::cout << "\033[0m";

//}

//Object::Object(const std::string &path)
////    : m_model(path)
//{

//}

//Object::Object(Model &&model)
//    : m_model(model)
//{

//}

//Object::Object(const std::string &path)
////    : m_model(path)
//{

//}

void Object::prepareHierarchy(ulong frameTime) const
{
    m_model->prepareHierarchy(frameTime);
}

void Object::draw(const Shader& shader, bool dotCloud, const Frustum &frustum, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model->draw(shader, dotCloud, frustum, localTransform, worldTransform);
}

void Object::draw(const Shader& shader, const glm::mat4& localTransform, const glm::mat4& worldTransform) const
{
    m_model->draw(shader, localTransform, worldTransform);
}

void Object::drawBoundingBox(const Shader &shader) const
{
    m_model->drawBoundingBox(shader);
}

//void Object::updateBoundingBox()
//{
//    m_model->updateBoundingBox();
//}

//void Object::drawBoundingBox(const Shader& shader) const
//{
//}

void Object::buildItemModel(QStandardItem *parent) const
{
    m_model->buildItemModel(parent);
}

void Object::updateSelectedVertexPosition(const glm::mat4 &localTransform, const glm::mat4 &worldTransform)
{
    m_model->updateSelectedVertexPosition(localTransform, worldTransform);
}

bool Object::selected() const
{
    return m_selected;
}

void Object::setSelected(bool selected)
{
    m_selected = selected;
}

const std::string &Object::name() const
{
    return m_model->name();
}

Model::Type Object::modelType() const
{
    return m_model->m_type;
}

const glm::mat4 &Object::transform() const
{
    return m_model->transform();
}

glm::mat4 &Object::getTransform()
{
    return m_model->getTransform();
}

void Object::setTransform(const glm::mat4 & transform)
{
    m_model->setTransform(transform);
}

const Model *Object::model() const
{
    return m_model;
}

Model *Object::getModel()
{
    return m_model;
}

const BoundingBox &Object::box() const
{
    return m_model->box();
}
