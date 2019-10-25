#ifndef CAMERA_H
#define CAMERA_H

#include <QKeyEvent>
#include <fstream>
#include <glm/glm.hpp>

//#include <session/Session.h>
#include <engine/scene/Object.h>
#include <engine/scene/model/Model.h>
#include "CameraStrategy.h"

class Camera : public Object {
public:
    CameraStrategy * m_cameraStrategy = nullptr;
    float m_fov;


public:
    Camera(float fov);
    Camera(std::ifstream& file);

    void save(std::ofstream& file);
    //    Camera(Camera * camera);
    //        virtual ~Camera() {}
//    void setDefault();
    glm::mat4 viewMatrix();

//    void switchStrategy();

protected:
    void prepareHierarchy(ulong frameTime) const override;
    void draw(const Shader& shader, bool dotCloud, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader& shader, const glm::mat4& localTransform = glm::mat4(1.0f), const glm::mat4& worldTransform = glm::mat4(1.0f)) const override;

//    void updateBoundingBox() const;
    void drawBoundingBox(const Shader& shader) const override;

    //    static float accuracyRotate;
    //    static float accuracyMove;
    //    static float accuracySlide;
private:

public:
    void setDefault();
    void setTarget(const glm::vec3 & target);
    void setFront(const glm::vec3& front);

    glm::vec3 front() const;
    glm::vec3 right() const;
    glm::vec3 up() const;

    glm::vec3 target() const;

//    float fov() const;
    const glm::vec3 position() const;

    //private:
};

#endif // CAMERA_H
