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
#include <opengl/camera/CameraFps.h>
#include <opengl/camera/CameraWorld.h>

//#include <opengl/OpenglContext.h>
//#include <opengl/grid.h>
#include <opengl/rayTracer/RayTracer.h>

std::list<const MainWindow3dView*>* MainWindow3dView::m_views;
//Shader MainWindow3dView::m_shaders;
Shader* MainWindow3dView::m_shaders[Shading::size];

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
    , ui(new Ui::MainWindow3dView)
//{
//    ui->setupUi(this);
//}
//    , m_camera

//    , m_camera = new CameraWorld(glm::vec3(200, -200, 200), glm::vec3(0, 0, 0))

//    , m_scene { scene }
//    , m_vbo(QOpenGLBuffer::VertexBuffer)
//    , shaderCube(":/shader/first.vsh", ":/shader/first.fsh")
//    , shaderLight(":/shader/light.vsh", ":/shader/light.fsh")
//    , model("../Goliath-Engine/model/cube/cube.obj")
//    , camera(glm::vec3(0.0f, 0.0f, 3.0f))
//    , m_shader(":/shader/model_loading.vsh", ":/shader/model_loading.fsh")
//    , m_ebo(QOpenGLBuffer::IndexBuffer)
{
    m_camera = new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0));
    //    m_camera = new CameraFps(glm::vec3(200.0f, -200.0f, 200.0f), 135.0f, -45.0f, this);

    ui->setupUi(this);
    //    g_openglContext.
    //    fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    fun = g_openglContext.m_fun;
    //    fun = g_fun;
    //    setFocusPolicy(Qt::ClickFocus);

    //    setAutoFillBackground(false);
    m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
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

    m_menus.push_back(ui->menuInteraction_Mode);
    //    ui->menuInteraction_Mode->setIcon(ui->actionObject_Mode->icon());
    m_menus.push_back(ui->menuCurent_Mode);

    m_mode = EDIT;
    setMode(OBJECT);

    m_menus.push_back(ui->menuX_Ray);
    ui->menuX_Ray->setIcon(ui->actionX_Rays->icon());

    m_menus.push_back(ui->menuWireFrame);
    ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());

    m_menus.push_back(ui->menuSkeleton);
    ui->menuSkeleton->setIcon(ui->actionSkeleton->icon());

    m_menus.push_back(ui->menuNormal);
    ui->menuNormal->setIcon(ui->actionNormal_2->icon());

    m_menus.push_back(ui->menuBoundingBox);
    ui->menuBoundingBox->setIcon(ui->actionBoundingBox->icon());

    m_menus.push_back(ui->menuDotCloud);
    ui->menuDotCloud->setIcon(ui->actionDotCloud->icon());

    m_menus.push_back(ui->menuShading);
    m_menus.push_back(ui->menuShading_2);

    ui->menubar->hide();
    //    for (QMenu & menu : m_menus) {
    //        qDebug() << menu.title();
    //    }
    //    m_menus.push_back(shading);
    //    setShading(WIRE_FRAME);
    setShading(SOLID);

    //    connect(centralWidget(), &QWidget::mouseMoveEvent, this, &MainWindow3dView::mouseMoveEvent);
    //    installEventFilter(this);
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

void MainWindow3dView::load(std::ifstream& file)
{
    Camera::Type type;
    file.read(reinterpret_cast<char*>(&type), sizeof(type));

    switch (type) {
    case Camera::FPS:
        m_camera = new CameraFps(this);
        break;

    case Camera::WORLD:
        m_camera = new CameraWorld;
        break;
    }

    m_camera->load(file);
    //    setShading(WIRE_FRAME);

    bool data[6];
    file.read(reinterpret_cast<char*>(data), sizeof(data));
    //    ui->actionWireFrame->setChecked(data[0]);
    if (data[0]) {
        //        if (!ui->actionWireFrame->isChecked())
        ui->actionWireFrame->trigger();
    }
    if (data[1]) {
        //        if (!ui->actionX_Rays->isChecked())
        ui->actionX_Rays->trigger();
    }
    if (data[2]) {
        ui->actionSkeleton->trigger();
    }
    if (data[3]) {
        ui->actionNormal_2->trigger();
    }
    if (data[4]) {
        ui->actionBoundingBox->trigger();
    }
    if (data[5]) {
        ui->actionDotCloud->trigger();
    }
    //    ui->actionX_Rays->setChecked(data[1]);

    file.read(reinterpret_cast<char*>(&m_shade), sizeof(m_shade));
    setShading(m_shade);
}

