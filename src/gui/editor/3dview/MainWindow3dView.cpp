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
#include <engine/scene/camera/CameraFps.h>
#include <engine/scene/camera/CameraWorld.h>

//#include <opengl/OpenglContext.h>
//#include <opengl/grid.h>
#include <engine/scene/Scene.h>
#include <gui/QOpenGLWidget_Editor.h>
#include <opengl/rayTracer/RayTracer.h>
//#include <engine/scene/camera/CameraStrategy.h>
#include <engine/scene/model/paramModel/curve/BSplineCurve.h>
#include <session/Session.h>

std::list<const MainWindow3dView*>* MainWindow3dView::m_views;
//Shader MainWindow3dView::m_shaders;
//Shader* MainWindow3dView::m_shaders[Shading::size];

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
    , m_localTransform(&Scene::m_scene->m_localTransform)
    , m_worldTransform(&Scene::m_scene->m_worldTransform)
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
    Q_ASSERT(Scene::m_scene != nullptr);
    //    Scene::m_scene->m_cameras.emplace_back(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0));
    // question : use emplace back, args ... to place directly in vector
    //    Scene::m_scene->addCamera(50.0f, glm::vec3(200, -200, 200), glm::vec3(0.0, 0.0, 0.0));
    //    m_camera = Scene::m_scene->m_cameras.back();

    //        m_camera = new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0));

    //    Scene::m_cameras.push_back(m_camera);
    //    Scene::m_scene->m_allObjects.push_back(m_camera);
    //        m_camera = new CameraFps(glm::vec3(200.0f, -200.0f, 200.0f), 135.0f, -45.0f, this);

    ui->setupUi(this);
    //    g_openglContext.
    //    fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    fun = g_openglContext.m_fun;
    //    fun = g_fun;
    //    setFocusPolicy(Qt::ClickFocus);

    //    setAutoFillBackground(false);

    //    m_projectionMatrix = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
    //    Scene::m_cameras.push_back(new CameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0)));
    //    QOpenGLWidget_Editor::m_editor->addCameraWorld(50.0f, glm::vec3(200, -200, 200), glm::vec3(0, 0, 0));

    m_iCamera = m_views->size();

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
    m_menus.push_back(ui->menuCameraId);
    //    ui->menuCameraId->setTitle("Camera Init");
    updateCameraId();

    m_menus.push_back(ui->menuInteraction_Mode);
    //    ui->menuInteraction_Mode->setIcon(ui->actionObject_Mode->icon());
    ui->menuInteraction_Mode->setStyleSheet("background-color: none");
    m_menus.push_back(ui->menuCurent_Mode);

    m_mode = EDIT;
    setMode(OBJECT);

    // ----------------------------------------------
    ui->menuShading->setStyleSheet("background-color: none");
    m_menus.push_back(ui->menuShading);
    m_menus.push_back(ui->menuShading_2);

    ui->menuAdd->setStyleSheet("background-color: none");
    m_menus.push_back(ui->menuAdd);

    // -----------------------------------------------
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

    m_menus.push_back(ui->menuIntersectRay);
    ui->menuIntersectRay->setIcon(ui->actionIntersectRay->icon());

    // -------------------------------------------------
    ui->menubar->hide();
    //    for (QMenu & menu : m_menus) {
    //        qDebug() << menu.title();
    //    }
    //    m_menus.push_back(shading);
    //    setShading(WIRE_FRAME);
    setShading(Shader::Type::SOLID);

    //    connect(centralWidget(), &QWidget::mouseMoveEvent, this, &MainWindow3dView::mouseMoveEvent);
    //    installEventFilter(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow3dView::onUpdateCameraFps);
    m_timerAutoUpdateCurve = new QTimer(this);
    connect(m_timerAutoUpdateCurve, &QTimer::timeout, this, &MainWindow3dView::onUpdateCurve);
    m_timerAutoUpdateSurface = new QTimer(this);
    connect(m_timerAutoUpdateSurface, &QTimer::timeout, this, &MainWindow3dView::onUpdateSurface);
}

MainWindow3dView::~MainWindow3dView()
{
    //    makeCurrent();
    //    qDebug() << "[3dView]" << this << "deleted";

    //    g_env.m_views.remove(this);
    //    qDebug() << "[3dView] " << this << "remove in views " << g_env.m_views;
    Q_ASSERT(m_views);
    m_views->remove(this);

    //    QOpenGLWidget_Editor::m_editor->deleteCamera(m_iCamera);
    //    delete m_grid;
    //    delete m_shader;
    //    doneCurrent();
}

void MainWindow3dView::load(std::ifstream& file)
{
    //    Camera::Type type;
    //    file.read(reinterpret_cast<char*>(&type), sizeof(type));
    //    if (m_camera != nullptr) {
    ////        auto& list = Scene::m_scene->m_allObjects;
    ////        Q_ASSERT(std::find(list.begin(), list.end(), m_camera) != list.end());
    ////        uint size = Scene::m_scene->m_allObjects.size();
    ////        list.remove(m_camera);
    ////        Q_ASSERT(Scene::m_scene->m_allObjects.size() == size - 1);
    //        delete m_camera;
    //    }

    //    switch (type) {
    //    case Camera::FPS:
    //        m_camera = new CameraFps(this);
    //        break;

    //    case Camera::WORLD:
    //        m_camera = new CameraWorld;
    //        break;
    //    }

    //    m_camera->load(file);

    //    Scene::m_cameras.push_back(m_camera);
    //    Q_ASSERT(Scene::m_scene != nullptr);
    //    Scene::m_scene->m_allObjects.push_back(m_camera);
    //    setShading(WIRE_FRAME);
    Session::load(m_iCamera, file);
    updateCameraId();

    Camera* m_camera = Scene::m_cameras[m_iCamera];
    if (m_camera->m_cameraStrategy->m_type == CameraStrategy::FPS) {
        static_cast<CameraFps*>(m_camera->m_cameraStrategy)->m_view = this;
    }

    bool data[7];
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
    if (data[6]) {
        ui->actionIntersectRay->trigger();
    }
    //    ui->actionX_Rays->setChecked(data[1]);

    file.read(reinterpret_cast<char*>(&m_shade), sizeof(m_shade));
    setShading(m_shade);
}

