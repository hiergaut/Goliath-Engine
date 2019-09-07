#ifndef CAMERAWORLD_H
#define CAMERAWORLD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <QDebug>
#include <iostream>
#include "Camera.h"
#include "CameraFps.h"


class CameraWorld : public Camera {
public:
    glm::vec3 m_target;

public:
    CameraWorld();
    CameraWorld(float fov, glm::vec3 position, glm::vec3 target);
//    CameraWorld(CameraFps * camera);

    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    void processSliding(float dx, float dy);
//    float getFov() const;

    void updateUpAfterReverse();


protected:
    void load(std::ifstream & file) override;
    void save(std::ofstream & file) override;
    glm::mat4 viewMatrix() const override;


    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:

    bool m_reverse = false;
    bool m_yUp = false;
    glm::vec3 m_up = glm::vec3(0.0f, 0.0f, 1.0f);
//    uint cpt =0;

    QPoint lastPos;

public:
    glm::vec3 target() const;
    glm::vec3 up() const override;
    glm::vec3 right() const override;
    glm::vec3 front() const override;

    void setFront(const glm::vec3 &front) override;
};

#endif // CAMERAWORLD_H

