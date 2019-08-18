#include "MainWindow3dView.h"
#include "ui_MainWindow3dView.h"


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

std::list<const MainWindow3dView *> * MainWindow3dView::m_views;

namespace {
float l_near = 0.1f;
float l_far = 100000.0f;
}

//MainWindow3dView::MainWindow3dView(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow3dView)
//{
//    ui->setupUi(this);
//}

//MainWindow3dView::~MainWindow3dView()
//{
//    delete ui;
//}


MainWindow3dView::MainWindow3dView(QWidget* parent)
//    : QWidget(parent),
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow3dView)
//{
//    ui->setupUi(this);
//}

    ,m_camera(glm::vec3(200, -200, 200), glm::vec3(0, 0, 0))
//    , m_scene { scene }
//    , m_vbo(QOpenGLBuffer::VertexBuffer)
//    , shaderCube(":/shader/first.vsh", ":/shader/first.fsh")
//    , shaderLight(":/shader/light.vsh", ":/shader/light.fsh")
//    , model("../Goliath-Engine/model/cube/cube.obj")
//    , camera(glm::vec3(0.0f, 0.0f, 3.0f))
//    , m_shader(":/shader/model_loading.vsh", ":/shader/model_loading.fsh")
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{

    ui->setupUi(this);
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
//    QMenu shading("Shading");
//    m_views->emplace_back(shading);


//    QMenu shading("Shading");
//    m_menus.emplace_back("Shading");
//    m_menus.emplace_back(std::move(shading));
//    m_menus.push_back(std::move(shading));
//    m_menus.emplace_back("Shading");

    m_menus.push_back(ui->menuShading);

    ui->menubar->hide();
//    for (QMenu & menu : m_menus) {
//        qDebug() << menu.title();
//    }
//    m_menus.push_back(shading);

}

MainWindow3dView::~MainWindow3dView()
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

void MainWindow3dView::load(std::ifstream &file)
{
    m_camera.load(file);

}

void MainWindow3dView::save(std::ofstream &file)
{
    m_camera.save(file);

}



void MainWindow3dView::keyPressEvent(QKeyEvent* event)
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

void MainWindow3dView::keyReleaseEvent(QKeyEvent* event)
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

void MainWindow3dView::mousePressEvent(QMouseEvent* event)
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

void MainWindow3dView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = false;
    }
}

void MainWindow3dView::mouseMoveEvent(QMouseEvent* event)
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

void MainWindow3dView::wheelEvent(QWheelEvent* event)
{
    float dy = event->delta();

    if (m_ortho) {
        orthoSize += -dy * 0.01;
        m_projectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, l_near, l_far);
    }
    m_camera.processMouseScroll(dy);
    //    updateProjection();
}

void MainWindow3dView::focusInEvent(QFocusEvent* event)
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

void MainWindow3dView::resizeEvent(QResizeEvent *event)
{
    m_projectionMatrix = glm::perspective(glm::radians(m_camera.getFov()), (float)width() / height(), l_near, l_far);

}

void MainWindow3dView::setFocusPolicy(Qt::FocusPolicy policy)
{
    QWidget::setFocusPolicy(policy);
}

QWidget *MainWindow3dView::widget()
{
    return this;
}

//std::list<QMenu> MainWindow3dView::menus() const
//{
//    return m_menus;
//}

const CameraWorld * MainWindow3dView::camera() const
{
    return &m_camera;
}

//void MainWindow3dView::setViews(std::list<const MainWindow3dView *> *views)
//{
//    m_views = views;
//}

glm::mat4 MainWindow3dView::viewMatrix() const
{
    //    return m_viewMatrix;
    return m_camera.getViewMatrix();
}

glm::mat4 MainWindow3dView::projectionViewMatrix() const
{
    return m_projectionMatrix * m_camera.getViewMatrix();

}

void MainWindow3dView::setViews(std::list<const MainWindow3dView *> *views)
{
    m_views = views;
}

glm::mat4 MainWindow3dView::projectionMatrix() const
{
    return m_projectionMatrix;
}

void MainWindow3dView::on_actionWireFrame_triggered()
{
   qDebug() << "wireFrame";
}
