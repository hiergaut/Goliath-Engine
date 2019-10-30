#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <opengl/BoundingBox.h>
#include <opengl/shader.h>
#include <QStandardItemModel>
#include <opengl/Frustum.h>

class Model {
public:

    enum Type {
        MESH,
        PARAM_CURVE,
        PARAM_SURFACE,
    } m_type;


public:
    //    Model(std::ifstream & file);
    //    Model(const std::string & path);
//    Model() = default;
    Model(const glm::mat4 & transform, Type type);
    Model(std::ifstream & file);
    virtual ~Model() = default;

    void setTransform(glm::mat4 && transform);
    void setTransform(const glm::mat4 & transform);

    virtual void save(std::ofstream & file) const;

    virtual void prepareHierarchy(ulong frameTime) const = 0;
    virtual void draw(const Shader& shader, bool dotCloud, const Frustum & frustum,
        const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f))
        const = 0;

    virtual void draw(const Shader& shader,
        const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f))
        const = 0;

    virtual void updateBoundingBox() = 0;

    virtual void drawBoundingBox(const Shader& shader) const = 0;

    virtual void updateSelectedVertexPosition(const glm::mat4 & localTransform, const glm::mat4 & worldTransform) = 0;

    virtual const std::string & name() const = 0;
    virtual void buildItemModel(QStandardItem* parent) const = 0;

//    glm::mat4 && transform();
    const glm::mat4 & transform() const;
    glm::mat4 & getTransform();

    const BoundingBox &box() const;

private:
//    virtual void updateBoundingBox() { Q_ASSERT(false); }

//private:
protected:
    BoundingBox m_box;
//    bool m_noBox;

    glm::mat4 m_transform = glm::mat4(1.0f);
};

#endif // MODEL_H
