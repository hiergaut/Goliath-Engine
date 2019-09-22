#ifndef OBJECT_H
#define OBJECT_H

#include <engine/scene/model/Model.h>
#include <glm/glm.hpp>
#include <opengl/shader.h>
//#include <gui/editor/3dview/MainWindow3dView.h>
#include <opengl/BoundingBox.h>
#include <engine/scene/model/meshModel/MeshModel.h>
//#include "model/paramModel/ParamModel.h"
//#include <engine/scene/model/paramModel/curve/BSplineCurve.h>

class Object {
public:
    mutable bool m_selected = false;
    //    mutable glm::mat4 m_transform = glm::mat4(1.0f);
    //    mutable BoundingBox m_box;
//    Model * m_model = nullptr;
//    Model & m_model;
    Model * m_model = nullptr;

public:
//    Object(Model && model) noexcept;
    Object(std::ifstream & file);
    Object(const std::string & path);
//    Object(Model &&model) noexcept;
//    Object(Object && object) noexcept = default;
    Object(Object && object) noexcept;

    Object(Model * model);
//    virtual ~Object();

    void save(std::ofstream & file) const;

    //    Object() = delete;
    virtual ~Object();

    virtual void prepareHierarchy(ulong frameTime) const;
    virtual void draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f)) const;

    virtual void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f),
        const glm::mat4& worldTransform = glm::mat4(1.0f)) const;

    virtual void updateBoundingBox() const;
    virtual void drawBoundingBox(const Shader& shader) const;

//    virtual void updateSelectedVertexPosition(const glm::mat4 & localTransform, const glm::mat4 & worldTransform);

    //    void drawOrigin(const glm::mat4 & worldTransform, const glm::mat4 & localTransform, const Shader & shader) const;
};

#endif // OBJECT_H
