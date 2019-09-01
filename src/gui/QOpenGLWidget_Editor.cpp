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

QOpenGLWidget_Editor::QOpenGLWidget_Editor(QWidget* parent, QMainWindow* mainWindow)
    : QOpenGLWidget(parent)
    , m_mainWindow(mainWindow)
{

    setAutoFillBackground(false);
    //    setStyleSheet("background-color: transparent");
    //    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_AlwaysStackOnTop);

    //    m_stream << std::setprecision(2) << std::fixed;
}

void QOpenGLWidget_Editor::loadNewModel(std::string filename)
{
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    makeCurrent();

    m_scene.addModel(filename);
}

void QOpenGLWidget_Editor::load(std::ifstream& file)
{
    //    clear();
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());
    //    qDebug() << "[GL_CONTEXT]" << QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    makeCurrent();

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
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

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

    m_axis = new Axis();

    //    QGLFormat glFormat;
    //      glFormat.setSampleBuffers(true);
    //      glFormat.setSamples(4);

    //    shaderAxis = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");
    //    g_env.m_scene.initialize();
    m_scene.initialize();

    //    m_textRender.initialize();
//    BoundingBox::m_cube.setupGL();

    m_lastFrame = QDateTime::currentMSecsSinceEpoch();
}

void QOpenGLWidget_Editor::paintGL()
{
    Q_ASSERT(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>());

    uint64_t currentFrameTime = QDateTime::currentMSecsSinceEpoch();

    if (m_cpt % 24 == 0) {
        m_deltaTime = currentFrameTime - m_lastFrame;
        m_lastFrame = currentFrameTime;

        m_fps = 24000.0f / m_deltaTime;

        ////            qDebug() << "fps : " << m_fps / period;
        //            m_fps = 0.0;
        //        m_stream.clear();
        //        m_stream << m_fps;
        //        std::string str;
        //    m_stream << m_fps << "\n";
        //        std::cout << "fps : " << m_fps << std::endl;
        m_statusBar->showMessage("fps:" + QString::number(m_fps));
    }
    //        glClearColor(0.0f, 1.0f, 0.0f, 0.5f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //    glViewport(width() - 100, 10, 100, 100);

    //    m_textRender.RenderText(str , 0.0f, 0.0f, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    //    glViewport(100, 100, 100, 100);
    // -------------------------------------------------------------------------------

    glm::mat4 model(1.0);

    m_scene.prepareHierarchy(currentFrameTime);

    for (const MainWindow3dView* view : *m_views) {


        Q_ASSERT(view->parent()->parent());
        Q_ASSERT(m_mainWindow->isAncestorOf(view));
        //        if (! m_mainWindow->isAncestorOf(view)) {
        //            continue;
        //        }

        QPoint point = view->mapTo(m_mainWindow, view->pos());

        int x = point.x();
        int y = m_mainWindow->height() - point.y() - view->height() + 5;
        glViewport(x, y, view->width(), view->height());

        glm::mat4 viewMatrix = view->viewMatrix();
        //        glm::mat4 projectionMatrix = view->projectionMatrix();
        m_scene.draw(*view);

        int minSide = qMin(view->width(), view->height());
        glViewport(x + 5, y + 5, minSide / 10, minSide / 10);
        m_axis->draw(viewMatrix);

//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    // ----------------------------------------------------------------

    ++m_cpt;
    //        QThread::msleep(10);
    update();
}

void QOpenGLWidget_Editor::setStatusBar(QStatusBar* statusBar)
{
    m_statusBar = statusBar;
}

void QOpenGLWidget_Editor::setViews(std::list<const MainWindow3dView*>* views)
{
    m_views = views;
    m_scene.setViews(views);
}
