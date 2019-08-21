#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H

//#include <version.h>
//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include <vector>
#include <QWidget>
#include <gui/editor/3dview/MainWindow3dView.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
//namespace CameraFps {

//const float YAW = -90.0f;
//const float PITCH = 0.0f;
const float SPEED = 0.1f;
const float SENSITIVITY = 0.1f;
//const float ZOOM = 60.0f;

const float ZOOM_MAX = 1.0f;
const float ZOOM_MIN = 170.0f;
//}

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class CameraFps : public Camera {
public:
//    CameraFps(glm::vec3 position, glm::vec3 target);
    CameraFps(glm::vec3 position, float yaw, float pitch, MainWindow3dView *view);
//    CameraFps(float posX, float posY, float posZ, float yaw, float pitch);

    glm::mat4 viewMatrix() const override;
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void updateCameraVectors();

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
//    QWidget * m_view;
    MainWindow3dView * m_view;
    // Camera Attributes
    QPoint m_center;
    QPoint m_centerLocal;
    QPoint m_lastPos;
//    glm::vec3 Position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
//    glm::vec3 m_worldUp;
    // Euler Angles
    float m_yaw;
    float m_pitch;
    // Camera options
//    float MovementSpeed;
//    float MouseSensitivity;
//    float Zoom;

    // Constructor with vectors

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
};
#endif
