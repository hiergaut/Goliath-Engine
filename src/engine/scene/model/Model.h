#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <opengl/BoundingBox.h>
#include <opengl/shader.h>
#include <QStandardItemModel>

class Model {
public:

    enum Type {
        MESH,
        PARAM_CURVE,
        PARAM_SURFACE,
    } m_type;

    mutable glm::mat4 m_transform = glm::mat4(1.0f);
    mutable BoundingBox m_box;

public:
    //    Model(std::ifstream & file);
    //    Model(const std::string & path);
//    Model() = default;
    Model(const glm::mat4 & transform, Type type);
    Model(std::ifstream & file);
    virtual ~Model() = default;

    virtual void save(std::ofstream & file) const;

    virtual void prepareHierarchy(ulong frameTime) const = 0;
    virtual void draw(const Shader& shader, bool dotCloud,
        const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f))
        const = 0;

    virtual void draw(const Shader& shader,
        const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f))
        const = 0;

    virtual void updateBoundingBox() const = 0;
    virtual void drawBoundingBox(const Shader& shader) const = 0;

    virtual void updateSelectedVertexPosition(const glm::mat4 & localTransform, const glm::mat4 & worldTransform) = 0;

    virtual std::string name() const = 0;
    virtual void buildItemModel(QStandardItem* parent) const = 0;
};

#endif // MODEL_H
