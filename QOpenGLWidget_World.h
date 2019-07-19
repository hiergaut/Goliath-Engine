#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>

#include "camera.h"

class QOpenGLWidget_World : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit QOpenGLWidget_World(QWidget* parent = nullptr);
    ~QOpenGLWidget_World();

signals:

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void focusInEvent(QFocusEvent* event) override;

private:
    void setCursorToCenter();
    void cameraMove();
    void updateProjection();

private:
    int cpt = 0;
    float fps;
//    QOpenGLBuffer m_vbo;
    //    QOpenGLBuffer m_ebo;
    QOpenGLVertexArrayObject m_vao;
//    QOpenGLVertexArrayObject m_vaoLight;

    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram m_programLight;

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

    QVector3D pointLightPositions[4] = {
       QVector3D(0.7f, 0.2f, 2.0f),
       QVector3D(2.3f, -3.3f, -4.0f),
       QVector3D(-4.0f, 2.0f, -12.0f),
       QVector3D(0.0f, 0.0f, -3.0f)
    };

    uint64_t deltaTime;
    uint64_t lastFrame;

    int frontDir = 0;
    int sideDir = 0;

    QPoint lastPos;

    Camera camera;

    QMatrix4x4 m_projection;
};

#endif // QOPENGLWIDGET_WORLD_H
