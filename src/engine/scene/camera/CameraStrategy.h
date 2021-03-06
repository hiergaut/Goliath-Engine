#ifndef CAMERASTRATEGY_H
#define CAMERASTRATEGY_H

#include <QKeyEvent>
#include <glm/glm.hpp>
#include <iostream>
#include <engine/scene/model/Model.h>
#include <opengl/Frustum.h>
//#include <engine/scene/camera/Camera.h>

class CameraStrategy {
public:
    enum Type {
        WORLD,
        FPS,
    } m_type;


public:
    //    glm::vec3 m_target;
    //    static Model * m_modelCamera;

    glm::mat4 & m_modelTransform;

    Model & m_model;
    std::list<uint> m_nearestPointLights;

//    Camera & m_camera;

    //    virtual void load(std::ifstream & file);

//    virtual glm::mat4 viewMatrix() const = 0;

//    protected:
//    CameraStrategy() = delete ;
public:
    CameraStrategy(glm::mat4 & modelTransform, uint & id, Model & model);
//    CameraStrategy(Model & model, uint &id);
//    virtual CameraStrategy(std::ifstream & file);
    virtual ~CameraStrategy() = default;

    //    ~Camera() {}
    //    void processMouseScroll(float dy);
    virtual void save(std::ofstream& file) = 0;

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

    virtual void focusInEvent(QFocusEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

//    virtual void setDefault() = 0;
    virtual void setTarget(const glm::vec3 & target) = 0;
    virtual void setFront(const glm::vec3& front) = 0;

    virtual glm::vec3 front() const = 0;
    virtual glm::vec3 right() const = 0;
    virtual glm::vec3 up() const = 0;

    virtual glm::vec3 target() const = 0;
//    virtual glm::vec3 position() const = 0;

//    virtual void updateModelTransform(const glm::mat4 & modelTransform) = 0;
    void updateModelTransform(glm::mat4 && modelTransform);
    void updateAttachFrustumViews();
    void updateNearestPointLights();


protected:
    //    mutable glm::vec3 m_position;
    uint & m_id;

    bool m_middleClicked = false;
    bool m_shiftPressed = false;

    float m_cptMovingStep =0;

//    Frustum m_frustum;

public:
//    float fov() const;
//    const glm::vec3 position() const;
};

#endif // CAMERASTRATEGY_H
