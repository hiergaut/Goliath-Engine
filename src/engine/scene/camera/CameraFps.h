#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H

//#include <version.h>
//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "Camera.h"
#include "CameraStrategy.h"
//#include "CameraWorld.h"
#include <vector>
#include <QWidget>
#include <gui/editor/3dview/MainWindow3dView.h>
//#include <QTimer>
//#include <QObject>
//#include <QWidget>

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
//const float MOUSE_SPEED = 0.1f;
//const float ZOOM_SPEED = 0.1f;
//const float MOVE_SPEED = 0.1f;
//const float ZOOM = 60.0f;

const float ZOOM_MAX = 1.0f;
const float ZOOM_MIN = 170.0f;
//}

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class CameraFps : public CameraStrategy {
//    Q_OBJECT
public:
    MainWindow3dView * m_view = nullptr;

public:
//    CameraFps(glm::vec3 position, glm::vec3 target);
//    CameraFps(std::ifstream & file);
//    CameraFps(MainWindow3dView *view);
//    CameraFps(float fov, const glm::vec3 & position, float yaw, float pitch, MainWindow3dView *view);
    CameraFps(std::ifstream &file, Model & model, float & fov);
    CameraFps(const glm::vec3 &position, float yaw, float pitch, MainWindow3dView *view, Model & model, float & fov);
//    CameraFps(MainWindow3dView *view, glm::mat4 &modelTransform);
//    CameraFps(CameraWorld * camera, MainWindow3dView *view);
    ~CameraFps() override;
//    CameraFps(float posX, float posY, float posZ, float yaw, float pitch);

//    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

//    glm::mat4 viewMatrix() const override;
    void ProcessKeyboard() const;

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void updateCameraVectors();

    void updateCenter();
//    void updateView();
    void trackingOn();
    void trackingOff();

    void startFpsView();


    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

//    void focusInEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    float & m_fov;

//    QTimer * timer;
    //    QWidget * m_view;
    // Camera Attributes
    QPoint m_center;
    QPoint m_centerLocal;
//    QPoint m_lastPos;
//    glm::vec3 Position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
//    glm::vec3 m_worldUp;
    // Euler Angles
    float m_yaw;
    float m_pitch;

    float frontDir = 0.0f;
    float sideDir = 0.0f;

    mutable uint64_t m_lastTime;
    // Camera options
//    float MovementSpeed;
//    float MouseSensitivity;
//    float Zoom;

    // Constructor with vectors

    // Calculates the front vector from the Camera's (updated) Euler Angles
public:
//    void setDefault() override;
    void setTarget(const glm::vec3 &target) override;
    void setFront(const glm::vec3 &front) override;

    glm::vec3 front() const override;
    glm::vec3 up() const override;
    glm::vec3 right() const override;
    glm::vec3 target() const override;

//    void autoRefreshMoving();
};
#endif
