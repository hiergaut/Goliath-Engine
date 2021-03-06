#include "QOpenGLWidget_Editor.h"

#include <QDateTime>
//#include <engine/Environment.h>
//#include <QMainWindow>

#include <QThread>
//#include <QMainWindow>
//#include "qmainwindow.h"
#include <QStandardItem>
#include <assimp/Importer.hpp>
//#include <gui/editor/fileOpenned/QListView_FileOpenned.h>
//#include <gui/editor/outliner/QTreeView_outliner.h>

//#include <freetype2/ft2build.h>
//#include <freetype2/freetype/freetype.h>
//#include <freetype2/freetype/ftglyph.h>
//#include <freetype2/freetype/ftoutln.h>
//#include <freetype2/freetype/fttrigon.h>
//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <iomanip>
#include <opengl/geometry/AxisGeometry.h>
#include <opengl/geometry/CubeGeometry.h>
#include <opengl/geometry/CubeMapGeometry.h>
#include <opengl/geometry/DotGeometry.h>
#include <opengl/geometry/LineGeometry.h>
#include <opengl/geometry/QuadGeometry.h>
#include <opengl/geometry/ScreenQuadGeometry.h>
#include <opengl/geometry/SkyBoxGeometry.h>
#include <opengl/geometry/TriangleGeometry.h>
#include <opengl/geometry/boneGeometry.h>
#include <opengl/geometry/uvSphereGeometry.h>

#include <QPainter>
#include <gui/editor/timeline/FormTimeline.h>

QOpenGLWidget_Editor* QOpenGLWidget_Editor::m_editor = nullptr;

QOpenGLWidget_Editor::QOpenGLWidget_Editor(QWidget* parent, QMainWindow* mainWindow)
    : QOpenGLWidget(parent)
    , m_mainWindow(mainWindow)
{
    RayTracer::setScene(&m_scene);

    setAutoFillBackground(false);
    //    setStyleSheet("background-color: transparent");
    //    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_AlwaysStackOnTop);

    //    m_stream << std::setprecision(2) << std::fixed;
    Q_ASSERT(m_editor == nullptr);
    m_editor = this;

    //    m_renderTimer = new QTimer(this);
    //    connect(m_renderTimer, &QTimer::timeout, this, &QOpenGLWidget_Editor::update);
}

void QOpenGLWidget_Editor::loadNewModel(std::string filename)
{
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    makeCurrent();

    glm::vec3 spawn(0.0f);

    for (const MainWindow3dView* view : *m_views) {
        if (view->hasFocus()) {
            spawn = view->camera()->target();
            break;
            //            switch (view->camera()->m_type) {
            //            case Camera::Type::FPS:
            //                //            origin = static_cast<CameraFps*>(view->m_camera)->m_target;
            //                spawn = glm::vec3(0.0f, 0.0f, 0.0f);
            //                break;

            //            case Camera::Type::WORLD:
            //                spawn = static_cast<const CameraWorld*>(view->camera())->m_target;
            //                break;
            //            }
            //            break;
        }
    }

    m_scene.addModel(filename, spawn);
}

void QOpenGLWidget_Editor::clear()
{
    m_views->clear();
    m_scene.clear();
}

void QOpenGLWidget_Editor::load(std::ifstream& file)
{
    //    clear();
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    clear();
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    makeCurrent();

//    m_scene.clear();
    m_scene.load(file);
}

void QOpenGLWidget_Editor::save(std::ofstream& file)
{
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    makeCurrent();

    m_scene.save(file);
}

