#ifndef CAMERAWORLD_H
#define CAMERAWORLD_H

#include <QDebug>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
//#include "Camera.h"
#include "CameraFps.h"
#include "CameraStrategy.h"

class CameraWorld : public CameraStrategy {
public:
    glm::vec3 m_target;

public:
    //    CameraWorld();
    //    CameraWorld(std::ifstream & file);
    CameraWorld(std::ifstream& file, glm::mat4 &modelTransform, uint & id, Model & model);
    CameraWorld(const glm::vec3& position, glm::vec3 target, glm::mat4 & modelTransform, uint & id, Model & model);
//    CameraWorld(std::ifstream& file, Model & model, uint & id);
//    CameraWorld(const glm::vec3& position, glm::vec3 target, Model & model, uint & id);
    //    CameraWorld(float fov, glm::vec3 position, glm::vec3 target, Model &model);
    //    CameraWorld(CameraFps * camera);

    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    void processSliding(float dx, float dy);
    //    float getFov() const;

    void updateUpAfterReverse();

protected:
    //    void load(std::ifstream & file) override;
    void save(std::ofstream& file) override;
    //    glm::mat4 viewMatrix() const override;

    //    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    //    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    //    void drawBoundingBox(const Shader &shader) const override;

    void mousePressEvent(QMouseEvent* event) override;
    //    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

//    glm::vec3 position() const override;

    //    void setDefault() override;
//    void updateModelTransform(glm::mat4 &&modelTransform) override;

private:
    bool m_reverse = false;
    bool m_yUp = false;
    glm::vec3 m_up = glm::vec3(0.0f, 0.0f, 1.0f);
    //    uint cpt =0;

    QPoint lastPos;

public:
    void setTarget(const glm::vec3 &target) override;
    void setFront(const glm::vec3& front) override;

    glm::vec3 front() const override;
    glm::vec3 target() const override;
    glm::vec3 up() const override;
    glm::vec3 right() const override;
};

#endif // CAMERAWORLD_H