void MainWindow3dView::save(std::ofstream& file)
{
    Camera::Type type = m_camera->m_type;
    file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    m_camera->save(file);

    bool wireFrame = ui->actionWireFrame->isChecked();
    bool xRays = ui->actionX_Rays->isChecked();

    bool data[6];
    data[0] = wireFrame;
    data[1] = xRays;
    data[2] = ui->actionSkeleton->isChecked();
    data[3] = ui->actionNormal_2->isChecked();
    data[4] = ui->actionBoundingBox->isChecked();
    data[5] = ui->actionDotCloud->isChecked();
    file.write(reinterpret_cast<const char*>(data), sizeof(data));

    file.write(reinterpret_cast<const char*>(&m_shade), sizeof(m_shade));
    //    setShading(m_shade);
}

void MainWindow3dView::setMode(MainWindow3dView::Mode mode)
{
    switch (mode) {
    case OBJECT:
        ui->menuInteraction_Mode->setIcon(ui->actionObject_Mode->icon());
        ui->menuCurent_Mode->setTitle("Object Mode");
        break;

    case EDIT:
        ui->menuInteraction_Mode->setIcon(ui->actionEdit_Mode->icon());
        ui->menuCurent_Mode->setTitle("Edit Mode");
        break;

    case POSE:
        ui->menuInteraction_Mode->setIcon(ui->actionPose_Mode->icon());
        ui->menuCurent_Mode->setTitle("Pose Mode");
        break;
    }

    m_previousMode = m_mode;
    m_mode = mode;
}

void MainWindow3dView::setShading(Shading shade)
{
    switch (shade) {
        //    case WIRE_FRAME:
        //        ui->menuShading->setIcon(ui->actionWireFrame->icon());
        //        ui->menuShading_2->setTitle("WireFrame");
        //        //        if (m_shader == nullptr)
        //        //            delete  m_shader;
        //        //        m_shader = new Shader("model_loading.vsh", "model_loading.fsh");
        //        break;

    case SOLID:
        ui->menuShading->setIcon(ui->actionSolid->icon());
        ui->menuShading_2->setTitle("Solid");
        break;

    case LOOK_DEV:
        ui->menuShading->setIcon(ui->actionLook_dev->icon());
        ui->menuShading_2->setTitle("LookDev");
        break;

    case RENDERED:
        ui->menuShading->setIcon(ui->actionRendered->icon());
        ui->menuShading_2->setTitle("Rendered");
        break;

    case NORMAL:
        ui->menuShading->setIcon(ui->actionNormal->icon());
        ui->menuShading_2->setTitle("Normal");
        break;

    case DEPTH:
        ui->menuShading->setIcon(ui->actionDepth->icon());
        ui->menuShading_2->setTitle("Depth");
        break;

    case VERTEX_GROUP:
        ui->menuShading->setIcon(ui->actionVertexGroup->icon());
        ui->menuShading_2->setTitle("Vertex_Group");
        break;
    }

    m_shade = shade;
}

void MainWindow3dView::glInitialize()
{
    //    m_shaders[Shading::WIRE_FRAME] = new Shader("shading/wireFrame.vsh", "shading/wireFrame.fsh");
    m_shaders[Shading::SOLID] = new Shader("shading/solid.vsh", "shading/solid.fsh");
    m_shaders[Shading::LOOK_DEV] = new Shader("shading/lookDev.vsh", "shading/lookDev.fsh");
    m_shaders[Shading::RENDERED] = new Shader("shading/rendered.vsh", "shading/rendered.fsh");
    m_shaders[Shading::NORMAL] = new Shader("shading/normal.vsh", "shading/normal.fsh");
    m_shaders[Shading::DEPTH] = new Shader("shading/depth.vsh", "shading/depth.fsh");
    m_shaders[Shading::VERTEX_GROUP] = new Shader("shading/vertexGroup.vsh", "shading/vertexGroup.fsh");
}

