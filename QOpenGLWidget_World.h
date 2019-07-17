#ifndef QOPENGLWIDGET_WORLD_H
#define QOPENGLWIDGET_WORLD_H

//#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
//#include <QWidget>

//#include <QObject>
//#include <QWidget>
//#include <QMatrix4x4>
//#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
//#include <QOpenGLVertexArrayObject>

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

private:
//    void makeObject();


private:
    //    QOpenGLVertexArrayObject m_vao;
    float time =0;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo;
    QOpenGLVertexArrayObject m_vao;

    QOpenGLShaderProgram m_program;
    //    QOpenGLShader * m_shader;
    //    QOpenGLTexture * m_texture;
    QOpenGLTexture * m_texture;
    QOpenGLTexture * m_texture2;

    //    QMatrix4x4 m_projection;
};

#endif // QOPENGLWIDGET_WORLD_H
