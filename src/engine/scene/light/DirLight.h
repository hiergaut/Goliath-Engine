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
//    glm::vec3 m_direction;

//    Model* m_model = nullptr;

protected:
    virtual glm::vec3 pos(const glm::mat4& localTransform = glm::mat4(1.0f),
                          const glm::mat4& worldTransform = glm::mat4(1.0f));
    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;


public:
    DirLight(const glm::vec3 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 direction);
    DirLight(std::ifstream &file);
    DirLight(DirLight && dirLight) noexcept = default;
//    ~DirLight();
    void initGL();
    Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));

//    void load(std::ifstream& file);
    void save(std::ofstream& file) const;
//    void draw(const Shader & shader) const;
    glm::vec3 direction(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;

    glm::mat4 viewMatrix();
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
