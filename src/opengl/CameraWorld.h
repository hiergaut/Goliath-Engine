#ifndef CAMERAWORLD_H
#define CAMERAWORLD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace  {
    float accuracyRotate = 0.005f;
    float accuracyMove = 0.001f;
    float accuracySlide = 0.05f;

}

class CameraWorld {
public:
    CameraWorld(glm::vec3 position, glm::vec3 target)
        : m_position { position }
        , m_target { target }
    {

//        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(m_position, m_target, glm::vec3(0, 0, 1));
    }

    void processMouseMovement(float xoffset, float yoffset) {
        glm::vec3 v = m_position - m_target;
        float dist = glm::length(v);
        v = glm::normalize(v);
        glm::mat4 m(1.0);
        glm::vec3 xy = glm::cross(v, glm::vec3(0, 0, 1));
        m = glm::rotate(m, -xoffset * accuracyRotate, glm::vec3(0, 0, 1));
        m = glm::rotate(m, yoffset * accuracyRotate, xy);

        v = m * glm::vec4(v, 1.0);
        m_position = v * dist + m_target;

    }

    void processMouseScroll(float yoffset) {
        glm::vec3 front = m_target - m_position;
        m_position += accuracyMove * front * yoffset;

    }

    void processSliding(float dx, float dy) {
        glm::vec3 front = m_target -m_position;
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 0, 1)));
        glm::vec3 up = glm::normalize(glm::cross(front, right));

        glm::vec3 slide = accuracySlide * (right * -dx + up * -dy);
        m_position += slide;
        m_target += slide;
    }

    float getFov() const {
        return m_fov;
    }

private:
    //    void updateCameraVectors() {

//    }

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    float m_fov = 50.0f;
};

#endif // CAMERAWORLD_H