void QOpenGLWidget_Editor::initializeGL()
{
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    Q_ASSERT(m_fun != nullptr);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    //        glDisable(GL_MULTISAMPLE);

    GLint MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    printf("Max supported patch vertices %d\n", MaxPatchVertices);
    m_fun->glPatchParameteri(GL_PATCH_VERTICES, 3);

    //        glEnable(GL_SAMPLE_COVERAGE);
    //        glDisable(GL_MULTISAMPLE);

    //    glEnable(GL_STENCIL_TEST);
    //    glStencilMask(0x00);
    //    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //    glEnable(GL_BLEND);
    //    glEnable(GL_LINE_SMOOTH);

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
    glPointSize(5.0f);
    glEnable(GL_POINT_SMOOTH);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Shader::glInitialize();

    m_axis = new Axis();

    //    QGLFormat glFormat;
    //      glFormat.setSampleBuffers(true);
    //      glFormat.setSamples(4);

    //    shaderAxis = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");
    //    g_env.m_scene.initialize();
    m_scene.initializeGL();

    //    m_scene.updateAllLightsShadowMap();

    //    RayTracer::setBone(new BoneGeometry);

    LineGeometry::initializeGL();
    CubeGeometry::initializeGL();
    TriangleGeometry::initializeGL();
    DotGeometry::initializeGL();
    AxisGeometry::initializeGL();
    UvSphereGeometry::initializeGL();
    BoneGeometry::initializeGL();
    QuadGeometry::initializeGL();
    ScreenQuadGeometry::initializeGL();
    SkyBoxGeometry::initializeGL();
    CubeMapGeometry::initializeGL();


    //    m_scene.updateAllLightsShadowMap();
    //    FormTimeline::setScene(&m_scene);

    //    m_textRender.initialize();
    //    BoundingBox::m_cube.setupGL();

    m_lastFrame = QDateTime::currentMSecsSinceEpoch();

    //    m_scene.prepareHierarchy(0.0f);
    //    m_scene.updateBoundingBox();

    m_initialized = true;
    //    m_renderTimer->start(100);
    //    for (const MainWindow3dView* view : *Scene::m_scene->m_views) {
    ////        if (view->m_iCamera == m_id) {
    //            view->updateFrustum();
    ////        }
    //        //        iCameras.push_back(view->m_iCamera);
    //    }
    //    m_scene.updateAllLightsShadowMap();
}

void drawRect(int x1, int y1, int x2, int y2, int windowHeight)
{
    glEnable(GL_COLOR_LOGIC_OP);
    glLogicOp(GL_XOR);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRecti(x1, windowHeight - y1, x2, windowHeight - y2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_COLOR_LOGIC_OP);
}

