#include "QOpenGLWidget_World.h"

QOpenGLWidget_World::QOpenGLWidget_World(QWidget * parent) : QOpenGLWidget(parent)
{

}

void QOpenGLWidget_World::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1, 0, 0, 0.5);

}

void QOpenGLWidget_World::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

}

void QOpenGLWidget_World::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT);

}
