#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

//#include "version.h"
//#include <opengl/version.h>

//#include <QOpenGLBuffer>
//#include <QOpenGLWidget>

//#include <QOpenGLFunctions_3_3_Core>

//#include <QOpenGLShaderProgram>
//#include <QOpenGLTexture>
//#include <QOpenGLVertexArrayObject>
//#include <opengl/grid.h>
//#include <opengl/axis.h>

//#include "camera.h"
//#include "camera.h"
#include <opengl/CameraWorld.h>
//#include <opengl/camera.h>
//#include "shader.h"
#include <opengl/shader.h>
//#include "model.h"
//#include <opengl/model.h>
#include <QWidget>


class QOpenGLWidget_3dView : public QWidget {
    Q_OBJECT

public:
    explicit QOpenGLWidget_3dView(QWidget* parent = nullptr);
    ~QOpenGLWidget_3dView();


//    void setScene(Model *scene);
//    void addModel(std::string file);
    void load(std::ifstream & file);
    void save(std::ofstream & file);


signals:

protected:
    //    void initializeGL() override;
//    void resizeGL(int w, int h) override;
//    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
//    void setCursorToCenter();
//    void cameraMove();
//    void updateProjection();

private:

    bool m_middleClicked = false;

    bool m_ortho = false;
    float orthoSize = 10.0f;


    int frontDir = 0;
    int sideDir = 0;

    QPoint lastPos;
    bool m_shiftPressed = false;

//    Camera camera;
    CameraWorld m_camera;

    glm::mat4 m_projectionMatrix;

    static std::list<const QOpenGLWidget_3dView*> * m_views;

//    glm::mat4 m_viewMatrix;

public:
    glm::mat4 projectionMatrix() const;
    glm::mat4 viewMatrix() const;
    static void setViews(std::list<const QOpenGLWidget_3dView *> *views);

    const CameraWorld * camera() const;
};


//std::list<const QOpenGLWidget_3dView *> * l_views;

#endif // QOPENGLWIDGET_WORLD_H
