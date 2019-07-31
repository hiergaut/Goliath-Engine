#include "QOpenGLWidget_3dView.h"

#include <QTime>
#include <QtMath>

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

//#include <QOpenGLContext>

#include <QCoreApplication>
//#include <QThread>
#include <engine/Environment.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <QOpenGLExtraFunctions>

//#include <opengl/OpenglContext.h>
//#include <opengl/grid.h>
namespace {
float l_near = 0.1f;
float l_far = 1000.0f;
}

QOpenGLWidget_3dView::QOpenGLWidget_3dView(QWidget* parent)
    : QWidget(parent)
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
    setFocusPolicy(Qt::ClickFocus);

    //    setAutoFillBackground(false);
    m_camera = new CameraWorld(glm::vec3(10, -10, 10), glm::vec3(0, 0, 0));
    //    setMouseTracking(true);
    //    setFocus();
    //    initializeOpenGLFunctions();
    //    setFocus();
    g_env.m_views->push_back(this);
    qDebug() << "[3dview] add " << this << "to " << g_env.m_views;
}

QOpenGLWidget_3dView::~QOpenGLWidget_3dView()
{
//    makeCurrent();

//    delete m_grid;
//    delete m_shader;
    //    doneCurrent();
}


//void QOpenGLWidget_3dView::addModel(string file)
//{
//    makeCurrent();
////    QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//    QOpenGLFunctionsCore * fun = context()->versionFunctions<QOpenGLFunctionsCore>();
//    Model model(file, fun);
//    m_models.push_back(std::move(model));
//}

//void QOpenGLWidget_3dView::initializeGL()
//{
//    fun = context()->versionFunctions<QOpenGLFunctionsCore>();
////    QOpenGLWidget::makeCurrent();
//    qDebug() << QThread::currentThreadId() << "[3dView]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();

//    //    qDebug() << "[GROUP] " << this << " 3dView : " << context()->shareGroup()->shares().size();
//    //    for (const auto & ctx : context()->shareGroup()->shares()) {
//    //        qDebug() << "\t" << ctx->functions();
//    //    }

//    //    QOpenGLContext * ctx = QOpenGLContext::currentContext();
//    //    ctx->setShareContext(g_ctx);
//    //    qDebug() << "[CONTEXT] 3dView : " << ctx;

//    //    QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//    //    QOpenGLWidget::makeCurrent();
//    //    fun->initializeOpenGLFunctions();
//    //    QOpenGLExtraFunctions * fun = QOpenGLContext::globalShareContext()->extraFunctions();
//    //    Q_ASSERT(fun);
//    //    qDebug() << "[CONTEXT] 3dView : " << fun;

//    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//    //        qDebug() << "3dview " << fun;

//    //        fun->initializeOpenGLFunctions();
//    //    QOpenGLFunctions *fun = QOpenGLContext::currentContext()->functions();
//    //    initializeOpenGLFunctions();
//    //    makeCurrent();

//    fun->glEnable(GL_DEPTH_TEST);
//    fun->glEnable(GL_CULL_FACE);
//    fun->glEnable(GL_MULTISAMPLE);

//    //    glFrontFace(GL_CW);
//    //    glCullFace(GL_BACK);
//    //    glEnable(GL_STENCIL_TEST);
//    //    glEnable(GL_BLEND);
//    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    //    glEnable(GL_LIGHT0);
//    //    glEnable(GL_LIGHTING);
//    //    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    //    glEnable(GL_COLOR_MATERIAL);
//    //    glEnable(GL_MULTISAMPLE);
//    // ---------------------------------------------------------------------
//    //    m_program.bind();

//    //        shaderCube = Shader("../Goliath-Engine/shader/first.vsh", "../Goliath-Engine/shader/first.fsh");

//    m_shader = new Shader(g_shaderPath + "model_loading.vsh", g_shaderPath + "model_loading.fsh", fun);

//    //    shader = Shader(":/resources/shader/model_loading.vsh", ":/resources/shader/model_loading.fsh");
//    //    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
//    //    vertexShader.compileSourceFile(":/shader/model_loading.vsh");

//    //    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
//    //    fragmentShader.compileSourceFile(":/shader/model_loading.fsh");

//    //    m_shader.addShader(&vertexShader);
//    //    m_shader.addShader(&fragmentShader);
//    //    m_shader.link();

//    //    m_shader = Q
//    //    qDebug() << QCoreApplication::applicationDirPath();

//    //    QFile file(":/resources/shader/model_loading.vsh");
//    //    QFile file("qrc:/resources/shader/model_loading.vsh");
//    //    QFile file(":/resources/shader/model_loading.vsh");
//    //    QFile file(":/shader/model_loading.fsh");
//    //    qDebug() << file.exists() << file.fileName();

//    //    shader = Shader(":/model_loading.vsh", ":/shader/model_loading.fsh");

//    //        shader = Shader("../Goliath-Engine/shader/model_loading.vsh", "../Goliath-Engine/shader/depthTesting.fsh");