void MainWindow3dView::save(std::ofstream& file) const
{
    //    Camera::Type type = m_camera->m_type;
    //    file.write(reinterpret_cast<const char*>(&type), sizeof(type));
    //    m_camera->save(file);
    Session::save(m_iCamera, file);

    bool wireFrame = ui->actionWireFrame->isChecked();
    bool xRays = ui->actionX_Rays->isChecked();

    bool data[7];
    data[0] = wireFrame;
    data[1] = xRays;
    data[2] = ui->actionSkeleton->isChecked();
    data[3] = ui->actionNormal_2->isChecked();
    data[4] = ui->actionBoundingBox->isChecked();
    data[5] = ui->actionDotCloud->isChecked();
    data[6] = ui->actionIntersectRay->isChecked();
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
        m_localTransform = &Scene::m_scene->m_localTransform;
        m_worldTransform = &Scene::m_scene->m_worldTransform;
        break;

    case EDIT:
        ui->menuInteraction_Mode->setIcon(ui->actionEdit_Mode->icon());
        ui->menuCurent_Mode->setTitle("Edit Mode");
        m_localTransform = &Scene::m_scene->m_localVertexTransform;
        m_worldTransform = &Scene::m_scene->m_worldVertexTransform;
        break;

    case POSE:
        ui->menuInteraction_Mode->setIcon(ui->actionPose_Mode->icon());
        ui->menuCurent_Mode->setTitle("Pose Mode");
        break;
    }

    m_previousMode = m_mode;
    m_mode = mode;
}

void MainWindow3dView::setShading(Shader::Type shade)
{
    switch (shade) {
        //    case WIRE_FRAME:
        //        ui->menuShading->setIcon(ui->actionWireFrame->icon());
        //        ui->menuShading_2->setTitle("WireFrame");
        //        //        if (m_shader == nullptr)
        //        //            delete  m_shader;
        //        //        m_shader = new Shader("model_loading.vsh", "model_loading.fsh");
        //        break;

    case Shader::Type::SOLID:
        ui->menuShading->setIcon(ui->actionSolid->icon());
        ui->menuShading_2->setTitle("Solid");
        break;

    case Shader::Type::LOOK_DEV:
        ui->menuShading->setIcon(ui->actionLook_dev->icon());
        ui->menuShading_2->setTitle("LookDev");
        break;

    case Shader::Type::RENDERED:
        ui->menuShading->setIcon(ui->actionRendered->icon());
        ui->menuShading_2->setTitle("Rendered");
        break;

    case Shader::Type::NORMAL:
        ui->menuShading->setIcon(ui->actionNormal->icon());
        ui->menuShading_2->setTitle("Normal");
        break;

    case Shader::Type::DEPTH:
        ui->menuShading->setIcon(ui->actionDepth->icon());
        ui->menuShading_2->setTitle("Depth");
        break;

    case Shader::Type::VERTEX_GROUP:
        ui->menuShading->setIcon(ui->actionVertexGroup->icon());
        ui->menuShading_2->setTitle("Vertex_Group");
        break;
    }

    m_shade = shade;
}

//void MainWindow3dView::glInitialize()
//{
//    //    m_shaders[Shading::WIRE_FRAME] = new Shader("shading/wireFrame.vsh", "shading/wireFrame.fsh");
//    m_shaders[Shading::SOLID] = new Shader("shading/solid.vsh", "shading/solid.fsh");
//    m_shaders[Shading::LOOK_DEV] = new Shader("shading/lookDev.vsh", "shading/lookDev.fsh");
//    m_shaders[Shading::RENDERED] = new Shader("shading/rendered.vsh", "shading/rendered.fsh");
//    m_shaders[Shading::NORMAL] = new Shader("shading/normal.vsh", "shading/normal.fsh");
//    m_shaders[Shading::DEPTH] = new Shader("shading/depth.vsh", "shading/depth.fsh");
//    m_shaders[Shading::VERTEX_GROUP] = new Shader("shading/vertexGroup.vsh", "shading/vertexGroup.fsh");
//}

