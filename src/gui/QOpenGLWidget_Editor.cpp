#include "QOpenGLWidget_Editor.h"

#include <QDateTime>
//#include <engine/Environment.h>
//#include <QMainWindow>

#include <QThread>
//#include <QMainWindow>
//#include "qmainwindow.h"

QOpenGLWidget_Editor::QOpenGLWidget_Editor(QWidget* parent, QMainWindow * mainWindow)
    : QOpenGLWidget(parent)
    , m_mainWindow(mainWindow)
{

    //    g_env.m_splitterRoot = & m_splitterRoot;

    setAutoFillBackground(false);
    //    setStyleSheet("background-color: transparent");
    //    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_AlwaysStackOnTop);
    //    loadEnv("temp.dat");
    //    g_env.m_views = &m_views;
}

void QOpenGLWidget_Editor::loadNewModel(std::string filename)
{
    makeCurrent();
//    Model newModel(filename);
//    m_models.push_back(std::move(newModel));
    m_scene.addModel(filename);

}

void QOpenGLWidget_Editor::load(ifstream & filename)
{

    makeCurrent();
//    g_env.load(filename);
    m_scene.load(filename);
//    std::ifstream file;
//    file.open(filename, std::ios::binary | std::ios::in);
//    if (!file.is_open()) {
//        std::cerr << "cannot open file" << std::endl;
//        //        exit(1);
//    } else {

//        g_env.load(file);
//        file.close();
//    }

}

void QOpenGLWidget_Editor::save(ofstream &filename)
{
    makeCurrent();
//    g_env.save(filename);
    m_scene.save(filename);

}

//std::vector<const QOpenGLWidget_3dView *> *QOpenGLWidget_Editor::views()
//{
//    return & m_views;
//}

//void QOpenGLWidget_Editor::addView(const QOpenGLWidget_3dView *view)
//{
////    m_views.emplace_back(view);
//    m_views.push_back(view);
//}

//void QOpenGLWidget_Editor::loadEnv(std::string filename)
//{
////    qDebug() << "[CONTEXT] mainWindow loadFile : " << QOpenGLContext::globalShareContext();

////    QOpenGLContext* ctx = QOpenGLContext::currentContext();
////    qDebug() << "[CONTEXT] mainWindow loadFile : " << ctx;

////    ctx->setShareContext(g_openglContext->m_context);

////    ui->stackedWidget->removeWidget(ui->page_splitterRoot);

//    //    qDebug() << "------------------------------ open conf ------------------------------";
//    std::ifstream file;
//    file.open(filename, std::ios::binary | std::ios::in);
//    if (!file.is_open()) {
//        std::cerr << "cannot open file" << std::endl;
//        //        exit(1);
//    } else {
//        g_env.load(file);
//        file.close();
//    }
//}

void QOpenGLWidget_Editor::initializeGL()
{
    QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

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

    m_axis = new Axis();

    //    QGLFormat glFormat;
    //      glFormat.setSampleBuffers(true);
    //      glFormat.setSamples(4);

    //    shaderAxis = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");
//    g_env.m_scene.initialize();
    m_scene.initialize();

}

//void QOpenGLWidget_Editor::resizeGL(int w, int h)
//{
//    qDebug() << "[GL EDITOR] : resize " << w << h;
//    //    QOpenGLWidget::makeCurrent();
//    //    glViewport(0, 0, w, h);
//    //    updateProjection();
//}

void QOpenGLWidget_Editor::paintGL()
{
    QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    QOpenGLWidget::makeCurrent();

    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    QOpenGLFunctions *fun = QOpenGLContext::currentContext()->functions();
    //    QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();

    //    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    //    m_deltaTime = currentFrame - m_lastFrame;
    //    m_lastFrame = currentFrame;
    //    m_fps += 1000.0 / m_deltaTime;
    //    if (m_cpt % 60 == 0) {
    //        qDebug() << "fps : " << m_fps / 60.0;
    //        m_fps = 0.0;
    //    }

    //    cameraMove();

    //    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glDepthMask(GL_FALSE);

    //    glViewport(100, 100, 100, 100);
    //    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    // -------------------------------------------------------------------------------

    //    glm::mat4 view = camera->getViewMatrix();
    //    //    glm::mat4 projection = m_projection;
    glm::mat4 model(1.0);
    //            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
    //            model = glm::scale(model, glm::vec3(0.01f));
    //            m_shader->use();

    for (const QOpenGLWidget_3dView * v : *m_views) {
//    for (const CameraWorld & camera : m_scene.cameras) {
//        Q_ASSERT(v);
        //        qDebug() << v << v->rect();
        //            QRect vRect = v->geometry();
        if (v->height() < 20 || v->width() < 20)
            continue;

        QPoint point = v->mapTo(m_mainWindow, v->pos());

        //            qDebug() << v << point;
        //            vRect.moveTopLeft(this->mapToGlobal(vRect.topLeft()));
        //    //        auto g = v->geometry();
        //            int x = vRect.x();
        //            int y = vRect.y();
        //            int width = vRect.width();
        //            int height = vRect.height();
        //            qDebug() << "[EDITOR] view " << v << x << y << width << height;

        int x = point.x();
        int y = m_mainWindow->height() - point.y() - v->height();
        glViewport(x, y, v->width(), v->height());
        //            glViewport(x, y, width, height);
        //        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 viewMatrix = v->viewMatrix();
        glm::mat4 projectionMatrix = v->projectionMatrix();

//        m_shader->use();
//        m_shader->setMat4("model", model);
//        m_shader->setMat4("view", viewMatrix);
//        m_shader->setMat4("projection", projectionMatrix);
//        //        qDebug() << "[3dView] " << this << "nb model = " << g_env.m_scene.size();
        //        for (int i =0; i <g_env.m_scene.size(); ++i) {
        //            g_env.m_scene[i].Draw(*m_shader);
        ////            m_scene = g_env.m_scene.at(0);
        ////            Model & model = g_env.m_scene.at(0);
        ////            model.Draw(*m_shader);
        //        }

        //    for (Model & model : m_models) {
        //        model.Draw(*m_shader);
        //    }
//        m_scene->Draw(*m_shader);
//        g_env.m_scene.draw(m_shader);
        m_scene.draw(projectionMatrix, viewMatrix);
//        for (Model * model : g_env.m_scene) {
//            model->Draw(*m_shader);
//        }

//        m_grid->draw(model, viewMatrix, projectionMatrix);

        //    m_grid->draw();

        //    shader.setVec3("viewPos", camera.Position);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        glViewport(x + 5, y + 5, 55, 55);
        //    glEnable(GL_LINE_SMOOTH);
        //    glDisable(GL_LINE_SMOOTH);
        //    glEnable(GL_LINE_SMOOTH);

        //    glLineWidth(10);
        //    GLfloat lineWidgthRange[2] ={0.0f, 0.0f};
        //    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidgthRange);
        //    qDebug() << lineWidgthRange[0] << lineWidgthRange[1];
        m_axis->draw(viewMatrix);
    }

    // ----------------------------------------------------------------

    ++m_cpt;
//    QThread::msleep(1000);
    update();
}

void QOpenGLWidget_Editor::setViews(std::list<const QOpenGLWidget_3dView *> *views)
{
    m_views = views;
}
