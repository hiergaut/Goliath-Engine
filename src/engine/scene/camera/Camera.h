#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <glm/glm.hpp>
#include <QKeyEvent>

//#include <session/Session.h>
#include <engine/scene/Object.h>
#include <engine/scene/model/Model.h>


class Camera : public Object
{
public:
    enum Type {
        WORLD,
        FPS,
    } m_type;

//    glm::vec3 m_target;
//    static Model * m_modelCamera;

public:
    Camera(float fov, const glm::vec3 & position);
    Camera(std::ifstream & file);

//    Camera(Camera * camera);
    virtual ~Camera() {}

//    virtual void load(std::ifstream & file);
    virtual void save(std::ofstream & file);

    virtual glm::mat4 viewMatrix() const = 0;

//    ~Camera() {}
//    void processMouseScroll(float dy);


    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent * event);

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void wheelEvent(QWheelEvent * event);

    virtual void focusInEvent(QFocusEvent * event);
    virtual void resizeEvent(QResizeEvent * event);

    virtual glm::vec3 front() const = 0;
    virtual glm::vec3 right() const = 0;
    virtual glm::vec3 up() const = 0;

    virtual void setFront(const glm::vec3 & front) = 0;
    virtual glm::vec3 target() const = 0;

    virtual void setDefault();

protected:
    void draw(const Shader &shader, bool dotCloud, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;
    void draw(const Shader &shader, const glm::mat4 &localTransform = glm::mat4(1.0f), const glm::mat4 &worldTransform = glm::mat4(1.0f)) const override;

    void updateBoundingBox() const override;
    void drawBoundingBox(const Shader &shader) const override;

    float m_fov;
    mutable glm::vec3 m_position;

    bool m_middleClicked = false;
    bool m_shiftPressed = false;





//    static float accuracyRotate;
//    static float accuracyMove;
//    static float accuracySlide;

public:
    float fov() const;
    const glm::vec3 & position() const;


//private:

};

#endif // CAMERA_H
