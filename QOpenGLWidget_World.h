#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

//#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
//#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
//#include <QWidget>

//#include <QObject>
//#include <QWidget>
//#include <QMatrix4x4>
//#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
//#include <QKeyEvent>
//#include <QOpenGLVertexArrayObject>
#include "camera.h"

class QOpenGLWidget_World : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit QOpenGLWidget_World(QWidget* parent = nullptr);
    ~QOpenGLWidget_World();
    //    ~QOpenGLWidget_World();

signals:

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
//    void paintGLprivate();

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void wheelEvent(QWheelEvent * event) override;

    void focusInEvent(QFocusEvent * event) override;
//    void paintEvent(QPaintEvent *e) override;



private:
    void setCursorToCenter();
    //    void makeObject();
    void cameraMove();
    void updateProjection();

private:
    //    QOpenGLVertexArrayObject m_vao;
    int cpt =0;
    float fps;
//    float time = 0;
    QOpenGLBuffer m_vbo;
    //    QOpenGLBuffer m_ebo;
    QOpenGLVertexArrayObject m_vao;

    QOpenGLShaderProgram m_program;
    //    QOpenGLShader * m_shader;
    //    QOpenGLTexture * m_texture;
    QOpenGLTexture* m_texture;
    QOpenGLTexture* m_texture2;

    QVector3D cubePositions[10] = {
        QVector3D(0.0f, 0.0f, 0.0f),
        QVector3D(2.0f, 5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D(2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f, 3.0f, -7.5f),
        QVector3D(1.3f, -2.0f, -2.5f),
        QVector3D(1.5f, 2.0f, -2.5f),
        QVector3D(1.5f, 0.2f, -1.5f),
        QVector3D(-1.3f, 1.0f, -1.5f)
    };

//    QVector3D cameraPos;
//    QVector3D cameraFront;
//    QVector3D cameraUp;

    uint64_t deltaTime;
    uint64_t lastFrame;

    int frontDir = 0;
    int sideDir = 0;

    QPoint lastPos;
//    float fov = 60.0f;
//    float yaw = -90.0f;
//    float pitch = 0.0f;

    Camera camera;

//    float cameraSpeed;

        QMatrix4x4 m_projection;
//        QMatrix4x4 m_view;
//        QMatrix4x4 m_model;
};

#endif // QOPENGLWIDGET_WORLD_H