void MainWindow3dView::keyPressEvent(QKeyEvent* event)
{
    //                qDebug() << this << ": keyPressEvent" << event;
    uint size = Scene::m_cameras.size();

    switch (event->key()) {

    case Qt::Key_F1:
        Mesh::enableSwitchTexture(Texture::DIFFUSE);
        break;
    case Qt::Key_F2:
        Mesh::enableSwitchTexture(Texture::SPECULAR);
        break;
    case Qt::Key_F3:
        Mesh::enableSwitchTexture(Texture::NORMAL);
        break;
    case Qt::Key_F4:
        Mesh::enableSwitchTexture(Texture::HEIGHT);
        break;

    case Qt::Key_F5:
        Mesh::enableSwitchTexture(Texture::OPACITY);
        break;

    case Qt::Key_F6:
        Scene::m_scene->m_computeShadow = ! Scene::m_scene->m_computeShadow;
        break;

    case Qt::Key_C:
        //        if (size == 0) {
        //            ui->menuCameraId->setTitle("No Camera");
        //        } else {

        if (size > 1) {
            m_iCamera = (m_iCamera + 1) % size;
            updateCameraId();
        }
        //            ui->menuCameraId->setTitle(QString("Camera ") + QString::number(m_iCamera));
        //    }
        break;

    case Qt::Key_Dollar:
        setMode(m_previousMode);
        //        std::swap(m_mode, m_previousMode);
        //        Mode temp = m_mode;
        //        m_mode = m_previousMode;
        break;

    case Qt::Key_Shift:
        m_shiftPressed = true;
        break;

    case Qt::Key_Control:
        m_ctrlPressed = true;
        break;

    case Qt::Key_X:
        if (m_shiftPressed) {
            if (event->key() == Qt::Key_X) {
                ui->actionX_Rays->trigger();
                break;
            }
        }
        break;
    case Qt::Key_Z:
        if (m_shiftPressed) {
            if (event->key() == Qt::Key_Z) {

                //            ui->actionX_Rays->trigger();
                ui->actionWireFrame->trigger();
                break;
            }
        }
        break;

    case Qt::Key_S:
        if (m_shiftPressed) {

            ui->actionSolid->trigger();
        }
        break;

    case Qt::Key_R:
        if (m_shiftPressed) {
            ui->actionRendered->trigger();
        }
        break;
    case Qt::Key_L:
        //        on_actionLook_dev_triggered();
        if (m_shiftPressed) {
            ui->actionLook_dev->trigger();
        }
        break;

    case Qt::Key_V:
        if (m_shiftPressed) {
            ui->actionVertexGroup->trigger();
        }
        break;

    case Qt::Key_I:
        ui->actionIntersectRay->trigger();
        break;

    case Qt::Key_N:
        if (m_shiftPressed) {
            ui->actionNormal->trigger();
        } else {
            ui->actionNormal_2->trigger();
        }
        break;

    case Qt::Key_D:
        if (m_shiftPressed) {
            ui->actionDepth->trigger();
        } else {
            ui->actionDotCloud->trigger();
        }
        break;

    case Qt::Key_B:
        if (m_shiftPressed) {
            ui->actionBoundingBox->trigger();
        } else {
            ui->actionSkeleton->trigger();
        }
        break;
    } // end switch

    // -----------------------------------------------------------------------------
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->keyPressEvent(event);

//        CameraStrategy::Type cameraType = m_camera->m_cameraStrategy->m_type;
        bool fpsCamera = m_camera->m_cameraStrategy->m_type == CameraStrategy::FPS;

        switch (event->key()) {

//        case Qt::Key_PageUp:
//            on_actionPoint_Light_triggered();
//            break;

        case Qt::Key_Delete:
            //        qDebug() << "delete";
            RayTracer::deleteSelected();
            break;

        case Qt::Key_Space:
            if (m_transformActive) {
                sendTransformToScene();
                m_firstTransform = true;
            }
            else {

                if (m_camera->m_cameraStrategy->m_type == CameraStrategy::WORLD) {
                    CameraWorld* camera = static_cast<CameraWorld*>(m_camera->m_cameraStrategy);
                    RayTracer::setSelectFocus(*camera);
                }
            }
            break;

        case Qt::Key_0:
            if (m_transformActive) {
                RayTracer::setSelectToOriginTransform();
            } else {
                //                m_camera->setDefault();
//                m_camera->setTarget(glm::vec3(0.0f));
            m_camera->setDefault();
            }

            break;

//        case Qt::Key_F5:
            break;

        case Qt::Key_X:
        case Qt::Key_Z:
            //            if (m_shiftPressed) {
            //                if (event->key() == Qt::Key_X) {
            //                    ui->actionX_Rays->trigger();
            //                    break;
            //                }
            //                if (event->key() == Qt::Key_Z) {

            //                    //            ui->actionX_Rays->trigger();
            //                    ui->actionWireFrame->trigger();
            //                    break;
            //                }
            //            }
        case Qt::Key_Y:
            //        else {

            if (m_transformActive) {
                //            sendTransformToScene();
                *m_localTransform = glm::mat4(1.0f);
                //            Scene::m_scene->m_transformMatrix = glm::mat4(1.0f);
                *m_worldTransform = glm::mat4(1.0f);
                //            Scene::m_scene->m_worldTransform = glm::mat4(1.0f);

                m_axisTransform = true;
                //            switch (m_transform) {
                //            case Transform::TRANSLATE:
                uint mem = m_axisFollow;
                m_axisFollow = static_cast<uint>(event->key() - Qt::Key_X);
                if (mem != m_axisFollow) {
                    //                m_axisLocal = !(m_transform == Transform::TRANSLATE);
                    switch (m_transform) {
                    case TRANSLATE:
                        m_axisLocal = false;
                        break;

                    case ROTATE:
                    case SCALE:
                        m_axisLocal = true;
                        break;
                    }
                } else {
                    m_axisLocal = !m_axisLocal;
                }

                //                break;

                //            case Transform::ROTATE:
                //            m_axisFollow = static_cast<uint>(event->key() - Qt::Key_X);
                //                break;

                //            case Transform::SCALE:
                //            m_axisFollow = static_cast<uint>(event->key() - Qt::Key_X);
                //                break;
                //            }
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
            //            if (m_shiftPressed) {

            //                ui->actionSolid->trigger();
            //            } else {
            if (!m_shiftPressed) {

                m_transform = Transform::SCALE;
                //            m_axisLocal = true;
                setTransformActive();
            }
            break;

        case Qt::Key_R:
            //            if (m_shiftPressed) {

            //                ui->actionRendered->trigger();
            //            } else {
            if (!m_shiftPressed) {
                m_transform = Transform::ROTATE;
                //            m_axisLocal = true;
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
            //        m_axisLocal = false;
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
            if (! fpsCamera) {
            m_camera->setFront(glm::vec3(-1.0f, 0.0f, 0.0f));
            updateOrthoProjection();
            m_alignAxis = true;
            }
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

        case Qt::Key_F:
            if (!m_shiftPressed) {
                glm::vec3 position = m_camera->position();
                glm::vec3 target = m_camera->target();
                //                m_camera->switchStrategy();
                switch (m_camera->m_cameraStrategy->m_type) {
                case CameraStrategy::FPS:
                    //        if (m_cameraStrategy->m_type == CameraStrategy::FPS) {
                    //                CameraFps* camera = static_cast<CameraFps*>(m_camera);

                    //                glm::vec3 front = glm::normalize(camera->front());
                    //            Q_ASSERT(glm::length(front) == 1.0f);

                    //                                glm::vec3 target = camera->position() + 200.0f * front;
                    //            glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

                    //                    Scene::m_scene->m_objects.remove(m_camera);
                    //        Scene::m_scene->removeCamera(m_iCamera);
                    //                    delete m_camera;
                    //                m_camera = new CameraWorld(fov, pos, camera->m_target);
                    delete m_camera->m_cameraStrategy;
                    //                    m_camera->m_cameraStrategy = new CameraWorld(position, target, m_camera->transform());
                    m_camera->m_cameraStrategy = new CameraWorld(position, target, *m_camera->getModel());
                    //        Scene::m_scene->m_objects.push_back(m_camera);
                    //            m_camera = new CameraWorld(static_cast<CameraFps*>(m_camera));
                    break;
                    //        } else {

                case CameraStrategy::WORLD:
                    //        CameraWorld* camera = static_cast<CameraWorld*>(m_camera);
                    //            glm::vec3 front = glm::normalize(camera->target() - pos);
                    //        glm::vec3 front = glm::normalize(camera->target() - pos);
                    //                    glm::vec3 front_ = front();
                    glm::vec3 front = m_camera->front();

                    //    m_yaw = glm::degrees(cosf(front.x /(sqrtf(front.x * front.x + front.z * front.z))));
                    //            float yaw = glm::degrees(atanf(front.y / front.x));
                    float yaw = glm::degrees(atan2f(front.y, front.x));
                    float pitch = glm::degrees(asinf(front.z));

                    //                    Scene::m_scene->m_objects.remove(m_camera);
                    //        Scene::m_scene->removeCamera(m_iCamera);
                    //                    delete m_camera;
                    delete m_camera->m_cameraStrategy;
                    //                    m_camera->m_cameraStrategy = new CameraFps(position, yaw, pitch, this, m_camera->transform(), m_camera->m_fov);
                    m_camera->m_cameraStrategy = new CameraFps(position, yaw, pitch, this, *m_camera->getModel(), m_camera->m_fov);
                    //        Scene::m_scene->m_objects.push_back(m_camera);

                    static_cast<CameraFps*>(m_camera->m_cameraStrategy)->startFpsView();

                    //            m_camera = new CameraFps(static_cast<CameraWorld*>(m_camera), this);
                    break;
                }

//            } else {
//                if (m_camera->m_cameraStrategy->m_type == CameraStrategy::WORLD) {
//                    CameraWorld* camera = static_cast<CameraWorld*>(m_camera->m_cameraStrategy);
//                    RayTracer::setSelectFocus(*camera);
//                }
            }
            break;
        }

    } // end if camera
}

void MainWindow3dView::keyReleaseEvent(QKeyEvent* event)
{
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->keyReleaseEvent(event);
    }

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
    //    qDebug() << "nb cameras " << Scene::m_cameras.size();
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        Q_ASSERT(m_camera != nullptr);
        //        qDebug() << "camera: " << m_camera;
        m_camera->m_cameraStrategy->mousePressEvent(event);

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
                if (m_mode == Mode::EDIT) {
                    //                    m_paramModelSelected->updateSelectedVertexPosition(*m_localTransform, *m_worldTransform);
                    if (Scene::m_scene->m_selectObject != nullptr) {
                        if (Scene::m_scene->m_selectObject->modelType() == Model::PARAM_CURVE) {
                            //                    m_paramModelSelected = static_cast<ParamModel*>(Scene::m_scene->m_selectObject->m_model);
                            //                    m_splineCurve = static_cast<BSplineCurve*>(Scene::m_scene->m_selectObject->m_model);
                            m_splineCurve->updateSelectedVertexPosition(*m_localTransform, *m_worldTransform);
                            //                    m_splineCurve = Scene::m_scene->m_selectObject->m_model;
                            m_timerAutoUpdateCurve->stop();
                            //                    m_timerAutoUpdateCurve->start(50);
                        } else if (Scene::m_scene->m_selectObject->modelType() == Model::PARAM_SURFACE) {
                            m_splineSurface->updateSelectedVertexPosition(*m_localTransform, *m_worldTransform);
                            m_timerAutoUpdateSurface->stop();
                        }
                    }
                }
                setTransformInactive();
            } else {
                switch (m_mode) {
                case Mode::OBJECT:
                    Scene::m_scene->objectSelectRay(clickRay(event), m_shiftPressed);
                    break;

                case Mode::EDIT:
                    Scene::m_scene->vertexSelectRay(clickRay(event), m_shiftPressed);
                    break;
                }
                //                Scene::m_scene->selectRay(clickRay(event), m_shiftPressed);
                //                RayTracer::selectRay(clickRay(event), m_shiftPressed);
                //                m_posClickPress = event->pos();
            }

            break;
            //        }
        case Qt::MidButton:

            //            } else {
            if (!m_shiftPressed) {
                if (m_alignAxis) {
                    m_alignAxis = false;
                    updatePersepectiveProjection();
                }
            }
            //            }
            break;

        case Qt::RightButton:
            if (m_camera->m_cameraStrategy->m_type == CameraStrategy::FPS) {
                on_actionPoint_Light_triggered();
            } else {
                m_rightClicked = true;
                m_posFirstRightClick = event->pos();
                m_posMouse = event->pos();
            }
            break;
        }
    }

    //    qDebug() << "[3dView]" << QWidget::mapToGlobal(pos());
    //    setMouseTracking(true);
    //    setFocus();
    event->ignore(); // splitter node
}

