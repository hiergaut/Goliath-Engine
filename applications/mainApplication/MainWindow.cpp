#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QTextEdit>
//#include <QSplitterHandle>
//#include <QMetaType>
//#include <Gui/TillingWindow/QSplitterNode.h>

//#include <QVariant>
#include <engine/Environment.h>
#include <opengl/version.h>
//#include <QOpengl
//Q_DECLARE_METATYPE(QList<QList<int>>);
//Q_DECLARE_METATYPE(Qt::Orientation);
#include <QSurface>
#include <fstream>
//#include <iostream>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <iostream>

#include <opengl/OpenglContext.h>
#include <QLayout>
#include <QThread>

//#include <opengl/version.h>
//#include <QOpenGLFunctionsCore>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//        QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    //    QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>()->initializeOpenGLFunctions();

    //    qRegisterMetaTypeStreamOperators<QList<int>>("QList<int>");
    //    qRegisterMetaTypeStreamOperators<Qt::Orientation>("Qt::Orientation");
    //    QOpenGLContext context

    //    QSurfaceFormat format;
    //    format.setVersion(3, 3);
    //    format.setProfile(QSurfaceFormat::CoreProfile);
    //    format.setDepthBufferSize(24);
    //    format.setSamples(4);
    //    QSurfaceFormat::setDefaultFormat(format);

    //    QOpenGLContext * context = new QOpenGLContext(this);
    //    context->setFormat(format);
    //    if (!context->create())
    //        throw std::runtime_error("context creation failed");

    //    QOpenGLContext::create(this);
    //    QOpenGLFunctionsCore* fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    fun = new QOpenGLFunctionsCore;
    //    fun->initializeOpenGLFunctions();
    //    fun->initializeOpenGLFunctions();
    //    QOpenGLFunctions * fun = context.functions();
    //    fun->initializeOpenGLFunctions();

    //    QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    fun->initializeOpenGLFunctions();

    //    g_context = context;
    //    g_fun = fun;

    //    QOpenGLContext * c = context();

    //    QOpenGLContext::th
    //        throw std::runtime_error("failed to initialize opengl functions");

    //    initializeOpenGLFunctions();

    ui->setupUi(this);


//    QOpenGLContext* ctx = QOpenGLContext::currentContext();
//    QOpenGLContext * ctx = QOpenGLContext::globalShareContext();
//    qDebug() << "[CONTEXT] mainWindow : " << ctx;

    //    QOpenGLFunctionsCore * fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //    qDebug() << this << fun;

//    connect(ui->page_systemBrowser, &FormSystemBrowser::canceled, this, &MainWindow::on_systemBrowserCanceled);
//    connect(ui->page_systemBrowser, &FormSystemBrowser::openned, this, &MainWindow::on_systemBrowserLoaded);

    //    ui->splitter_root->setup();
    //    ui->splitter_root->loadSetting();

    //    ui->splitter_root->setParent(ui->splitter_root);
    //    g_env.m_splitterRoot = &ui->splitter_root;
    //    m_splitterRoot = new QSplitterNode;
    //    g_env.m_splitterRoot = &m_splitterRoot;

    g_env.m_splitterRoot = &ui->page_splitterRoot;


    editor = new QOpenGLWidget_Editor(centralWidget());

//    g_env.m_views = editor->views();
//    ui->stackedWidget->addWidget(new QOpenGLWidget_3dView(this));
    //    ui->stackedWidget->addWidget(&m_splitterRoot);

    //    g_env.m_splitterRoot = ui->page;
    //    ui->page = m_splitterRoot;
    //    ui->page_2 = &m_systemBrowser;

    //    g_env.m_splitterRoot = &ui->page;
    //    g_env.m_splitterRoot = &ui->page;
    //    ui->stackedWidget->setCurrentIndex(2);

    loadFile("temp.dat");

    //    m_splitterRoot = new QSplitterNode;
    //    QSplitterNode * node = new QSplitterNode(m_splitterRoot);
    //    MainWindowEditor * w = new widgetTemplate;
    //    w->setEditor(VIEW);
    //    node->addWidget(w);

    //    setCentralWidget(m_splitterRoot);

    //    m_splitterRoot->addWidget(node);

    //    QSplitterNode * node2 = new QSplitterNode(node);
    //    node->addWidget(new widgetTemplate);
    //    QWidget * w = new widgetTemplate;
    //    node->addWidget(node2);

    //    m_splitterRoot->setParent(nullptr);
    //    qDebug() << m_splitterRoot->parent();

    //    m_splitterRoot->addWidget(new widgetTemplate);
    //    g_env.m_splitterRoot = *m_splitterRoot;

    //    *m_splitterRoot = new QSplitterNode;
    //    *m_splitterRoot.addWidget(new temp);

    //    ui->splitter_root->setup();
    //    std::cout << "load splitter root : " << std::endl;
    //    std::cout << *ui->splitter_root;
    //    std::cout << *m_splitterRoot;

    //    ui->splitter_root->loadSetting();
    //    ui->splitter_root->loadEnv();

    //    ui->splitter_root->setFocus();
    //    setCentralWidget(ui->splitter_root);

    //    QTextEdit * editor1 = new QTextEdit;
    //    QTextEdit * editor2 = new QTextEdit;
    //    QTextEdit * editor3 = new QTextEdit;

    ////    splitter = new QSplitter(Qt::Horizontal);
    //    splitter = new QSplitter(Qt::Vertical);
    //    splitter->addWidget(editor1);
    //    splitter->addWidget(editor2);
    //    splitter->addWidget(editor3);

    //    node = new QSplitterNode;

