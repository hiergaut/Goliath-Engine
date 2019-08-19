#ifndef CAMERAWORLD_H
#define CAMERAWORLD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <QDebug>
#include <iostream>

namespace  {
    float accuracyRotate = 0.005f;
    float accuracyMove = 0.001f;
    float accuracySlide = 0.05f;

}

class CameraWorld {
public:
    CameraWorld(glm::vec3 position, glm::vec3 target);
    glm::mat4 getViewMatrix() const;
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    void processSliding(float dx, float dy);
    float getFov() const;

    void load(std::ifstream & file);
    void save(std::ofstream & file);

    glm::vec3 getPosition() const;

private:

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    float m_fov = 50.0f;
};

#endif // CAMERAWORLD_H

