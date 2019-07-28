#include "QOpenGLWidget_3dView.h"

#include <QTime>
#include <QtMath>

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

//#include <QOpenGLContext>

#include <QCoreApplication>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <opengl/grid.h>

QOpenGLWidget_3dView::QOpenGLWidget_3dView(QWidget* parent)
    : QOpenGLWidget(parent)
//    , m_vbo(QOpenGLBuffer::VertexBuffer)
//    , shaderCube(":/shader/first.vsh", ":/shader/first.fsh")
//    , shaderLight(":/shader/light.vsh", ":/shader/light.fsh")
//    , model("../Goliath-Engine/model/cube/cube.obj")
//    , camera(glm::vec3(0.0f, 0.0f, 3.0f))
//    , m_shader(":/shader/model_loading.vsh", ":/shader/model_loading.fsh")
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{

    //    setAutoFillBackground(false);
    //    setMouseTracking(true);
    //    setFocus();
    //    initializeOpenGLFunctions();
    //    setFocus();
}

QOpenGLWidget_3dView::~QOpenGLWidget_3dView()
{
    makeCurrent();

    delete m_grid;
    //    doneCurrent();
}

void QOpenGLWidget_3dView::initializeGL()
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

    //        shaderCube = Shader("../Goliath-Engine/shader/first.vsh", "../Goliath-Engine/shader/first.fsh");

    //    shader = Shader(resourcesPath + "shader/model_loading.vsh", resourcesPath + "shader/model_loading.fsh");

    //    shader = Shader(":/resources/shader/model_loading.vsh", ":/resources/shader/model_loading.fsh");
    //    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    //    vertexShader.compileSourceFile(":/shader/model_loading.vsh");

    //    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    //    fragmentShader.compileSourceFile(":/shader/model_loading.fsh");

    //    m_shader.addShader(&vertexShader);
    //    m_shader.addShader(&fragmentShader);
    //    m_shader.link();

    //    m_shader = Q
    //    qDebug() << QCoreApplication::applicationDirPath();

    //    QFile file(":/resources/shader/model_loading.vsh");
    //    QFile file("qrc:/resources/shader/model_loading.vsh");
    //    QFile file(":/resources/shader/model_loading.vsh");
    //    QFile file(":/shader/model_loading.fsh");
    //    qDebug() << file.exists() << file.fileName();

    //    shader = Shader(":/shader/model_loading.vsh", ":/shader/model_loading.fsh");

    //        shader = Shader("../Goliath-Engine/shader/model_loading.vsh", "../Goliath-Engine/shader/depthTesting.fsh");

    //    shaderLight = Shader("../Goliath-Engine/resources/shader/light.vsh", "../../Goliath-Engine/resources/shader/light.fsh");
    //    Model
    //    model =  Model("../Goliath-Engine/model/cube/cube.obj");
    //    scene = Model(resourcesPath + "maps/de_aztec/de_aztec.obj");
    //    scene = Model(":/maps/de_aztec/de_aztec.obj");

    //    scene = Model("../Goliath-Engine/model/nanosuit/nanosuit.obj");
    camera = new CameraWorld(glm::vec3(10, -10, 10), glm::vec3(0, 0, 0));
    m_projection = glm::perspective(glm::radians(camera->getFov()), width() / float(height()), 0.1f, 100.0f);
    //    m_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

    m_grid = new Grid;

    m_axis = new Axis();

    //    QGLFormat glFormat;
    //      glFormat.setSampleBuffers(true);
    //      glFormat.setSamples(4);

    //    shaderAxis = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");

    //      widget = new GLWidget(glFormat, ui->centralWidget);
    //      widget->setObjectName(QStringLiteral("widget"));
    //      ui->horizontalLayout->addWidget(widget);
    //    QSurfaceFormat glFormat;
    //    glFormat.setSamples(4);
    //    this->setFormat(glFormat);

    //    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    //    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    //    {
    //        // initialisation de la sortie de débogage
    //    }
}

