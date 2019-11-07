#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <opengl/BoundingBox.h>
//#include <engine/scene/model/Model.h>
//#include <engine/scene/Object.h>
//#include <opengl/version.h>

class Light {
public:
    //    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    //    BoundingBox m_box;
    mutable bool m_shadowComputed;

    mutable float m_coeffBlink = 1.0f;
    bool m_blink = false;

public:
    enum Type {
        SUN,
        POINT,
        SPOT,
        AREA
    } m_type;

    //    Light() = default;
    Light(const glm::vec3 ambient = 0.5f * glm::vec3(1.0f), const glm::vec3 diffuse = glm::vec3(1.0f), const glm::vec3 specular = glm::vec3(1.0f));

    void load(std::ifstream& file);
    void save(std::ofstream& file) const;

    virtual bool selected() const = 0;
//    virtual Shader & depthShader(glm::)
    virtual Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const = 0;

    void setSelected(bool selected);

    //    void updateShadowMap();
//    Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f));
//    void showDepth();
//    void renderQuad();

//    uint quadVAO = 0;
//    uint quadVBO;

protected:
//    virtual glm::vec3 pos(const glm::mat4& localTransform = glm::mat4(1.0f),
//                          const glm::mat4& worldTransform = glm::mat4(1.0f)) = 0;
//    virtual glm::mat4 viewMatrix() = 0;

    //    Light(const glm::vec3 position);

private:


    //    Model
    //    Model* m_cameraModel = nullptr;
};

#endif // LIGHT_H