void MainWindow3dView::mouseReleaseEvent(QMouseEvent* event)
{
    //    setMouseTracking(true);
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->mouseReleaseEvent(event);

        //        QPoint posClickRelease(event->pos());
        //        uint minX = qMin(m_posClickPress.x(), posClickRelease.x());
        //        uint maxX = qMax(m_posClickPress.x(), posClickRelease.x());
        //        uint minY = qMin(m_posClickPress.y(), posClickRelease.y());
        //        uint maxY = qMax(m_posClickPress.y(), posClickRelease.y());
        //        QRect selectRect(QPoint(minX, minY), QPoint(maxX, maxY));

        //        qDebug() << selectRect;
        //        QRect selectRect()
        switch (event->button()) {
        case Qt::RightButton:
            //            glm::mat4 projectionMatrix = glm::perspective(glm::radians(m_camera->m_fov), (float)width() / height(), l_near, l_far);
            //            Scene::m_scene->vertexSelectFrustum(projectionMatrix, viewMatrix(), m_shiftPressed);
            //            Scene::m_scene->vertexSelectFrustum({viewMatrix() * m_projectionMatrix}, m_shiftPressed);
            //            Scene::m_scene->vertexSelectFrustum({viewMatrix() * m_projectionMatrix}, m_shiftPressed);
            //            Scene::m_scene->vertexSelectFrustum(Frustum(viewMatrix() * m_projectionMatrix), m_shiftPressed);
            //            Scene::m_scene->vertexSelectFrustum(Frustum(m_projectionMatrix * viewMatrix()), m_shiftPressed);
            Scene::m_scene->vertexSelectFrustum(Frustum(m_camera->position(), m_camera->front(),
                                                    m_camera->right(), m_camera->up(), l_near, l_far, m_camera->m_fov,
                                                    static_cast<float>(width()) / height()),
                m_shiftPressed);
            m_rightClicked = false;

            ////            Q_ASSERT(m_iCamera < Scene::m_cameras.size());
            ////            Camera* m_camera = Scene::m_cameras[m_iCamera];
            //            //    QOpenGLFunctionsCore * m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
            //            //    qDebug() << "ratio " << width() / height();
            //            //    float ratio = static_cast<float>(height()) / width();
            //            float ratio = static_cast<float>(width()) / height();
            //            glm::vec3 front = m_camera->front();
            //            glm::vec3 right = m_camera->right();
            //            glm::vec3 up = m_camera->up();
            //            float fov = m_camera->m_fov;
            //            glm::vec3 source = m_camera->position();

            ////            float x = (2.0f * event->x()) / (float)width() - 1.0f;
            ////            float y = (2.0f * event->y()) / (float)height() - 1.0f;

            //            // ------------------------------------------------------------------------------------
            //            float halfHeightNearPlane = l_near * tanf(glm::radians(fov) * 0.5f);
            //            //    float heightNearPlane = l_near * tanf(glm::radians(m_camera->fov()) * ratio);
            //            //    float heightNearPlane = widthNearPlane;
            //            //    float heightNearPlane = l_near * tanf(glm::radians(m_camera->fov()));
            //            float halfWidthNearPlane = halfHeightNearPlane * ratio;

            ////            float dx = x * halfWidthNearPlane;
            ////            float dy = y * halfHeightNearPlane;
            //            float xTopLeft = -halfWidthNearPlane;
            //            float yTopLeft = -halfHeightNearPlane;
            //            float xBottomRight = halfWidthNearPlane;
            //            float yBottomRight = halfHeightNearPlane;

            ////            glm::vec3 hitNearPlane = source + m_camera->front() * l_near + m_camera->up() * -dy + m_camera->right() * -dx;
            //            glm::vec3 dirTopLeft = glm::normalize((source + front * l_near + up * yTopLeft + right * xTopLeft) - source);
            //            glm::vec3 dirBottomRight = glm::normalize((source + front * l_near + up * yBottomRight + right * xBottomRight) - source);
            //            glm::vec3 dirTopRight = glm::normalize((source + front * l_near + up * yTopLeft + right * xBottomRight) - source);
            //            glm::vec3 dirBottomLeft = glm::normalize((source + front * l_near + up * yBottomRight + right * xTopLeft) - source);

            //            Scene::m_scene->addRay({source, dirTopLeft});
            //            Scene::m_scene->addRay({source, dirBottomRight});
            //            Scene::m_scene->addRay({source, dirTopRight});
            //            Scene::m_scene->addRay({source, dirBottomLeft});

            //            return { source, glm::normalize(hitNearPlane - source) };
            // ------------------------------------------------------------------------

            //    float dx = x * fov * 0.5f;
            break;
        }
    }
}

