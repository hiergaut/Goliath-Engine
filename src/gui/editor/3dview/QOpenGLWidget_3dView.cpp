#include "QOpenGLWidget_3dView.h"

#include <QTime>
#include <QtMath>

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

//#include <QOpenGLContext>

#include <QCoreApplication>
//#include <QThread>
//#include <engine/Environment.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <QOpenGLExtraFunctions>

//#include <opengl/OpenglContext.h>
//#include <opengl/grid.h>

std::list<const QOpenGLWidget_3dView *> * QOpenGLWidget_3dView::m_views;

namespace {
float l_near = 0.1f;
float l_far = 1000.0f;
}

QOpenGLWidget_3dView::QOpenGLWidget_3dView(QWidget* parent)
    : QWidget(parent),

    m_camera(glm::vec3(200, -200, 200), glm::vec3(0, 0, 0))
//    , m_scene { scene }
//    , m_vbo(QOpenGLBuffer::VertexBuffer)
//    , shaderCube(":/shader/first.vsh", ":/shader/first.fsh")
//    , shaderLight(":/shader/light.vsh", ":/shader/light.fsh")
//    , model("../Goliath-Engine/model/cube/cube.obj")
//    , camera(glm::vec3(0.0f, 0.0f, 3.0f))
//    , m_shader(":/shader/model_loading.vsh", ":/shader/model_loading.fsh")
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{

    //    g_openglContext.
    //    fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    fun = g_openglContext.m_fun;
    //    fun = g_fun;
//    setFocusPolicy(Qt::ClickFocus);

    //    setAutoFillBackground(false);
    m_projectionMatrix = glm::perspective(glm::radians(m_camera.getFov()), (float)width() / height(), l_near, l_far);
    //    setMouseTracking(true);
    //    setFocus();
    //    initializeOpenGLFunctions();
    //    setFocus();
    m_views->push_back(this);
//    qDebug() << "[3dView]" << this << "created";
//    g_env.m_views.push_back(this);
//    qDebug() << "[3dview] add " << this << "to " << g_env.m_views;
}

QOpenGLWidget_3dView::~QOpenGLWidget_3dView()
{
//    makeCurrent();
//    qDebug() << "[3dView]" << this << "deleted";

//    g_env.m_views.remove(this);
//    qDebug() << "[3dView] " << this << "remove in views " << g_env.m_views;
    Q_ASSERT(m_views);
    m_views->remove(this);

//    delete m_grid;
//    delete m_shader;
    //    doneCurrent();
}

void QOpenGLWidget_3dView::load(std::ifstream &file)
{
    m_camera.load(file);

}

void QOpenGLWidget_3dView::save(std::ofstream &file)
{
    m_camera.save(file);

}



void QOpenGLWidget_3dView::keyPressEvent(QKeyEvent* event)
{
//            qDebug() << this << ": keyPressEvent" << event;

    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;

    case Qt::Key_Clear:
        //        qDebug() << "change projection";
        if (m_ortho) {
            m_projectionMatrix = glm::perspective(glm::radians(m_camera.getFov()), (float)width() / height(), l_near, l_far);
        } else {
            m_projectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, l_near, l_far);
        }
        m_ortho = !m_ortho;
        //        update();
        break;
        //    case Qt::Key_Escape:
        //        setMouseTracking(false);
        //        break;

        //    case Qt::Key_Up:
        //    case Qt::Key_Comma:
        //        //        cameraPos += cameraFront * cameraSpeed;
        //        frontDir = 1;
        //        break;

        //    case Qt::Key_Down:
        //    case Qt::Key_O:

        //        frontDir = -1;
        //        //        cameraPos -= cameraFront * cameraSpeed;
        //        break;

        //    case Qt::Key_Left:
        //    case Qt::Key_A:
        //        sideDir = -1;
        //        //        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        //        break;

        //    case Qt::Key_Right:
        //    case Qt::Key_E:
        //        sideDir = 1;
        //        //        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        //        break;
    }
}

void QOpenGLWidget_3dView::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = false;
        break;
        //    case Qt::Key_Up:
        //    case Qt::Key_Comma:
        //    case Qt::Key_Down:
        //    case Qt::Key_O:
        //        frontDir = 0;
        //        break;

        //    case Qt::Key_Left:
        //    case Qt::Key_A:
        //    case Qt::Key_Right:
        //    case Qt::Key_E:
        //        sideDir = 0;
        //        break;
    }
}

void QOpenGLWidget_3dView::mousePressEvent(QMouseEvent* event)
{
//    qDebug() << "[3dView]" << QWidget::mapToGlobal(pos());
    //    setMouseTracking(true);
    //    setFocus();
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        lastPos = event->pos();
    }
    else if (event->button() == Qt::LeftButton) {
//        qDebug() << this << "left clicked";
    }
    event->ignore(); // splitter node
}

void QOpenGLWidget_3dView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = false;
    }
}

void QOpenGLWidget_3dView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_middleClicked) {
        float dx = event->x() - lastPos.x();
        //    float dx = event->x();
        float dy = event->y() - lastPos.y();
        lastPos = event->pos();
        //    float dy = event->y();

        //    setCursorToCenter();
        //    qDebug() << dx << dy;
        if (m_shiftPressed) {
            m_camera.processSliding(dx, dy);

        } else {
            m_camera.processMouseMovement(dx, dy);
        }
    }
}

void QOpenGLWidget_3dView::wheelEvent(QWheelEvent* event)
{
    float dy = event->delta();

    if (m_ortho) {
        orthoSize += -dy * 0.01;
        m_projectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, l_near, l_far);
    }
    m_camera.processMouseScroll(dy);
    //    updateProjection();
}

void QOpenGLWidget_3dView::focusInEvent(QFocusEvent* event)
{
    m_shiftPressed = false;
//    qDebug() << this << ": focusInEvent";
    //    setCursorToCenter();
    //    setCursor(Qt::BlankCursor);
    //    setMouseTracking(true);

    //    GLint bufs;
    //    GLint samples;
    //    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    //    glGetIntegerv(GL_SAMPLES, &samples);
    //    qDebug("Have %d buffers and %d samples", bufs, samples);
}

void QOpenGLWidget_3dView::resizeEvent(QResizeEvent *event)
{
    m_projectionMatrix = glm::perspective(glm::radians(m_camera.getFov()), (float)width() / height(), l_near, l_far);

}

const CameraWorld * QOpenGLWidget_3dView::camera() const
{
    return &m_camera;
}

//void QOpenGLWidget_3dView::setViews(std::list<const QOpenGLWidget_3dView *> *views)
//{
//    m_views = views;
//}

glm::mat4 QOpenGLWidget_3dView::viewMatrix() const
{
    //    return m_viewMatrix;
    return m_camera.getViewMatrix();
}

void QOpenGLWidget_3dView::setViews(std::list<const QOpenGLWidget_3dView *> *views)
{
    m_views = views;
}

glm::mat4 QOpenGLWidget_3dView::projectionMatrix() const
{
    return m_projectionMatrix;
}
