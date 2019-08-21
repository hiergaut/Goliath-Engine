#ifndef CAMERAWORLD_H
#define CAMERAWORLD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <QDebug>
#include <iostream>
#include "Camera.h"


class CameraWorld : public Camera {
public:
    CameraWorld(glm::vec3 position, glm::vec3 target);

    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    void processSliding(float dx, float dy);
//    float getFov() const;



protected:
    void load(std::ifstream & file) override;
    void save(std::ofstream & file) override;
    glm::mat4 viewMatrix() const override;


    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    glm::vec3 m_target;

    QPoint lastPos;

public:
};

#endif // CAMERAWORLD_H