//    qDebug() << "[mainWindow][SHARED CONTEXT]" << QOpenGLContext::globalShareContext()->functions();

    //    setCentralWidget(splitter);

    //    openglWidget = new QOpenGLWidget_World(this);
    //    openglWidget->resize(ui->centralWidget->size());
    //    openglWidget->setFocus();

    //    openglWidget->resize(openglWidget->sizeHint());

    //    setCentralWidget(openglWidget);

    //    ui->openGLWidget->setFocus();

    //    setCentralWidget(ui->openGLWidget);
    //    ui->openGLWidget->setAcceptDrops(true);
    //    setAcceptDrops(true);
    //    QGLFormat glFormat;
    //      glFormat.setSampleBuffers(true);
    //      glFormat.setSamples(4);

    //      widget = new GLWidget(glFormat, ui->centralWidget);
    //      widget->setObjectName(QStringLiteral("widget"));
    //      ui->horizontalLayout->addWidget(widget);
//    centralWidget() = new QHBoxLayout(this);
//    Model model(g_resourcesPath + filename.toStdString());

//    view = new QOpenGLWidget_3dView(this);
//    ui->stackedWidget->addWidget(view);
//    QHBoxLayout * layout = new QHBoxLayout(this);
//    QWidget * layout = new QWidget(this);
//    layout->addWidget(view);

//    ui->stackedWidget->addWidget(layout);
//    ui->stackedWidget->setCurrentWidget(view);
//    view->setFocusPolicy(Qt::ClickFocus);

//    ui->horizontalLayout_2->addWidget(view);

//    g_env.add3dView(view);


//    g_env.addModel(g_resourcesPath + "maps/de_aztec/de_aztec.obj");

//    view2 = new QOpenGLWidget_3dView(this);
//    ui->horizontalLayout_2->addWidget(view2);

//    g_env.add3dView(view2);

//    QOpenGLContext::globalShareContext()->create();
//    view2->context()->create();
//    view2->context()->setShareContext(QOpenGLContext::globalShareContext());


//    QOpenGLWidget_3dView * view3 = new QOpenGLWidget_3dView(view);
//    ui->horizontalLayout_2->addWidget(view3);

//    qDebug() << QApplication::instance()->thread();
//    qDebug() << "[mainWindow][Thread] " << QThread::currentThreadId();


//    qDebug() << "[GROUP] view : " << view->context()->shareGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
    //    delete m_splitterRoot;
}

void MainWindow::loadFile(std::string filename)
{
//    qDebug() << "[CONTEXT] mainWindow loadFile : " << QOpenGLContext::globalShareContext();

//    QOpenGLContext* ctx = QOpenGLContext::currentContext();
//    qDebug() << "[CONTEXT] mainWindow loadFile : " << ctx;

//    ctx->setShareContext(g_openglContext->m_context);


//    ui->stackedWidget->removeWidget(ui->page_splitterRoot);

    //    qDebug() << "------------------------------ open conf ------------------------------";
    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        //        exit(1);
    } else {
        g_env.load(file);
        file.close();
    }

//        ui->page_splitterRoot->setParent(ui->stackedWidget);

    ui->stackedWidget->addWidget(ui->page_splitterRoot);
    ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);

    //    ui->page = m_splitterRoot;
    //    setCentralWidget(m_splitterRoot);

    //    for (auto pair : g_env.m_sizes.toStdMap()) {
    //        qDebug() << "pair : " << pair;
    //    }


//    editor->resize(ui->stackedWidget->size());
    editor->resize(500, 500);
//    setCentralWidget(editor);

    //    std::cout << "str : '" << g_env.str << "'" << std::endl;
    //    std::cout << g_env;

    //    ui->splitter_root->loadEnv();

    //    std::cout << "load splitter root : " << std::endl;
    //    std::cout << *m_splitterRoot;
    //    std::cout << "-------------------------------------------------------" << std::endl;
}

void MainWindow::saveFile(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        exit(1);
    }
    g_env.save(file);
    file.close();
}