void MainWindow3dView::keyPressEvent(QKeyEvent* event)
{
    //                qDebug() << this << ": keyPressEvent" << event;
    m_camera->keyPressEvent(event);

    switch (event->key()) {

    case Qt::Key_Dollar:
        setMode(m_previousMode);
        //        std::swap(m_mode, m_previousMode);
        //        Mode temp = m_mode;
        //        m_mode = m_previousMode;
        break;

    case Qt::Key_Delete:
        //        qDebug() << "delete";
        RayTracer::deleteSelected();
        break;

    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;

    case Qt::Key_Control:
        m_ctrlPressed = true;
        break;

    case Qt::Key_X:
        if (!m_transformActive) {
            ui->actionX_Rays->trigger();
        }
    case Qt::Key_Y:
    case Qt::Key_Z:
        if (m_transformActive) {
            sendTransformToScene();

            m_axisLocal = !m_axisLocal;

            m_axisTransform = true;
            m_axisFollow = static_cast<uint>(event->key() - Qt::Key_X);
        }
        break;

    case Qt::Key_Escape:
        setTransformInactive();
        //        m_transformMatrix = glm::mat4(1.0f);
        //        m_transformActive = false;
        //        setMouseTracking(false);
        //        centralWidget()->setMouseTracking(false);
        //        setCursor(Qt::ArrowCursor);
        break;

        //    case Qt::Key_Enter:
        //        m_transform = glm::mat4(1.0f);
        //        m_transformActive = false;
        //        setMouseTracking(false);
        //        centralWidget()->setMouseTracking(false);
        //        break;
        //        break;
    case Qt::Key_S:
        if (m_shiftPressed) {

            ui->actionSolid->trigger();
        } else {

            m_transform = Transform::SCALE;
            setTransformActive();
        }
        break;

    case Qt::Key_R:
        if (m_shiftPressed) {

            ui->actionRendered->trigger();
        } else {
            m_transform = Transform::ROTATE;
            setTransformActive();
        }
        break;

    case Qt::Key_G:
        //        m_transform = glm::scale(m_transform, glm::vec3(2.0f, 2.0f, 2.0f));
        //        m_transformActive = true;
        //        m_transform = Transform::TRANSLATE;
        //        m_firstTransform = true;
        //        m_memRight = m_camera->right();
        //        m_memUp = m_camera->up();
        //        setMouseTracking(true);
        //        centralWidget()->setMouseTracking(true);
        //        setCursor(Qt::SizeAllCursor);
        m_transform = Transform::TRANSLATE;
        setTransformActive();
        break;

    case Qt::Key_End:
        //        qDebug() << "y";
        m_camera->setFront(glm::vec3(0.0f, 1.0f, 0.0f));
        updateOrthoProjection();
        //        m_ortho = true;
        m_alignAxis = true;
        break;

    case Qt::Key_PageDown:
        //        qDebug() << "x";
        m_camera->setFront(glm::vec3(-1.0f, 0.0f, 0.0f));
        updateOrthoProjection();
        m_alignAxis = true;
        //        m_ortho = true;
        break;

    case Qt::Key_Home:
        //        qDebug() << "z";
        m_camera->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
        updateOrthoProjection();
        m_alignAxis = true;
        //        m_ortho = true;
        break;

    case Qt::Key_Clear:
        //        qDebug() << "change projection";
        if (m_ortho) {
            //            m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
            //            updateProjectionMatrix();
            updatePersepectiveProjection();
        } else {
            updateOrthoProjection();
        }
        //        m_ortho = !m_ortho;
        //        update();
        break;

    case Qt::Key_L:
        //        on_actionLook_dev_triggered();
        ui->actionLook_dev->trigger();
        break;

    case Qt::Key_V:
        ui->actionVertexGroup->trigger();
        break;

    case Qt::Key_N:
        if (m_shiftPressed) {
            ui->actionNormal_2->trigger();
        } else {

            ui->actionNormal->trigger();
        }
        break;

    case Qt::Key_D:
        if (m_shiftPressed) {
            ui->actionDotCloud->trigger();
        } else {
            ui->actionDepth->trigger();
        }
        break;

    case Qt::Key_B:
        if (m_shiftPressed) {
            ui->actionBoundingBox->trigger();
        } else {
            ui->actionSkeleton->trigger();
        }
        break;

    case Qt::Key_F:
        if (m_shiftPressed) {

            if (m_camera->m_type == Camera::WORLD) {
                CameraWorld* camera = static_cast<CameraWorld*>(m_camera);
                RayTracer::setSelectFocus(*camera);
            }

        } else {

            glm::vec3 pos = m_camera->position();
            float fov = m_camera->fov();
            if (m_camera->m_type == Camera::FPS) {
                CameraFps* camera = static_cast<CameraFps*>(m_camera);

                glm::vec3 front = glm::normalize(camera->front());
                //            Q_ASSERT(glm::length(front) == 1.0f);
                glm::vec3 target = camera->position() + 200.0f * front;
                //            glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

                delete m_camera;
                m_camera = new CameraWorld(fov, pos, target);
                //            m_camera = new CameraWorld(static_cast<CameraFps*>(m_camera));
            } else {
                CameraWorld* camera = static_cast<CameraWorld*>(m_camera);
                //            glm::vec3 front = glm::normalize(camera->target() - pos);
                glm::vec3 front = glm::normalize(camera->target() - pos);

                //    m_yaw = glm::degrees(cosf(front.x /(sqrtf(front.x * front.x + front.z * front.z))));
                //            float yaw = glm::degrees(atanf(front.y / front.x));
                float yaw = glm::degrees(atan2f(front.y, front.x));
                float pitch = glm::degrees(asinf(front.z));

                delete m_camera;
                m_camera = new CameraFps(fov, pos, yaw, pitch, this);

                static_cast<CameraFps*>(m_camera)->startFpsView();

                //            m_camera = new CameraFps(static_cast<CameraWorld*>(m_camera), this);
            }
            break;
        }
    }
}

