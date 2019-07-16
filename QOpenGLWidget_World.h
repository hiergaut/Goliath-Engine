#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
//#include <QObject>
//#include <QWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>

class QOpenGLWidget_World : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
//        Q_OBJECT

public:
    QOpenGLWidget_World(QWidget* parent);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

//    QOpenGLShaderProgram * m_program;
//    QOpenGLShader * m_shader;
//    QOpenGLTexture * m_texture;

    QMatrix4x4 m_projection;
};

#endif // QOPENGLWIDGET_WORLD_H
