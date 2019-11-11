#ifndef DIRLIGHT_H
#define DIRLIGHT_H

#include "Light.h"
#include <opengl/shader.h>
#include <opengl/geometry/uvSphereGeometry.h>

#include <engine/scene/model/Model.h>
#include <engine/scene/Object.h>

class DirLight : public Light, public Object
{
public:
    mutable float m_coeffSunrise = 1.0f;

//    glm::vec3 m_direction;

//    Model* m_model = nullptr;
    Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
    bool selected() const override;

protected:
    virtual glm::vec3 pos(const glm::mat4& localTransform = glm::mat4(1.0f),
                          const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
    void draw(const Shader &shader, bool dotCloud, const Frustum & frustum, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;

    void prepareHierarchy(ulong frameTime) const override;

//    void setSelected(bool selected) override;

public:
    DirLight(const glm::vec3 position, const glm::vec3 direction, const glm::vec3 ambient = glm::vec3(0.4f), const glm::vec3 diffuse = glm::vec3(1.0f), const glm::vec3 specular = glm::vec3(1.0f));
    DirLight(std::ifstream &file);
    DirLight(DirLight && dirLight) noexcept = default;
//    ~DirLight();
    void initGL();
    glm::mat4 lightSpaceMatrix(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;

//    void load(std::ifstream& file);
    void save(std::ofstream& file) const;
//    void draw(const Shader & shader) const;
    glm::vec3 direction(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;

    glm::mat4 viewMatrix() const;
    uint depthMap() const;
private:
    QOpenGLFunctionsCore* m_fun;
    uint m_depthFbo;
    uint m_depthMap;
    //    float m_nearPlane;
    //    float m_farPlane;

    Shader* m_simpleDepthShader; //{"shadow/shadow_mapping_depth.vsh", "shadow/shadow_mapping_depth.fsh"};
//    Shader* m_debugDepthQuad; //{"shadow/debug_quad.vsh", "shadow/debug_quad.fsh"};
//    UvSphereGeometry m_sphere;
};

#endif // DIRLIGHT_H