void MainWindow::showSystemBrowser()
{
//    view->update();
//    Model*  model = new Model(g_resourcesPath + "maps/de_aztec/de_aztec.obj");
//    g_env.addModel(g_resourcesPath + "maps/de_aztec/de_aztec.obj");
//    g_env.m_scene.push_back(model);
//    view->setScene(model);
//    view2->setScene(model);

//    qDebug() << QThread::currentThreadId() << "[MainWindow][CONTEXT]" << QOpenGLContext::currentContext()->functions();
//    qDebug() << "[MainWindow][GROUP]" << QOpenGLContext::currentContext()->shareGroup()->shares().size();
//    for (const auto & ctx : QOpenGLContext::currentContext()->shareGroup()->shares()) {
//        qDebug() << "\t" << ctx->functions();
//    }

    //    setCentralWidget(&m_systemBrowser);
    ui->stackedWidget->setCurrentWidget(ui->page_systemBrowser);
    //    centralWidget() = &m_systemBrowser;
}

void MainWindow::keyPressEvent(QKeyEvent* ev)
{
    qDebug() << this << ": keyPressEvent";

    switch (ev->key()) {
    case Qt::Key_Escape:
//        loadFile("temp.dat");
        //            ui->stackedWidget->setCurrentWidget(&m_splitterRoot);
        ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);
        //            ui->stackedWidget->setCurrentIndex(ui->page);
        //            setCentralWidget(m_splitterRoot);
        //        QOpenGLContext * ctx = QOpenGLContext::currentContext();
//        QOpenGLContext* ctx = QOpenGLContext::currentContext();
//        qDebug() << "[CONTEXT] mainWindow loadFile : " << ctx->functions();


        //        qDebug() << "[CONTEXT] mainWindow : " << ctx;
//    qDebug() << "[CONTEXT] mainWindow : " << QOpenGLContext::currentContext()->functions();

//        QOpenGLFunctionsCore* fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//        qDebug() << "[CONTEXT] mainWindow : " << fun;
        break;
    }
    //    ev->ignore();
}

void MainWindow::focusInEvent(QFocusEvent*)
{
    qDebug() << this << ": focusInEvent";
}

void MainWindow::on_actionQuit_triggered()
{
    //    ui->splitter_root->saveSetting();
    //    std::cout << std::flush;
    QCoreApplication::quit();
}

void MainWindow::on_actionSave_As_triggered()
{
    //    qDebug() << "----------------------- save conf ----------------------------------";
    //    g_env.clear();
    //    std::cout << "save splitter root : " << std::endl;
    //    std::cout << *m_splitterRoot;
    //    std::cout << "-------------------------------------------------------" << std::endl;

    //    ui->splitter_root->saveEnv();
    //        qDebug() << &g_env;
    //    g_env.m_sizes["fuck"] = QList<int>({1, 2});

    //    qDebug() << g_env.m_sizes["root"];
    //    qDebug() << g_env.m_sizes.count();
    //    for (auto pair : g_env.m_sizes.toStdMap()) {
    //        qDebug() << "pair : " << pair;
    //    }
//    saveFile("current.dat");

    //    file.open("temp.dat", std::t
    //    file.write(&g_env, sizeof(&g_env));

    //    std::cout << g_env;
    //    std::cout << "str : '" << g_env.str << "'" << std::endl;
    //    g_env.save();
}

void MainWindow::on_actionOpen_triggered()
{
//    loadFile("temp.dat");

    //    //    qDebug() << "------------------------------ open conf ------------------------------";
    //    std::ifstream file;
    //    file.open("temp.dat", std::ios::binary | std::ios::in);
    //    if (!file.is_open()) {
    //        std::cerr << "cannot open file" << std::endl;
    //        //        exit(1);
    //    } else {
    //        g_env.load(file);
    //        file.close();
    //    }
//        setCentralWidget(m_splitterRoot);

    //    //    for (auto pair : g_env.m_sizes.toStdMap()) {
    //    //        qDebug() << "pair : " << pair;
    //    //    }

    //    //    std::cout << "str : '" << g_env.str << "'" << std::endl;
    //    //    std::cout << g_env;

    //    //    ui->splitter_root->loadEnv();

    //    std::cout << "load splitter root : " << std::endl;
    //    std::cout << *m_splitterRoot;
    //    std::cout << "-------------------------------------------------------" << std::endl;
}

void MainWindow::on_actionLoad_Factory_Settings_triggered()
{
//    loadFile("factory.dat");
}

void MainWindow::on_actionSave_Startup_File_triggered()
{
//    saveFile("startup.dat");
}

void MainWindow::on_actionNew_triggered()
{
}

void MainWindow::on_actionImport_triggered()
{
    //    qDebug() << m_splitterRoot;
    showSystemBrowser();
    //    qDebug() << m_splitterRoot;
}

void MainWindow::on_systemBrowserCanceled()
{
//    ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);
//    ui->stackedWidget->setCurrentWidget()
//    ui->stackedWidget->setCurrentWidget(view);
}

void MainWindow::on_systemBrowserLoaded(QString filename)
{
//    ui->stackedWidget->setCurrentWidget(view);
//    ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);

//    qDebug() << QThread::currentThreadId() << "[MainWindow][CONTEXT]" << QOpenGLContext::currentContext()->functions();
//    Model model(g_resourcesPath + filename.toStdString());

//    g_env.m_scene.push_back(model);
}
