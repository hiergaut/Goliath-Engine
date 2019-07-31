#include "QOpenGLWidget_Editor.h"

#include <QDateTime>
#include <engine/Environment.h>

QOpenGLWidget_Editor::QOpenGLWidget_Editor(QWidget* parent)
    : QOpenGLWidget(parent)
{

    //    g_env.m_splitterRoot = & m_splitterRoot;

    //    loadEnv("temp.dat");
    g_env.m_views = &m_views;
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
    //    fun = context()->versionFunctions<QOpenGLFunctionsCore>();
    //    QOpenGLWidget::makeCurrent();
    //    qDebug() << QThread::currentThreadId() << "[3dView]" << this << "[CONTEXT]" << QOpenGLContext::currentContext()->functions();

    //    qDebug() << "[GROUP] " << this << " 3dView : " << context()->shareGroup()->shares().size();
    //    for (const auto & ctx : context()->shareGroup()->shares()) {
    //        qDebug() << "\t" << ctx->functions();
    //    }

    //    QOpenGLContext * ctx = QOpenGLContext::currentContext();
    //    ctx->setShareContext(g_ctx);
    //    qDebug() << "[CONTEXT] 3dView : " << ctx;

    //    QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    QOpenGLWidget::makeCurrent();
    //    fun->initializeOpenGLFunctions();
    //    QOpenGLExtraFunctions * fun = QOpenGLContext::globalShareContext()->extraFunctions();
    //    Q_ASSERT(fun);
    //    qDebug() << "[CONTEXT] 3dView : " << fun;

    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        qDebug() << "3dview " << fun;

    //        fun->initializeOpenGLFunctions();
    //    QOpenGLFunctions *fun = QOpenGLContext::currentContext()->functions();
    //    initializeOpenGLFunctions();
    //    makeCurrent();

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

    m_shader = new Shader(g_shaderPath + "model_loading.vsh", g_shaderPath + "model_loading.fsh");

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

    //    shader = Shader(":/model_loading.vsh", ":/shader/model_loading.fsh");

    //        shader = Shader("../Goliath-Engine/shader/model_loading.vsh", "../Goliath-Engine/shader/depthTesting.fsh");

    //    shaderLight = Shader("../Goliath-Engine/resources/shader/light.vsh", "../../Goliath-Engine/resources/shader/light.fsh");
    //    Model
    //    model =  Model("../Goliath-Engine/model/cube/cube.obj");
    //    scene = Model(":/maps/de_aztec/de_aztec.obj");

    m_scene = new Model(g_resourcesPath + "maps/de_aztec/de_aztec.obj");

    //    scene = Model("../Goliath-Engine/model/nanosuit/nanosuit.obj");
    //    camera = new CameraWorld(glm::vec3(10, -10, 10), glm::vec3(0, 0, 0));
    //    m_projection = glm::perspective(glm::radians(camera->getFov()), width() / float(height()), l_near, l_far);
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

void QOpenGLWidget_Editor::resizeGL(int w, int h)
{
    //    QOpenGLWidget::makeCurrent();
        glViewport(0, 0, w, h);
    //    updateProjection();
}

void QOpenGLWidget_Editor::paintGL()
{
    //    QOpenGLWidget::makeCurrent();

    //        QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    QOpenGLFunctions *fun = QOpenGLContext::currentContext()->functions();
    //    QOpenGLExtraFunctions * fun = QOpenGLContext::currentContext()->extraFunctions();

    uint64_t currentFrame = QDateTime::currentMSecsSinceEpoch();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    m_fps += 1000.0 / m_deltaTime;
    if (m_cpt % 60 == 0) {
        qDebug() << "fps : " << m_fps / 60.0;
        m_fps = 0.0;
    }

    //    cameraMove();

        glViewport(100, 100, 100, 100);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glDepthMask(GL_FALSE);

    // -------------------------------------------------------------------------------

    //    glm::mat4 view = camera->getViewMatrix();
//    //    glm::mat4 projection = m_projection;
//    glm::mat4 model(1.0);
//    //    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0, 0));
//    //    model = glm::scale(model, glm::vec3(0.01f));

//    m_shader->use();
//    m_shader->setMat4("model", model);

//    for (auto v : m_views) {
//        int x = v->x();
//        int y = v->y();
//        int width = v->width();
//        int height = v->height();
//        qDebug() << "[EDITOR] view " << v << x << y << width << height;

////        glViewport(x, y, width, height);

////        glm::mat4 viewMatrix = v->viewMatrix();
////        glm::mat4 projectionMatrix = v->projectionMatrix();

////        m_shader->setMat4("view", viewMatrix);
////        m_shader->setMat4("projection", projectionMatrix);
////        //        qDebug() << "[3dView] " << this << "nb model = " << g_env.m_scene.size();
////        //        for (int i =0; i <g_env.m_scene.size(); ++i) {
////        //            g_env.m_scene[i].Draw(*m_shader);
////        ////            m_scene = g_env.m_scene.at(0);
////        ////            Model & model = g_env.m_scene.at(0);
////        ////            model.Draw(*m_shader);
////        //        }

////        //    for (Model & model : m_models) {
////        //        model.Draw(*m_shader);
////        //    }
////        m_scene->Draw(*m_shader);

////        m_grid->draw(model, viewMatrix, projectionMatrix);
////        //    m_grid->draw();

////        //    shader.setVec3("viewPos", camera.Position);
////        //    glDrawArrays(GL_TRIANGLES, 0, 36);
////        glViewport(x +5, y +5, x +55, y +55);
////        //    glEnable(GL_LINE_SMOOTH);
////        //    glDisable(GL_LINE_SMOOTH);
////        //    glEnable(GL_LINE_SMOOTH);

////        //    glLineWidth(10);
////        //    GLfloat lineWidgthRange[2] ={0.0f, 0.0f};
////        //    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidgthRange);
////        //    qDebug() << lineWidgthRange[0] << lineWidgthRange[1];
////        m_axis->draw(viewMatrix);
//    }

    // ----------------------------------------------------------------

    ++m_cpt;
    update();
}
