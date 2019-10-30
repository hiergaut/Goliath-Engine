#ifndef CAMERA_H
#define CAMERA_H

#include <QKeyEvent>
#include <fstream>
#include <glm/glm.hpp>

//#include <session/Session.h>
#include "CameraStrategy.h"
#include <engine/scene/Object.h>
#include <engine/scene/model/Model.h>

#include <opengl/Frustum.h>
#include <engine/scene/camera/CameraStrategy.h>
//#include <engine/scene/light/SpotLight.h>

//class Camera : public Object {
class Camera : public Object {
public:
    CameraStrategy* m_cameraStrategy = nullptr;
    float m_fov;
    uint m_id;

    bool m_torchEnable = false;

public:
    Camera(float fov, uint id);
    Camera(std::ifstream& file, uint id);

    void save(std::ofstream& file);
    //    Camera(Camera * camera);
    //        virtual ~Camera() {}
    //    void setDefault();
    glm::mat4 viewMatrix() const;

    glm::vec3 direction(const glm::mat4 & localTransform = glm::mat4(1.0f)) const;
    virtual glm::vec3 position(const glm::mat4& localTransform = glm::mat4(1.0f),
                          const glm::mat4& worldTransform = glm::mat4(1.0f)) const;

    //    void switchStrategy();
        void updateBoundingBox() const;
    void initGL();
    Shader& depthShader(const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const;

protected:
    void prepareHierarchy(ulong frameTime) const override;
    void draw(const Shader& shader, bool dotCloud, const Frustum & frustum, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;

    void drawBoundingBox(const Shader& shader) const override;


    //    static float accuracyRotate;
    //    static float accuracyMove;
    //    static float accuracySlide;
private:

public:
    void setDefault();
    void setTarget(const glm::vec3& target);
    void setFront(const glm::vec3& front);

    glm::vec3 front() const;
    glm::vec3 right() const;
    glm::vec3 up() const;

    glm::vec3 target() const;

    //    float fov() const;
//    const glm::vec3 position() const;


    uint depthMap() const;
    glm::mat4 lightSpaceMatrix(const glm::mat4 &localTransform = glm::mat4(1.0f)) const;
private:
    QOpenGLFunctionsCore* m_fun;
    uint m_depthFbo;
    uint m_depthMap;
    //    float m_nearPlane;
    //    float m_farPlane;

    Shader* m_simpleDepthShader; //{"shadow/shadow_mapping_depth.vsh", "shadow/shadow_mapping_depth.fsh"};

//private:
//    Frustum m_frustum;
};

#endif // CAMERA_H
