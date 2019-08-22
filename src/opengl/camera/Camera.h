#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <glm/glm.hpp>
#include <QKeyEvent>



class Camera
{
public:
    enum Type {
        WORLD,
        FPS,
    } m_type;

public:
    Camera(float fov, glm::vec3 position);
//    Camera(Camera * camera);
    virtual ~Camera() {}

    virtual void load(std::ifstream & file);
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

protected:
    float m_fov;
    mutable glm::vec3 m_position;

    bool m_middleClicked = false;
    bool m_shiftPressed = false;



    static float accuracyRotate;
    static float accuracyMove;
    static float accuracySlide;

public:
    float fov() const;
    const glm::vec3 & position() const;


//private:

};

#endif // CAMERA_H