void MainWindow3dView::mouseMoveEvent(QMouseEvent* event)
{
    //    setMouseTracking(true);
    //    centralWidget()->setMouseTracking(true);
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->mouseMoveEvent(event);
    }

    if (m_transformActive) {
        if (m_firstTransform) {
            m_firstTransform = false;

            m_memEventPos = event->pos();
            m_WheelPos = 0.0f;
        } else {
            QPoint diff = m_memEventPos - event->pos();
            //            float dx = diff.x() + m_memAxisPos;
            float dx = diff.x();
            float dy = diff.y();

            updateTransformMatrix(dx, dy);
        }
    }

    if (m_rightClicked) {
        m_posMouse = event->pos();
    }
    //    event->ignore();
}

void MainWindow3dView::wheelEvent(QWheelEvent* event)
{
    if (m_shiftPressed) {
        if (m_transformActive) {
            //            float dx = event->delta();
            //            int diff = m_memWheelPos - event->delta();
            if (m_firstTransform) {
                m_WheelPos = 0.0f;
            }
            m_WheelPos += event->delta();
            //            float newPos = dx + m_memAxisPos;
            //            m_memAxisPos = newPos;
            //        qDebug() << "transform active";
            //            if (!m_axisTransform) {
            //                if (m_transform == Transform::TRANSLATE) {
            //                    qDebug() << "translate";
            //                    //            if (!m_axisTransform) {
            //                    //            float newPos = dx + m_memAxisPos;
            ////                    m_worldTransform = m_worldTransform * glm::translate(glm::mat4(1.0f), m_memFront * dx);
            //                    //            m_memAxisPos = newPos;
            ////                    m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * m_memWheelPos);
            //                    //            }
            //                    return;
            //                }
            //                //            if (m_transform == Transform::SCALE) {
            //                //                m_transformMatrix = glm::scale(glm::mat4(1.0f), 1.0f + dx * 0.1f * glm::vec3(1.0f, 1.0f, 1.0f));
            //                //                return;
            //                //            }
            //            }
            //            //        if (m_axisTransform) {
            //        else {
            //        qDebug() << "axis active";

            //            float dx = event->delta();
            //            if (m_axisTransform) {
            //                //                updateTransformMatrix(m_WheelPos + m_memAxisPos, 0.0f);
            //                qDebug() << "wheelPos " << m_WheelPos;
            //                updateTransformMatrix(m_WheelPos, 0.0f);

            //            } else {
            //                updateTransformMatrix(0.0f, 0.0f);
            //            }
            return;
            //        }
        }
    }
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->wheelEvent(event);
    }

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
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->focusInEvent(event);

        m_shiftPressed = false;
    }
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
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_camera->m_cameraStrategy->resizeEvent(event);

        m_projectionMatrix = glm::perspective(glm::radians(m_camera->m_fov), (float)width() / height(), l_near, l_far);
    }
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
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        float targetDist;
        if (m_camera->m_cameraStrategy->m_type == CameraStrategy::WORLD) {
            //        glm::vec3 target = static_cast<CameraWorld*>(m_camera)->target();
            glm::vec3 target = m_camera->target();
            targetDist = glm::length(camera()->position() - target);
        } else {
            targetDist = 200.0f;
        }
        float fov = glm::radians(m_camera->m_fov);
        float right = targetDist * tanf(fov / 2);
        float ratio = (float)height() / width();
        float up = right * ratio;

        m_projectionMatrix = glm::ortho(-right, right, -up, up, l_near, l_far);
        m_ortho = true;
    }
}

void MainWindow3dView::updatePersepectiveProjection()
{
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];
        m_projectionMatrix = glm::perspective(glm::radians(m_camera->m_fov), (float)width() / height(), l_near, l_far);
        m_ortho = false;
    }
}

