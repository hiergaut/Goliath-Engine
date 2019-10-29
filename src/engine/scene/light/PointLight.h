#ifndef POINTLIGHT_H
#define POINTLIGHT_H


//class PointLight
//{
//public:
//    PointLight();
//};


#include "Light.h"
#include <opengl/shader.h>
#include <opengl/geometry/uvSphereGeometry.h>

#include <engine/scene/model/Model.h>
#include <engine/scene/Object.h>

class PointLight : public Light, public Object
{
public:
//    glm::vec3 m_direction;

//    Model* m_model = nullptr;

protected:
    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;


public:
    PointLight(const glm::vec3 position, const glm::vec3 ambient = glm::vec3(0.05f), const glm::vec3 diffuse = glm::vec3(0.8f), const glm::vec3 specular = glm::vec3(1.0f));
    PointLight(std::ifstream &file);
    PointLight(PointLight && dirLight) noexcept = default;
//    ~PointLight();
    void initGL();
    void initViewMatrix();

    virtual glm::vec3 position(const glm::mat4& localTransform = glm::mat4(1.0f),
                          const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
    Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;
//    glm::mat4 lightSpaceMatrix(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;

//    void load(std::ifstream& file);
    void save(std::ofstream& file) const;
//    void draw(const Shader & shader) const;
//    glm::vec3 direction(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;

//    glm::mat4 viewMatrix() const;
    uint depthMap() const;
private:
    QOpenGLFunctionsCore* m_fun;
    uint m_depthFbo;
    uint m_depthMap;
    //    float m_nearPlane;
    //    float m_farPlane;

    Shader* m_simpleDepthShader; //{"shadow/shadow_mapping_depth.vsh", "shadow/shadow_mapping_depth.fsh"};
//    Shader * m_cube

    glm::mat4 m_viewMatrix[6];

    glm::mat4 m_shadowProj;
    float m_near_plane = 20.0f;
    float m_far_plane = 5000.0f;

//    float m_constant;
//    float m_linear;
//    float m_quadratic;

//    Shader* m_debugDepthQuad; //{"shadow/debug_quad.vsh", "shadow/debug_quad.fsh"};
//    UvSphereGeometry m_sphere;
//    Shader * m_skyBoxShader;
};

#endif // POINTLIGHT_H