void QOpenGLWidget_Editor::paintGL()
{
    Q_ASSERT(m_initialized);
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());

    uint64_t currentFrameTime = QDateTime::currentMSecsSinceEpoch();

    int period = 60; // nb frames
    if (m_cpt % period == 0) {
        m_deltaTime = currentFrameTime - m_lastFrame;
        m_lastFrame = currentFrameTime;

        m_fps = (period * 1000.0f) / m_deltaTime;

        ////            qDebug() << "fps : " << m_fps / period;
        //            m_fps = 0.0;
        //        m_stream.clear();
        //        m_stream << m_fps;
        //        std::string str;
        //    m_stream << m_fps << "\n";
        //        std::cout << "fps : " << m_fps << std::endl;
//        m_statusBar->showMessage("fps:" + QString::number(m_fps) + "  camera:" + QString::number(m_scene.m_cameras.size()) + "  dirLight:" + QString::number(m_scene.m_dirLights.size()) + "  pointLight:" + QString::number(m_scene.m_pointLights.size()) + "  spotLight:" + QString::number(m_scene.m_spotLights.size()) + "  shadow:" + QString::number(m_scene.m_computeShadow) + "  zPrepass:" + QString::number(m_scene.m_zPrepass) + "  multisample:" + QString::number(m_multiSample) + "  frustumCulling:" + QString::number(Frustum::m_enable) + "  pointLightsShadow:" + QString::number(Scene::m_scene->m_nbComputePointLightShadow));
        m_statusBar->showMessage("fps:" + QString::number(m_fps) + "  camera:" + QString::number(m_scene.m_cameras.size()) + "  dirLight:" + QString::number(m_scene.m_dirLights.size()) + "  pointLight:" + QString::number(m_scene.m_pointLights.size()) + "  spotLight:" + QString::number(m_scene.m_spotLights.size()) + "  shadow:" + QString::number(m_scene.m_computeShadow) + "  zPrepass:" + QString::number(m_scene.m_zPrepass) + "  multisample:" + QString::number(m_multiSample) + "  frustumCulling:" + QString::number(Frustum::m_enable));
    }
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glViewport(100, 100, 100, 100);
    //                glClearColor(0.0f, 1.0f, 0.0f, 0.5f);

    //    glViewport(width() - 100, 10, 100, 100);

    //    m_textRender.RenderText(str , 0.0f, 0.0f, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    //    glViewport(100, 100, 100, 100);
    // -------------------------------------------------------------------------------

    //    glm::mat4 modelMatrix(1.0);

    bool autoUpdate = false;
    for (const MainWindow3dView* view : *m_views) {
        if (view->boundingBox()) {
            autoUpdate = true;
            //            break;
        }
        //                m_fun->glBindFramebuffer(GL_FRAMEBUFFER, view->hdrFbo());
        //                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    //    m_fun->glBindFramebuffer(GL_FRAMEBUFFER, 1);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_scene.m_autoUpdateBoundingBox = autoUpdate;
    m_scene.prepareHierarchy(currentFrameTime, Scene::m_scene->m_localPoseTransform, Scene::m_scene->m_worldPoseTransform);
    //    m_scene.prepareHierarchy(0);
    m_scene.updateLightsShadowMap();
    //    m_scene.updateAllLightsShadowMap();

    for (const MainWindow3dView* view : *m_views) {
        if (view->m_iCamera < Scene::m_cameras.size()) {

            Q_ASSERT(view->parent()->parent());
            Q_ASSERT(m_mainWindow->isAncestorOf(view));
            //        if (! m_mainWindow->isAncestorOf(view)) {
            //            continue;
            //        }

            QPoint point = view->mapTo(m_mainWindow, view->pos());

            const int viewWidth = view->width();
            const int viewHeight = view->height();
            const int x = point.x();
            const int y = m_mainWindow->height() - point.y() - viewHeight + 5;
            //            glViewport(x, y, viewWidth, viewHeight);

            //            glViewport(x, y - 3, view->width(), view->height());

            //        glm::mat4 projectionMatrix = view->projectionMatrix();
            m_scene.draw(*view, x, y, viewWidth, viewHeight);
            //        RayTracer::draw(modelMatrix, viewMatrix, projectionMatrix);

            int minSide = qMin(viewWidth, viewHeight);
            glViewport(x + 5, y + 5, minSide / 10, minSide / 10);
            glm::mat4 viewMatrix = view->viewMatrix();
            m_axis->draw(viewMatrix);

            //            drawRect(x + 50, y + 50, x + 2000, y +2000, view->height());

            //        glClear(GL_DEPTH_BUFFER_BIT);
            //            glDisable(GL_DEPTH_TEST);
            //            glDepthFunc(GL_ALWAYS);
            //                QPainter painter(this);

            //                painter.setPen(QPen(Qt::white, 12));
            //                painter.drawLine(x + 100, y + 100, x + 1000, y + 1000);
            ////            glEnable(GL_DEPTH_TEST);
            //            glDepthFunc(GL_LESS);
            //            painter.end();

            //                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
    }
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //    m_scene.updateLightsShadowMap();

    // ----------------------------------------------------------------

    ++m_cpt;
#ifdef DEBUG
    QThread::msleep(10);
#endif
    update();
}

void QOpenGLWidget_Editor::setStatusBar(QStatusBar* statusBar)
{
    m_statusBar = statusBar;
}

void QOpenGLWidget_Editor::addLight(Light::Type lightType, const glm::vec3 position)
{
    Q_ASSERT(m_initialized);
    makeCurrent();
    m_scene.addLight(lightType, position);
}

void QOpenGLWidget_Editor::addDefaultCamera()
{
    Q_ASSERT(m_initialized);
    makeCurrent();
    //    m_scene.m_cameras.push_back(new CameraWorld(60.0f, glm::vec3(200.0f, -200.0f, 200.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    //    m_scene.m_cameras.push_back(new Camera(60.0f));
    m_scene.addDefaultCamera();

    for (const MainWindow3dView* view : *m_views) {
        view->updateCameraId();
    }
}

void QOpenGLWidget_Editor::addCurve(BSplineCurve::Type type)
{
    makeCurrent();
    m_scene.addCurve(type);
}

void QOpenGLWidget_Editor::addSurface(BSplineSurface::Type type)
{
    makeCurrent();
    m_scene.addSurface(type);
}

void QOpenGLWidget_Editor::switchMultiSample()
{
    makeCurrent();
    if (m_multiSample) {
        glDisable(GL_MULTISAMPLE);
    } else {
        glEnable(GL_MULTISAMPLE);
    }

    m_multiSample = !m_multiSample;
}

void QOpenGLWidget_Editor::makeCurrent()
{
    QOpenGLWidget::makeCurrent();
}

//void QOpenGLWidget_Editor::addCameraWorld(float fov, glm::vec3&& position, glm::vec3&& target)
//{
//    Q_ASSERT(m_initialized);
//    makeCurrent();
//    m_scene.m_cameras.push_back(new CameraWorld(position, target));
//}

//void QOpenGLWidget_Editor::deleteCamera(uint iCamera)
//{
//    bool other = false;
//    for (const MainWindow3dView* view : *m_views) {
//        if (view->m_iCamera == iCamera) {
//            other = true;
//            break;
//        }
//    }

//    if (!other) {
//        m_scene.removeCamera(iCamera);
////        m_scene.m_cameras.erase(m_scene.m_cameras.begin() + iCamera);
////        m_scene.m_cameras.remove(
////        for (const MainWindow3dView* view : *m_views) {
////            if (view->m_iCamera == iCamera) {
////                other = true;
////                break;
////            }
////        }
//    }
//}

void QOpenGLWidget_Editor::setViews(std::list<const MainWindow3dView*>* views)
{
    m_views = views;
    m_scene.setViews(views);
}