Ray MainWindow3dView::clickRay(QMouseEvent* event)
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    QOpenGLFunctionsCore * m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    qDebug() << "ratio " << width() / height();
    //    float ratio = static_cast<float>(height()) / width();
    float ratio = static_cast<float>(width()) / height();
    glm::vec3 front = m_camera->front();
    glm::vec3 right = m_camera->right();
    glm::vec3 up = m_camera->up();
    float fov = m_camera->m_fov;
    glm::vec3 source = m_camera->position();

    float x = (2.0f * event->x()) / (float)width() - 1.0f;
    float y = (2.0f * event->y()) / (float)height() - 1.0f;

    // ------------------------------------------------------------------------------------
    float heightNearPlane = l_near * tanf(glm::radians(m_camera->m_fov) * 0.5f);
    //    float heightNearPlane = l_near * tanf(glm::radians(m_camera->fov()) * ratio);
    //    float heightNearPlane = widthNearPlane;
    //    float heightNearPlane = l_near * tanf(glm::radians(m_camera->fov()));
    float widthNearPlane = heightNearPlane * ratio;

    float dx = x * widthNearPlane;
    float dy = y * heightNearPlane;

    glm::vec3 hitNearPlane = source + m_camera->front() * l_near + m_camera->up() * -dy + m_camera->right() * -dx;

    return { source, glm::normalize(hitNearPlane - source) };
    // ------------------------------------------------------------------------

    //    float dx = x * fov * 0.5f;
    //    float dy = y * fov * 0.5f;

    //    glm::mat4 rotate(1.0f);
    //    rotate = glm::rotate(rotate, glm::radians(-dx), up);
    //    rotate = glm::rotate(rotate, glm::radians(dy), right);

    //    front = glm::normalize(rotate * glm::vec4(front, 1.0f));
    //    return {source, front};

    //    glm::vec3 hitNearPlane = source + front * l_near + up * dy + right * -dx;

    //    float mx = (float)((event->x() - width() * 0.5) * (1.0 / width()) * m_camera->fov() * 0.5);
    //    float my = (float)((event->y() - height() * 0.5) * (1.0 / width()) * m_camera->fov() * 0.5);
    //    glm::vec3 dx = m_camera->right() * mx;
    //    glm::vec3 dy = m_camera->up() * my;

    //    glm::vec3 dir = normalize(m_camera->front() + (dx + dy) * 2.0f);

    //    return {m_camera->position(), dir};

    //    int y = (event->y() -height() / 2.0f) / (height() / 2.0f);

    //        emit launchRayTracing(x, y);
    //    qDebug() << "width " << width() << "height " << height() << "x" << x << "y" << y;

    //    glm::mat4 projView(projectionViewMatrix());

    //    glm::mat4 proj = glm::perspective(glm::radians(m_camera->fov()), (float)width() / height(), l_near, l_far);
    //    glm::mat4 proj = m_projectionMatrix;
    //        glm::mat4 view = m_camera->viewMatrix();

    //        glm::mat4 invVP = glm::inverse(proj * view);
    //        glm::vec4 screenPos = glm::vec4(x, -y, 1.0f, 1.0f);
    //        glm::vec4 worldPos = invVP * screenPos;

    //        glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
    //    return { m_camera->position(), dir };

    ////    float rad = fov *  / 180.0f;
    //    float rad = glm::radians(fov);
    //    float vLength = tanf(rad / 2.0f) * l_near;
    //    float hLength = vLength * (static_cast<float>(width()) / height());

    //    up *= hLength;
    //    right *= vLength;

    //    // question : ration = w / h or h / w ? horizontal fov or vertical ?
    ////    float ratio = static_cast<float>(width()) / height();

    //    //        int dx = x -width() /2;
    //    //        int dy = y -height() / 2;
    //    float dx = (2.0f * static_cast<float>(x) / width() - 1.0f);
    //    float dy = (static_cast<float>(y) / height() - 0.5f);

    //        qDebug() << "left click" << dx << dy;

    //    glm::mat4 rotate(1.0f);
    //        rotate = glm::rotate(rotate, dx, glm::vec3(0.0f, 0.0f, 1.0f));
    //        rotate = glm::rotate(rotate, dy, glm::vec3(1.0f, 0.0f, 0.0f));

    //    rotate = glm::rotate(rotate, glm::radians(-dx), up);
    //    rotate = glm::rotate(rotate, glm::radians(dy), right);

    //    front = glm::normalize(rotate * glm::vec4(front, 1.0f));
    //    glm::vec3 hitNearPlane = source +  front * l_near + up * dy + right * -dx;

    //    return { source, glm::normalize(hitNearPlane -source) };
}

