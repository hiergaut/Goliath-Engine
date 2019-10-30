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

class Camera : public Object {
public:
    CameraStrategy* m_cameraStrategy = nullptr;
    float m_fov;
    uint m_id;

public:
    Camera(float fov, uint id);
    Camera(std::ifstream& file, uint id);

    void save(std::ofstream& file);
    //    Camera(Camera * camera);
    //        virtual ~Camera() {}
    //    void setDefault();
    glm::mat4 viewMatrix();

    //    void switchStrategy();
        void updateBoundingBox() const;

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
    const glm::vec3 position() const;


//private:
//    Frustum m_frustum;
};

#endif // CAMERA_H