//    //    shaderLight = Shader("../Goliath-Engine/resources/shader/light.vsh", "../../Goliath-Engine/resources/shader/light.fsh");
//    //    Model
//    //    model =  Model("../Goliath-Engine/model/cube/cube.obj");
//    //    scene = Model(":/maps/de_aztec/de_aztec.obj");

//    m_scene = new Model(g_resourcesPath + "maps/de_aztec/de_aztec.obj", fun);

//    //    scene = Model("../Goliath-Engine/model/nanosuit/nanosuit.obj");
//    m_projection = glm::perspective(glm::radians(camera->getFov()), width() / float(height()), l_near, l_far);
//    //    m_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

//    m_grid = new Grid;

//    m_axis = new Axis();

//    //    QGLFormat glFormat;
//    //      glFormat.setSampleBuffers(true);
//    //      glFormat.setSamples(4);

//    //    shaderAxis = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");

//    //      widget = new GLWidget(glFormat, ui->centralWidget);
//    //      widget->setObjectName(QStringLiteral("widget"));
//    //      ui->horizontalLayout->addWidget(widget);
//    //    QSurfaceFormat glFormat;
//    //    glFormat.setSamples(4);
//    //    this->setFormat(glFormat);

//    //    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
//    //    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
//    //    {
//    //        // initialisation de la sortie de débogage
//    //    }
//}

//void QOpenGLWidget_3dView::resizeGL(int w, int h)
//{
//    QOpenGLWidget::makeCurrent();
//    //    glViewport(0, 0, w / 2, h /2);
//    //    updateProjection();
//}

//void QOpenGLWidget_3dView::paintGL()
//{
//    QOpenGLWidget::makeCurrent();


//    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

//    //    QOpenGLFunctions *fun = QOpenGLContext::currentContext()->functions();
//    //    QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();

//    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
//    deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
//    fps += 1000.0 / deltaTime;
//    if (cpt % 60 == 0) {
//        //        qDebug() << "fps : " << fps / 60.0;
//        fps = 0.0;
//    }

//    //    cameraMove();

//    //    glViewport(0, 0, width() / 2, height() /2);
//    fun->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    fun->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //    glDepthMask(GL_FALSE);

//    // -------------------------------------------------------------------------------

//    glm::mat4 view = camera->getViewMatrix();
//    glm::mat4 projection = m_projection;
//    glm::mat4 model(1.0);
//    //    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
//    //    model = glm::scale(model, glm::vec3(0.01f));

//    m_shader->use();
//    m_shader->setMat4("view", view);
//    m_shader->setMat4("projection", projection);
//    m_shader->setMat4("model", model);

//    //        qDebug() << "[3dView] " << this << "nb model = " << g_env.m_scene.size();
//    //        for (int i =0; i <g_env.m_scene.size(); ++i) {
//    //            g_env.m_scene[i].Draw(*m_shader);
//    ////            m_scene = g_env.m_scene.at(0);
//    ////            Model & model = g_env.m_scene.at(0);
//    ////            model.Draw(*m_shader);
//    //        }

//    for (Model & model : m_models) {
//        model.Draw(*m_shader);
//    }
////    m_scene->Draw(*m_shader);

//    m_grid->draw(model, view, projection);
//    //    m_grid->draw();

//    //    shader.setVec3("viewPos", camera.Position);
//    //    glDrawArrays(GL_TRIANGLES, 0, 36);
//    fun->glViewport(5, 5, 55, 55);
//    //    glEnable(GL_LINE_SMOOTH);
//    //    glDisable(GL_LINE_SMOOTH);
//    //    glEnable(GL_LINE_SMOOTH);

//    //    glLineWidth(10);
//    //    GLfloat lineWidgthRange[2] ={0.0f, 0.0f};
//    //    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidgthRange);
//    //    qDebug() << lineWidgthRange[0] << lineWidgthRange[1];
//    m_axis->draw(view);

//    // ----------------------------------------------------------------

//    update();
//    ++cpt;
//}

void QOpenGLWidget_3dView::keyPressEvent(QKeyEvent* event)
{
            qDebug() << this << ": keyPressEvent" << event;

    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;

    case Qt::Key_Clear:
        //        qDebug() << "change projection";
        if (m_ortho) {
            m_projectionMatrix = glm::perspective(glm::radians(m_camera->getFov()), (float)width() / height(), l_near, l_far);
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
    //    setMouseTracking(true);
    //    setFocus();
    if (event->button() == Qt::MiddleButton) {
        m_middleClicked = true;
        lastPos = event->pos();
    }
    else if (event->button() == Qt::LeftButton) {
        qDebug() << this << "left clicked";
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
            m_camera->processSliding(dx, dy);

        } else {
            m_camera->processMouseMovement(dx, dy);
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
    m_camera->processMouseScroll(dy);
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

glm::mat4 QOpenGLWidget_3dView::viewMatrix() const
{
//    return m_viewMatrix;
    return m_camera->getViewMatrix();
}

glm::mat4 QOpenGLWidget_3dView::projectionMatrix() const
{
    return m_projectionMatrix;
}

//void QOpenGLWidget_3dView::setScene(Model* scene)
//{
//    m_scene = scene;
//}

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