void MainWindow3dView::updateTransformMatrix(float dx, float dy)
{
    //    qDebug() << "updateTransformMatrix " << dx << dy;
    //    glm::mat4 & m_transformMatrix = Scene::m_scene->m_transformMatrix;
    //    glm::mat4 & m_worldTransform = Scene::m_scene->m_worldTransform;

    *m_localTransform = glm::mat4(1.0f);

    switch (m_transform) {
    case Transform::TRANSLATE:
        if (m_axisTransform) {
            if (m_axisLocal) {

                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    *m_localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * (-dx + m_WheelPos));
                    break;
                case 1:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    *m_localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * (-dx + m_WheelPos));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    *m_localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * (-dx + m_WheelPos));
                    break;
                }
            } else {
                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    *m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * (-dx + m_WheelPos));
                    //            m_worldTransform = glm::translate(m_worldTransform, m_memFront * m_WheelPos);
                    break;
                case 1:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    *m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * (-dx + m_WheelPos));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    *m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * (-dx + m_WheelPos));
                    break;
                }
            }

        } else {

            *m_worldTransform = glm::translate(glm::mat4(1.0f), m_memRight * 3.0f * dx);
            *m_worldTransform = glm::translate(*m_worldTransform, m_memUp * 3.0f * dy);
            *m_worldTransform = glm::translate(*m_worldTransform, m_memFront * m_WheelPos);
        }
        break;

    case Transform::ROTATE:
        if (m_axisTransform) {
            if (m_axisLocal) {

                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    *m_localTransform = glm::rotate(*m_localTransform, -dx * 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
                    break;
                case 1:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * -dx);
                    *m_localTransform = glm::rotate(*m_localTransform, -dx * 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * -dx);
                    *m_localTransform = glm::rotate(*m_localTransform, -dx * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
                    break;
                }
            } else {
                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    *m_worldTransform = glm::rotate(glm::mat4(1.0f), -dx * 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
                    break;
                case 1:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * -dx);
                    *m_worldTransform = glm::rotate(glm::mat4(1.0f), -dx * 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * -dx);
                    *m_worldTransform = glm::rotate(glm::mat4(1.0f), -dx * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
                    break;
                }
            }

        } else {

            //                m_transformMatrix = glm::rotate(m_transformMatrix, 0.01f * dx, m_memUp);
            //                m_transformMatrix = glm::rotate(m_transformMatrix, dy* 0.01f, m_memRight);
            *m_localTransform = glm::rotate(*m_localTransform, -dx * 0.01f, m_memFront);
        }
        break;

    case Transform::SCALE:
        if (m_axisTransform) {
            if (m_axisLocal) {

                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    *m_localTransform = glm::scale(*m_localTransform, 1.0f + dx * 0.01f * glm::vec3(1.0f, 0.0f, 0.0f));
                    break;
                case 1:
                    //                        m_localTransform = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * -dx);
                    *m_localTransform = glm::scale(*m_localTransform, 1.0f + dx * 0.01f * glm::vec3(0.0f, 1.0f, 0.0f));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    //                            m_transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * -dx);
                    *m_localTransform = glm::scale(*m_localTransform, 1.0f + dx * 0.01f * glm::vec3(0.0f, 0.0f, 1.0f));
                    break;
                }
            } else {
                switch (m_axisFollow) {
                case 0:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    //                        m_translate += glm::vec3(1.0f, 0.0f, 0.0f);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f) * -dx);
                    *m_worldTransform = glm::scale(glm::mat4(1.0f), 1.0f + dx * 0.01f * glm::vec3(1.0f, 0.0f, 0.0f));
                    break;
                case 1:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * dx);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f) * -dx);
                    *m_worldTransform = glm::scale(glm::mat4(1.0f), 1.0f + dx * 0.01f * glm::vec3(0.0f, 1.0f, 0.0f));
                    break;
                case 2:
                    //                        m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(0.0f, 0.0f, 1.0f) * dx);
                    //                            m_worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f) * -dx);
                    *m_worldTransform = glm::scale(glm::mat4(1.0f), 1.0f + dx * 0.01f * glm::vec3(0.0f, 0.0f, 1.0f));
                    break;
                }
            }

        } else {

            //                    m_transformMatrix = glm::scale(m_transformMatrix, 1.0f + dx * 0.01f * m_memRight);
            //                    m_transformMatrix = glm::scale(m_transformMatrix, 1.0f + dy * 0.01f * m_memUp);
            *m_localTransform = glm::scale(*m_localTransform, 1.0f + dx * 0.01f * glm::vec3(1.0f, 1.0f, 1.0f));
        }
        break;
    }
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
    //    if (m_transformActive) {
    //        //        RayTracer::setSelectRootTransform(m_transformMatrix);
    //        sendTransformToScene();
    //    }
    if (m_iCamera < Scene::m_cameras.size()) {
        Camera* m_camera = Scene::m_cameras[m_iCamera];

        m_memAxisPos = 0.0f;
        m_transformActive = true;
        m_firstTransform = true;
        m_axisTransform = false;
        m_axisFollow = 10;
        //    m_axisLocal = true;
        m_memRight = m_camera->right();
        m_memUp = m_camera->up();
        m_memFront = m_camera->front();
        setMouseTracking(true);
        centralWidget()->setMouseTracking(true);
        setCursor(Qt::SizeAllCursor);

        if (m_mode == Mode::EDIT) {
            if (Scene::m_scene->m_selectObject != nullptr) {
                if (Scene::m_scene->m_selectObject->modelType() == Model::PARAM_CURVE) {
                    //                    m_paramModelSelected = static_cast<ParamModel*>(Scene::m_scene->m_selectObject->m_model);
                    m_splineCurve = static_cast<BSplineCurve*>(Scene::m_scene->m_selectObject->getModel());
                    //                    m_splineCurve = Scene::m_scene->m_selectObject->m_model;
                    m_timerAutoUpdateCurve->start(50);
                } else if (Scene::m_scene->m_selectObject->modelType() == Model::PARAM_SURFACE) {

                    m_splineSurface = static_cast<BSplineSurface*>(Scene::m_scene->m_selectObject->getModel());
                    m_timerAutoUpdateSurface->start(50);
                }
            }
        }
    }
}

void MainWindow3dView::setTransformInactive()
{
    m_transformActive = false;
    *m_localTransform = glm::mat4(1.0f);
    *m_worldTransform = glm::mat4(1.0f);
    setMouseTracking(false);
    centralWidget()->setMouseTracking(false);
    setCursor(Qt::ArrowCursor);

    m_axisTransform = false;
    //    m_axisLocal = false;
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
    //    RayTracer::setSelectRootTransform(*m_localTransform, *m_worldTransform);
    Scene::m_scene->setSelectRootTransform(*m_localTransform, *m_worldTransform, m_mode);
    //    RayTracer::setSelectRootTransform(m_worldTransform * m_transformMatrix);
    *m_localTransform = glm::mat4(1.0f);
    *m_worldTransform = glm::mat4(1.0f);
}

void MainWindow3dView::updateCameraId() const
{
    //    ui->menuCameraId->setTitle(QString("Camera " + QString::number(m_iCamera)));
    uint size = Scene::m_cameras.size();
    if (size == 0) {
        ui->menuCameraId->setTitle("No Camera");
    } else {

        //        m_iCamera = (m_iCamera + 1) % size;
        ui->menuCameraId->setTitle(QString("Camera ") + QString::number(m_iCamera));
    }
}

void MainWindow3dView::onUpdateCameraFps()
{
    static_cast<CameraFps*>(Scene::m_scene->m_cameras[m_iCamera]->m_cameraStrategy)->ProcessKeyboard();
}

void MainWindow3dView::onUpdateCurve()
{

    //    m_paramModelSelected->updateCurve();
    //    m_paramModelSelected->updateSelectedVertexPosition(*m_localTransform, *m_worldTransform);
    //    m_paramModelSelected->updateCurve(*m_localTransform, *m_worldTransform);
    m_splineCurve->updateCurve(*m_localTransform, *m_worldTransform);
    //    m_paramModelSelected->updk
}

void MainWindow3dView::onUpdateSurface()
{
    m_splineSurface->updateSurface(*m_localTransform, *m_worldTransform);
}

void MainWindow3dView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::white, 12));
    painter.drawLine(0, 0, 100, 100);
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

bool MainWindow3dView::intersectRay() const
{
    return ui->actionIntersectRay->isChecked();
}

bool MainWindow3dView::vertexGroupShader() const
{
    return m_shade == Shader::Type::VERTEX_GROUP;
}

bool MainWindow3dView::solid() const
{
    return m_shade == Shader::Type::SOLID;
}

void MainWindow3dView::setCursorToCenter()
{
    QPoint glob = mapToGlobal(QPoint(width() / 2, height() / 2));
    QCursor::setPos(glob);
}

