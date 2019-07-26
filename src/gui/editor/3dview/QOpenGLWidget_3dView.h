#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

//#include "version.h"
#include <opengl/version.h>

#include <QOpenGLBuffer>
#include <QOpenGLWidget>

#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <opengl/grid.h>
#include <opengl/axis.h>

//#include "camera.h"
//#include "camera.h"
#include <opengl/CameraWorld.h>
//#include <opengl/camera.h>
//#include "shader.h"
#include <opengl/shader.h>
//#include "model.h"
#include <opengl/model.h>

class QOpenGLWidget_3dView : public QOpenGLWidget, QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit QOpenGLWidget_3dView(QWidget* parent = nullptr);
    ~QOpenGLWidget_3dView();

signals:

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

private:
//    void setCursorToCenter();
//    void cameraMove();
//    void updateProjection();

private:
    int cpt = 0;
    float fps;

    bool m_middleClicked = false;
    //    QOpenGLBuffer m_vbo;
    //    QOpenGLBuffer m_ebo;
//    Shader shader;
    Model * scene;
//    Shader shaderLight;
    Grid * m_grid;

    Axis m_axis;

    bool m_ortho = false;
    float orthoSize = 10.0f;

//    Shader * shaderAxis;
//    QOpenGLShaderProgram m_shader;
//    QOpenGLVertexArrayObject m_vao;
    //    QOpenGLVertexArrayObject m_vaoLight;

    //    QOpenGLShaderProgram m_program;
    //    QOpenGLShaderProgram m_programLight;

    //    QOpenGLShader * m_shader;
    //    QOpenGLTexture * m_texture;
//    QOpenGLTexture* m_texture;
//    QOpenGLTexture* m_texture2;

//    glm::vec3 cubePositions[10] = {
//        glm::vec3(0.0f, 0.0f, 0.0f),
//        glm::vec3(2.0f, 5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f, 3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f, 2.0f, -2.5f),
//        glm::vec3(1.5f, 0.2f, -1.5f),
//        glm::vec3(-1.3f, 1.0f, -1.5f)
//    };

//    glm::vec3 pointLightPositions[4] = {
//        glm::vec3(0.7f, 0.2f, 2.0f),
//        glm::vec3(2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f, 2.0f, -12.0f),
//        glm::vec3(0.0f, 0.0f, -3.0f)
//    };

    uint64_t deltaTime;
    uint64_t lastFrame;

    int frontDir = 0;
    int sideDir = 0;

    QPoint lastPos;
    bool m_shiftPressed = false;

//    Camera camera;
    CameraWorld * camera;

    glm::mat4 m_projection;
};

#endif // QOPENGLWIDGET_WORLD_H
