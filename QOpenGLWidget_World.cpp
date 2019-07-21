#include "QOpenGLWidget_World.h"
#include <QTime>
#include <QtMath>

#include <QKeyEvent>
#include <QPainter>

#include <QOpenGLContext>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

QOpenGLWidget_World::QOpenGLWidget_World(QWidget* parent)
    : QOpenGLWidget(parent)
    //    , m_vbo(QOpenGLBuffer::VertexBuffer)
    //    , shaderCube(":/shader/first.vsh", ":/shader/first.fsh")
    //    , shaderLight(":/shader/light.vsh", ":/shader/light.fsh")
    //    , model("../Goliath-Engine/model/cube/cube.obj")
    , camera(glm::vec3(0.0f, 0.0f, 3.0f))
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{

    //    setAutoFillBackground(false);
    setMouseTracking(true);
}

QOpenGLWidget_World::~QOpenGLWidget_World()
{
    makeCurrent();

    //    doneCurrent();
}

void QOpenGLWidget_World::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    //    glFrontFace(GL_CW);
    //    glCullFace(GL_BACK);
    //    glEnable(GL_STENCIL_TEST);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //    glEnable(GL_LIGHT0);
    //    glEnable(GL_LIGHTING);
    //    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //    glEnable(GL_COLOR_MATERIAL);
    //    glEnable(GL_MULTISAMPLE);
    // ---------------------------------------------------------------------
    //    m_program.bind();

    //    shaderCube = Shader("../Goliath-Engine/shader/first.vsh", "../Goliath-Engine/shader/first.fsh");
    shader = Shader("../Goliath-Engine/shader/model_loading.vsh", "../Goliath-Engine/shader/model_loading.fsh");
    //    shader = Shader("../Goliath-Engine/shader/model_loading.vsh", "../Goliath-Engine/shader/depthTesting.fsh");
    //    shaderLight = Shader("../Goliath-Engine/shader/light.vsh", "../Goliath-Engine/shader/light.fsh");
    //    Model
    //    model =  Model("../Goliath-Engine/model/cube/cube.obj");
    scene = Model("../Goliath-Engine/map/de_aztec.obj");
    //    scene = Model("../Goliath-Engine/model/nanosuit/nanosuit.obj");

//    QGLFormat glFormat;
//      glFormat.setSampleBuffers(true);
//      glFormat.setSamples(4);

//      widget = new GLWidget(glFormat, ui->centralWidget);
//      widget->setObjectName(QStringLiteral("widget"));
//      ui->horizontalLayout->addWidget(widget);
//    QSurfaceFormat glFormat;
//    glFormat.setSamples(4);
//    this->setFormat(glFormat);

    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        // initialisation de la sortie de débogage
    }
}

void QOpenGLWidget_World::resizeGL(int w, int h)
{
    updateProjection();

    GLint bufs;
    GLint samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    qDebug("Have %d buffers and %d samples", bufs, samples);
}

void QOpenGLWidget_World::paintGL()
{
    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    fps += 1000.0 / deltaTime;
    if (cpt % 60 == 0) {
        qDebug() << "fps : " << fps / 60.0;
        fps = 0.0;
    }

    cameraMove();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glDepthMask(GL_FALSE);

    // -------------------------------------------------------------------------------

    shader.use();

    shader.setMat4("view", camera.GetViewMatrix());
    shader.setMat4("projection", m_projection);
    glm::mat4 model(1.0);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
    model = glm::scale(model, glm::vec3(0.01f));
    shader.setMat4("model", model);

    scene.Draw(shader);

    //    shader.setVec3("viewPos", camera.Position);
    //    glDrawArrays(GL_TRIANGLES, 0, 36);

    // ----------------------------------------------------------------

    update();
    ++cpt;
}

void QOpenGLWidget_World::keyPressEvent(QKeyEvent* event)
{
    //    qDebug() << "keyPressEvent";

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Comma:
        //        cameraPos += cameraFront * cameraSpeed;
        frontDir = 1;
        break;

    case Qt::Key_Down:
    case Qt::Key_O:

        frontDir = -1;
        //        cameraPos -= cameraFront * cameraSpeed;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
        sideDir = -1;
        //        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;

    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 1;
        //        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    }
}

void QOpenGLWidget_World::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Comma:
    case Qt::Key_Down:
    case Qt::Key_O:
        frontDir = 0;
        break;

    case Qt::Key_Left:
    case Qt::Key_A:
    case Qt::Key_Right:
    case Qt::Key_E:
        sideDir = 0;
        break;
    }
}

void QOpenGLWidget_World::mousePressEvent(QMouseEvent* event)
{
    //    qDebug() << "fuck";
}

void QOpenGLWidget_World::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->x() - lastPos.x();
    float dy = event->y() - lastPos.y();

    setCursorToCenter();
    camera.ProcessMouseMovement(dx, -dy);
}

void QOpenGLWidget_World::wheelEvent(QWheelEvent* event)
{
    float dy = event->delta() * 0.1f;

    camera.ProcessMouseScroll(dy);
    updateProjection();
}

void QOpenGLWidget_World::focusInEvent(QFocusEvent* event)
{
    setCursorToCenter();
    setCursor(Qt::BlankCursor);
}

void QOpenGLWidget_World::setCursorToCenter()
{
    lastPos = QPoint(width() / 2, height() / 2);
    QPoint glob = mapToGlobal(lastPos);
    QCursor::setPos(glob);
}

void QOpenGLWidget_World::cameraMove()
{
    if (frontDir == 1) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    } else if (frontDir == -1) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (sideDir == 1) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    } else if (sideDir == -1) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
}

void QOpenGLWidget_World::updateProjection()
{
    //    m_projection.setToIdentity();
    m_projection = glm::perspective(glm::radians(camera.Zoom), width() / float(height()), 0.1f, 100.0f);
}
