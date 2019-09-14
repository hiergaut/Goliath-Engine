#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <opengl/shader.h>
#include <engine/scene/model/Model.h>
//#include <gui/editor/3dview/MainWindow3dView.h>
#include <opengl/BoundingBox.h>

class Object {
public:
    mutable bool m_selected = false;
    mutable glm::mat4 m_transform = glm::mat4(1.0f);
    mutable BoundingBox m_box;

public:
    //    Object();

    virtual ~Object() = default;

    virtual void draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f)) const = 0;

    virtual void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f)) const = 0;

    virtual void updateBoundingBox() const = 0;
    virtual void drawBoundingBox(const Shader& shader) const = 0;

    //    void drawOrigin(const glm::mat4 & worldTransform, const glm::mat4 & localTransform, const Shader & shader) const;
};

#endif // OBJECT_H