void MainWindow3dView::keyReleaseEvent(QKeyEvent* event)
{
    m_camera->keyReleaseEvent(event);

    switch (event->key()) {
    case Qt::Key_Shift:
        m_shiftPressed = false;
        break;

    case Qt::Key_Control:
        m_ctrlPressed = false;
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
    switch (event->button()) {

    case Qt::LeftButton:
        //        front = glm::rotate()
        //        emit launchRayTracing(source, front);
        //        RayTracer::launch({source, front});
        //        if (m_ctrlPressed) {
        //            RayTracer::unselectRay(clickRay(event));
        //        } else {

        if (m_transformActive) {
//            RayTracer::setSelectRootTransform(m_transformMatrix);
            sendTransformToScene();
            //            m_transformMatrix = glm::mat4(1.0f);
            //            m_transformActive = false;
            //			setCursor(Qt::ArrowCursor);
            setTransformInactive();
        } else {
            RayTracer::selectRay(clickRay(event), m_shiftPressed);
        }

        break;
        //        }
    case Qt::MidButton:
        if (!m_shiftPressed) {
            if (m_alignAxis) {
                m_alignAxis = false;
                updatePersepectiveProjection();
            }
        }
        break;
    }
    m_camera->mousePressEvent(event);

    //    qDebug() << "[3dView]" << QWidget::mapToGlobal(pos());
    //    setMouseTracking(true);
    //    setFocus();
    event->ignore(); // splitter node
}

void MainWindow3dView::mouseReleaseEvent(QMouseEvent* event)
{
    //    setMouseTracking(true);
    m_camera->mouseReleaseEvent(event);
}

void MainWindow3dView::mouseMoveEvent(QMouseEvent* event)
{
    //    setMouseTracking(true);
    //    centralWidget()->setMouseTracking(true);
    m_camera->mouseMoveEvent(event);

    if (m_transformActive) {
        if (m_firstTransform) {
            m_firstTransform = false;

            m_memEventPos = event->pos();
        } else {
            QPoint diff = m_memEventPos - event->pos();
            float dx = diff.x();
            float dy = diff.y();
            m_transformMatrix = glm::mat4(1.0f);

            switch (m_transform) {
            case Transform::TRANSLATE:
                if (m_axisTransform) {
                    switch (m_axisFollow) {
                    case 0:
//                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
//                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                        m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                        break;
                    case 1:
//                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                        m_worldTransform = glm::translate(m_worldTransform, glm::vec3(0.0f, 1.0f, 0.0f) * -dx);
                        break;
                    case 2:
//                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                        m_worldTransform = glm::translate(m_worldTransform, glm::vec3(0.0f, 0.0f, 1.0f) * -dx);
                        break;
                    }

                } else {

                    m_transformMatrix = glm::translate(m_transformMatrix, m_memRight * dx);
                    m_transformMatrix = glm::translate(m_transformMatrix, m_memUp * dy);
                }
                break;

            case Transform::ROTATE:
                //                m_transformMatrix = glm::rotate(m_transformMatrix, 0.01f * dx, m_memUp);
                //                m_transformMatrix = glm::rotate(m_transformMatrix, dy* 0.01f, m_memRight);
                m_transformMatrix = glm::rotate(m_transformMatrix, -dx * 0.01f, m_memFront);
                break;

            case Transform::SCALE:
                m_transformMatrix = glm::scale(m_transformMatrix, 1.0f + dx * 0.01f * m_memRight);
                m_transformMatrix = glm::scale(m_transformMatrix, 1.0f + dy * 0.01f * m_memUp);
                break;
            }
        }
    }
    //    event->ignore();
}

void MainWindow3dView::wheelEvent(QWheelEvent* event)
{
    m_camera->wheelEvent(event);

    if (m_ortho)
        updateOrthoProjection();
    //    float dy = event->delta();

    //    if (m_ortho) {
    //        orthoSize += -dy * 0.01;
    //        m_projectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, l_near, l_far);
    //    }
}

//bool MainWindow3dView::eventFilter(QObject* obj, QEvent* event)
//{
//    if (event->type() == QEvent::MouseMove) {
//        qDebug("eventFilter:  hello");
////        return QWidget::eventFilter(obj, event);
//    } else {
////        return QWidget::eventFilter(obj, event);
//    }
//    return true;
//}

void MainWindow3dView::focusInEvent(QFocusEvent* event)
{
    //    qDebug() << "MainWindow3dView::focusInEvnt";
    //    centralWidget()->setFocus();
    //    centralWidget()->setFocus();
    m_camera->focusInEvent(event);

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

void MainWindow3dView::resizeEvent(QResizeEvent* event)
{
    m_camera->resizeEvent(event);

    m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
}

void MainWindow3dView::setFocusPolicy(Qt::FocusPolicy policy)
{
    QWidget::setFocusPolicy(policy);
}

QWidget* MainWindow3dView::widget()
{
    return this;
}

void MainWindow3dView::updateOrthoProjection()
{
    float targetDist;
    if (m_camera->m_type == Camera::WORLD) {
        glm::vec3 target = static_cast<CameraWorld*>(m_camera)->target();
        targetDist = glm::length(camera()->position() - target);
    } else {
        targetDist = 200.0f;
    }
    float fov = glm::radians(m_camera->fov());
    float right = targetDist * tanf(fov / 2);
    float ratio = (float)height() / width();
    float up = right * ratio;

    m_projectionMatrix = glm::ortho(-right, right, -up, up, l_near, l_far);
    m_ortho = true;
}

void MainWindow3dView::updatePersepectiveProjection()
{
    m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
    m_ortho = false;
}

Ray MainWindow3dView::clickRay(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();
    //        emit launchRayTracing(x, y);

    glm::vec3 source = m_camera->position();
    glm::vec3 front = m_camera->front();
    glm::vec3 right = m_camera->right();
    glm::vec3 up = m_camera->up();
    float fov = m_camera->fov();
    //        float ratio = static_cast<float>(height()) / width();
    // question : ration = w / h or h / w ? horizontal fov or vertical ?
    float ratio = static_cast<float>(width()) / height();

    //        int dx = x -width() /2;
    //        int dy = y -height() / 2;
    float dx = fov * ratio * (static_cast<float>(x) / width() - 0.5f);
    float dy = fov * (static_cast<float>(y) / height() - 0.5f);

    //        qDebug() << "left click" << dx << dy;

    glm::mat4 rotate(1.0f);
    //        rotate = glm::rotate(rotate, dx, glm::vec3(0.0f, 0.0f, 1.0f));
    //        rotate = glm::rotate(rotate, dy, glm::vec3(1.0f, 0.0f, 0.0f));

    rotate = glm::rotate(rotate, glm::radians(-dx), up);
    rotate = glm::rotate(rotate, glm::radians(dy), right);

    front = glm::normalize(rotate * glm::vec4(front, 1.0f));

    return { source, front };
}

void MainWindow3dView::updateProjectionMatrix()
{
    //    m_projectionMatrix = fov;
    //    m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
    //    m_ortho = false;
    if (m_ortho) {
        updateOrthoProjection();
    } else {
        updatePersepectiveProjection();
    }
}

void MainWindow3dView::setTransformActive()
{
    if (m_transformActive) {
        //        RayTracer::setSelectRootTransform(m_transformMatrix);
        sendTransformToScene();
    }

    m_transformActive = true;
    m_firstTransform = true;
    m_axisLocal = true;
    m_memRight = m_camera->right();
    m_memUp = m_camera->up();
    m_memFront = m_camera->front();
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    setCursor(Qt::SizeAllCursor);
}

void MainWindow3dView::setTransformInactive()
{
    m_transformActive = false;
    m_transformMatrix = glm::mat4(1.0f);
    setMouseTracking(false);
    centralWidget()->setMouseTracking(false);
    setCursor(Qt::ArrowCursor);

    m_axisTransform = false;
    m_axisLocal = false;
    //    case Qt::Key_Enter:
    //        m_transform = glm::mat4(1.0f);
    //        m_transformActive = false;
    //        setMouseTracking(false);
    //        centralWidget()->setMouseTracking(false);
    //        break;
    //        break;

    //    case Qt::Key_G:
    //        m_transform = glm::scale(m_transform, glm::vec3(2.0f, 2.0f, 2.0f));
}

void MainWindow3dView::sendTransformToScene()
{
    RayTracer::setSelectRootTransform(m_worldTransform * m_transformMatrix);
//    RayTracer::setSelectRootTransform(m_worldTransform * m_transformMatrix);
    m_transformMatrix = glm::mat4(1.0f);
    m_worldTransform = glm::mat4(1.0f);
}

bool MainWindow3dView::xRays() const
{
    return ui->actionX_Rays->isChecked();
}

bool MainWindow3dView::skeleton() const
{
    return ui->actionSkeleton->isChecked();
}

bool MainWindow3dView::normal() const
{
    return ui->actionNormal_2->isChecked();
}

bool MainWindow3dView::boundingBox() const
{
    return ui->actionBoundingBox->isChecked();
}

bool MainWindow3dView::dotCloud() const
{
    return ui->actionDotCloud->isChecked();
}

bool MainWindow3dView::vertexGroupShader() const
{
    return m_shade == Shading::VERTEX_GROUP;
}

bool MainWindow3dView::solid() const
{
    return m_shade == Shading::SOLID;
}

void MainWindow3dView::setCursorToCenter()
{
    QPoint glob = mapToGlobal(QPoint(width() / 2, height() / 2));
    QCursor::setPos(glob);
}

const Shader& MainWindow3dView::shader() const
{
    //    return *m_shader;
    const Shader& shader = *m_shaders[m_shade];

    shader.use();
    shader.setMat4("view", viewMatrix());
    shader.setMat4("projection", projectionMatrix());

    switch (m_shade) {
        //    case WIRE_FRAME:
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //        break;

    case SOLID:
        shader.setVec3("viewPos", m_camera->position());
        shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
        //    m_shader->setVec3("material.diffuse", 0.3f, 0.3f, 0.3f);
        shader.setVec3("material.specular", 0.5f, 0.5f, 1.0f);
        shader.setFloat("material.shininess", 1.0f);
        break;

    case LOOK_DEV:
        break;

    case RENDERED:
        break;

    case NORMAL:
        break;

    case DEPTH:
        break;

    case VERTEX_GROUP:
        break;
    }

    if (ui->actionWireFrame->isChecked()) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //        if (ui->actionX_Rays->isChecked()) {
        //            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //        } else {
        //            glPolygonMode(GL_FRONT, GL_LINE);
        //        }

    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //            glPolygonMode(GL_BACK, GL_LINE);
        //        if (ui->actionX_Rays->isChecked()) {
        //            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //        } else {
        //            glPolygonMode(GL_FRONT, GL_FILL);
        //        }
    }

    if (ui->actionX_Rays->isChecked()) {
        //        glBlendFunc(GL_ONE, GL_ONE);
        glDisable(GL_CULL_FACE);
    } else {
        //        glBlendFunc(GL_ONE, GL_ZERO);
        glEnable(GL_CULL_FACE);
    }

    return *m_shaders[m_shade];
}

//std::list<QMenu> MainWindow3dView::menus() const
//{
//    return m_menus;
//}

const Camera* MainWindow3dView::camera() const
{
    Q_ASSERT(m_camera != nullptr);
    return m_camera;
}

//void MainWindow3dView::setViews(std::list<const MainWindow3dView *> *views)
//{
//    m_views = views;
//}

glm::mat4 MainWindow3dView::viewMatrix() const
{
    //    return m_viewMatrix;
    Q_ASSERT(m_camera != nullptr);
    return m_camera->viewMatrix();
}

glm::mat4 MainWindow3dView::projectionViewMatrix() const
{
    return m_projectionMatrix * m_camera->viewMatrix();
}

void MainWindow3dView::setViews(std::list<const MainWindow3dView*>* views)
{
    m_views = views;
}

glm::mat4 MainWindow3dView::projectionMatrix() const
{
    return m_projectionMatrix;
}

glm::mat4 MainWindow3dView::projectionMatrixZoom() const
{
    return glm::perspective(glm::radians(m_camera->fov() - 1), (float)width() / height(), l_near, l_far);
}

//void MainWindow3dView::on_actionWireFrame_triggered()
//{
//    setShading(WIRE_FRAME);
//}

void MainWindow3dView::on_actionSolid_triggered()
{
    setShading(SOLID);
}

void MainWindow3dView::on_actionLook_dev_triggered()
{
    setShading(LOOK_DEV);
}

void MainWindow3dView::on_actionRendered_triggered()
{
    setShading(RENDERED);
}

void MainWindow3dView::on_actionNormal_triggered()
{
    setShading(NORMAL);
}

void MainWindow3dView::on_actionDepth_triggered()
{
    setShading(DEPTH);
}

void MainWindow3dView::on_actionVertexGroup_triggered()
{
    setShading(VERTEX_GROUP);
}

void MainWindow3dView::on_actionWireFrame_triggered()
{
    //    QIcon icon = ui->actionWireFrame->icon();
    //    QPixmap pixmap(icon);
    //    ui->actionWireFrame->toggle();

    if (ui->actionWireFrame->isChecked()) {
        QPixmap pixmap(":/icons/wireframe.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        ui->menuWireFrame->setIcon(icon);

    } else {

        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionX_Rays_triggered()
{
    if (ui->actionX_Rays->isChecked()) {
        QPixmap pixmap(":/icons/xRays.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuX_Ray->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuX_Ray->setIcon(ui->actionX_Rays->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionSkeleton_triggered()
{
    if (ui->actionSkeleton->isChecked()) {
        QPixmap pixmap(":/icons/bones.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuSkeleton->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuSkeleton->setIcon(ui->actionSkeleton->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionNormal_2_triggered()
{
    if (ui->actionNormal_2->isChecked()) {
        QPixmap pixmap(":/icons/normal.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuNormal->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuNormal->setIcon(ui->actionNormal_2->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionBoundingBox_triggered()
{
    if (ui->actionBoundingBox->isChecked()) {
        QPixmap pixmap(":/icons/boundingBox.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuBoundingBox->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuBoundingBox->setIcon(ui->actionBoundingBox->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionDotCloud_triggered()
{
    if (ui->actionDotCloud->isChecked()) {
        QPixmap pixmap(":/icons/vertex.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuDotCloud->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuDotCloud->setIcon(ui->actionDotCloud->icon());
    }
    //    ui->actionWireFrame->ic
}

void MainWindow3dView::on_actionObject_Mode_triggered()
{
    setMode(OBJECT);
}

void MainWindow3dView::on_actionEdit_Mode_triggered()
{
    setMode(EDIT);
}

void MainWindow3dView::on_actionPose_Mode_triggered()
{
    setMode(POSE);
}