void QOpenGLWidget_3dView::resizeGL(int w, int h)
{
    //    glViewport(0, 0, w / 2, h /2);
    //    updateProjection();
}

void QOpenGLWidget_3dView::paintGL()
{
    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    fps += 1000.0 / deltaTime;
    if (cpt % 60 == 0) {
        //        qDebug() << "fps : " << fps / 60.0;
        fps = 0.0;
    }

    //    cameraMove();

    //    glViewport(0, 0, width() / 2, height() /2);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glDepthMask(GL_FALSE);

    // -------------------------------------------------------------------------------

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = m_projection;
    glm::mat4 model(1.0);
    //    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
    //    model = glm::scale(model, glm::vec3(0.01f));

    //    shader.use();
    //    shader.setMat4("view", view);
    //    shader.setMat4("projection", projection);
    //    shader.setMat4("model", model);

    //    scene.Draw(shader);

    m_grid->draw(model, view, projection);
    //    m_grid->draw();

    //    shader.setVec3("viewPos", camera.Position);
    //    glDrawArrays(GL_TRIANGLES, 0, 36);
    glViewport(5, 5, 55, 55);
    //    glEnable(GL_LINE_SMOOTH);
    //    glDisable(GL_LINE_SMOOTH);
    //    glEnable(GL_LINE_SMOOTH);

    //    glLineWidth(10);
    //    GLfloat lineWidgthRange[2] ={0.0f, 0.0f};
    //    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidgthRange);
    //    qDebug() << lineWidgthRange[0] << lineWidgthRange[1];
    m_axis->draw(view);

    // ----------------------------------------------------------------

    update();
    ++cpt;
}

void QOpenGLWidget_3dView::keyPressEvent(QKeyEvent* event)
{
    //        qDebug() << this << ": keyPressEvent" << event;

    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;

    case Qt::Key_Clear:
        //        qDebug() << "change projection";
        if (m_ortho) {
            m_projection = glm::perspective(glm::radians(camera->getFov()), (float)width() / height(), 0.1f, 100.0f);
        } else {
            m_projection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, 0.1f, 100.0f);
        }
        m_ortho = !m_ortho;
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
    //    setMouseTracking(true);
    //    setFocus();
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        lastPos = event->pos();
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
            camera->processSliding(dx, dy);

        } else {
            camera->processMouseMovement(dx, dy);
        }
    }
}

void QOpenGLWidget_3dView::wheelEvent(QWheelEvent* event)
{
    float dy = event->delta();

    if (m_ortho) {
        orthoSize += -dy * 0.01;
        m_projection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, 0.1f, 100.0f);
    }
    camera->processMouseScroll(dy);
    //    updateProjection();
}

void QOpenGLWidget_3dView::focusInEvent(QFocusEvent* event)
{
    qDebug() << this << ": focusInEvent";
    //    setCursorToCenter();
    //    setCursor(Qt::BlankCursor);
    //    setMouseTracking(true);

    //    GLint bufs;
    //    GLint samples;
    //    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    //    glGetIntegerv(GL_SAMPLES, &samples);
    //    qDebug("Have %d buffers and %d samples", bufs, samples);
}

//void QOpenGLWidget_3dView::setCursorToCenter()
//{
//    lastPos = QPoint(width() / 2, height() / 2);
//    QPoint glob = mapToGlobal(lastPos);
//    QCursor::setPos(glob);
//}

//void QOpenGLWidget_3dView::cameraMove()
//{
//    if (frontDir == 1) {
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    } else if (frontDir == -1) {
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    }

//    if (sideDir == 1) {
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    } else if (sideDir == -1) {
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    }
//}

//void QOpenGLWidget_3dView::updateProjection()
//{
//    //    m_projection.setToIdentity();
//    m_projection = glm::perspective(glm::radians(camera->getFov()), width() / float(height()), 0.1f, 100.0f);
//}