const Shader& MainWindow3dView::shader() const
{
    //    return *m_shader;
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());

    Camera* m_camera = Scene::m_cameras[m_iCamera];
    const Shader& shader = *Shader::m_shaders[m_shade];

    shader.use();
    shader.setMat4("view", viewMatrix());
    shader.setMat4("projection", projectionMatrix());

    switch (m_shade) {
        //    case WIRE_FRAME:
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //        break;

    case Shader::Type::SOLID:
        shader.setVec3("viewPos", m_camera->position());
        shader.apply(Scene::m_scene->m_solid);
        //        shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
        //    m_shader->setVec3("material.diffuse", 0.3f, 0.3f, 0.3f);
        //        shader.setVec3("material.specular", 0.5f, 0.5f, 1.0f);
        //        shader.setFloat("material.shininess", 1.0f);
        break;

    case Shader::Type::LOOK_DEV:
        break;

    case Shader::Type::RENDERED:
        shader.setVec3("viewPos", m_camera->position());
        break;

    case Shader::Type::NORMAL:
        break;

    case Shader::Type::DEPTH:
        break;

    case Shader::Type::VERTEX_GROUP:
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

    //    glCullFace(GL_FRONT_AND_BACK);
    if (ui->actionX_Rays->isChecked()) {
        //        glBlendFunc(GL_ONE, GL_ONE);
        glDisable(GL_CULL_FACE);
    } else {
        //        glBlendFunc(GL_ONE, GL_ZERO);
        //        glDisable(GL_CULL_FACE);
        glEnable(GL_CULL_FACE);
    }

    //    return *m_shaders[m_shade];
    //    return *Shader::m_shaders[m_shade];
    return shader;
}

//std::list<QMenu> MainWindow3dView::menus() const
//{
//    return m_menus;
//}

const Camera* MainWindow3dView::camera() const
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    Q_ASSERT(m_camera != nullptr);
    return m_camera;
}

//void MainWindow3dView::setViews(std::list<const MainWindow3dView *> *views)
//{
//    m_views = views;
//}

glm::mat4 MainWindow3dView::viewMatrix() const
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    return m_viewMatrix;
    Q_ASSERT(m_camera != nullptr);
    return m_camera->viewMatrix();
    //    }

    //    return glm::mat4(1.0f);
}

glm::mat4 MainWindow3dView::projectionViewMatrix() const
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
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
    Q_ASSERT((m_iCamera < Scene::m_cameras.size()));
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    return glm::perspective(glm::radians(m_camera->m_fov - 1), (float)width() / height(), l_near, l_far);
}

//void MainWindow3dView::on_actionWireFrame_triggered()
//{
//    setShading(WIRE_FRAME);
//}

void MainWindow3dView::on_actionSolid_triggered()
{
    setShading(Shader::Type::SOLID);
}

void MainWindow3dView::on_actionLook_dev_triggered()
{
    setShading(Shader::Type::LOOK_DEV);
}

void MainWindow3dView::on_actionRendered_triggered()
{
    setShading(Shader::Type::RENDERED);
}

void MainWindow3dView::on_actionNormal_triggered()
{
    setShading(Shader::Type::NORMAL);
}

void MainWindow3dView::on_actionDepth_triggered()
{
    setShading(Shader::Type::DEPTH);
}

void MainWindow3dView::on_actionVertexGroup_triggered()
{
    setShading(Shader::Type::VERTEX_GROUP);
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

void MainWindow3dView::on_actionIntersectRay_triggered()
{
    if (ui->actionIntersectRay->isChecked()) {
        QPixmap pixmap(":/icons/intersectRay.png");
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

        painter.fillRect(pixmap.rect(), QColor(255, 0, 0));

        QIcon icon(pixmap);
        //        ui->menuWireFrame->setIcon(icon);
        ui->menuIntersectRay->setIcon(icon);

    } else {

        //        ui->menuWireFrame->setIcon(ui->actionWireFrame->icon());
        ui->menuIntersectRay->setIcon(ui->actionIntersectRay->icon());
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

void MainWindow3dView::on_actionDir_Light_triggered()
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    Scene::m_scene->addLight(Light::Type::SUN, m_camera->m_target);
    QOpenGLWidget_Editor::m_editor->addLight(Light::Type::SUN, m_camera->target());
}

void MainWindow3dView::on_actionPoint_Light_triggered()
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    Scene::m_scene->addLight(Light::Type::POINT, m_camera->m_target);
    QOpenGLWidget_Editor::m_editor->addLight(Light::Type::POINT, m_camera->target());
}

void MainWindow3dView::on_actionSpot_Light_triggered()
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    Scene::m_scene->addLight(Light::Type::SPOT, m_camera->m_target);
    QOpenGLWidget_Editor::m_editor->addLight(Light::Type::SPOT, m_camera->target());
}

void MainWindow3dView::on_actionArea_Light_triggered()
{
    Q_ASSERT(m_iCamera < Scene::m_cameras.size());
    Camera* m_camera = Scene::m_cameras[m_iCamera];
    //    Scene::m_scene->addLight(Light::Type::AREA, m_camera->m_target);
    QOpenGLWidget_Editor::m_editor->addLight(Light::Type::AREA, m_camera->target());
}

//void MainWindow3dView::on_actionB_Spline_triggered()
//{
//    //    QOpenGLWidget_Editor::m_editor->addCurve(Curve::B_SPLINE);
//}

//void MainWindow3dView::on_actionBSpline_curve_triggered()
//{
//    QOpenGLWidget_Editor::m_editor->addCurve();
//}

//void MainWindow3dView::on_actionBSpline_surface_triggered()
//{
//    QOpenGLWidget_Editor::m_editor->addSurface();
//}

void MainWindow3dView::on_actionSpline_triggered()
{

    QOpenGLWidget_Editor::m_editor->addCurve(BSplineCurve::Type::SPLINE);
}

void MainWindow3dView::on_actionCircle_triggered()
{
    QOpenGLWidget_Editor::m_editor->addCurve(BSplineCurve::Type::CIRCLE);
}

void MainWindow3dView::on_actionCircle8_triggered()
{
    QOpenGLWidget_Editor::m_editor->addCurve(BSplineCurve::Type::CIRCLE8);
}

void MainWindow3dView::on_actionTomb_triggered()
{
    QOpenGLWidget_Editor::m_editor->addSurface(BSplineSurface::TOMB);
}

void MainWindow3dView::on_actionSphere_triggered()
{
    QOpenGLWidget_Editor::m_editor->addSurface(BSplineSurface::SPHERE);
}

void MainWindow3dView::on_actionPlane_triggered()
{
    QOpenGLWidget_Editor::m_editor->addSurface(BSplineSurface::PLANE);
}

void MainWindow3dView::on_actionThor_triggered()
{

    QOpenGLWidget_Editor::m_editor->addSurface(BSplineSurface::THOR);
}

void MainWindow3dView::on_actionPot_triggered()
{
    QOpenGLWidget_Editor::m_editor->addSurface(BSplineSurface::POT);
}
