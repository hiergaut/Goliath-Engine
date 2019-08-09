#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QTextEdit>
//#include <QSplitterHandle>
//#include <QMetaType>
//#include <Gui/TillingWindow/QSplitterNode.h>

//#include <QVariant>
//#include <engine/Environment.h>
//#include <opengl/version.h>
//#include <QOpengl
//Q_DECLARE_METATYPE(QList<QList<int>>);
//Q_DECLARE_METATYPE(Qt::Orientation);
#include <QSurface>
#include <fstream>
//#include <iostream>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <iostream>

#include <QLayout>
#include <QThread>
#include <gui/editor/MainWindowEditor.h>
//#include <opengl/OpenglContext.h>

//#include <opengl/version.h>
//#include <QOpenGLFunctionsCore>
//#include <gui/editor/fileOpenned/QListView_FileOpenned.h>



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->page_systemBrowser, &FormSystemBrowser::canceled, this, &MainWindow::on_systemBrowserCanceled);
    connect(ui->page_systemBrowser, &FormSystemBrowser::openned, this, &MainWindow::on_systemBrowserLoaded);

    m_views = new std::list<const QOpenGLWidget_3dView*>;
    QOpenGLWidget_3dView::setViews(m_views);

    editor = new QOpenGLWidget_Editor(centralWidget(), this);
    editor->setViews(m_views);

//    QListView_FileOpenned::setModelFileOpenned(&m_fileOpennedModel);

    //        ui->page_splitterRoot->load(file);
    MainWindowEditor* w = new MainWindowEditor;
    //    qDebug() << "[mainApplication] create mainWindowEditor" << w;
    w->setEditor(Editor::id::VIEW);
    //        w->setEditor(VIEW);
    //    node->addWidget(w);
    //        setCentralWidget(ui->page_splitterRoot);
    //    ui->page_splitterRoot->addWidget(node);
    ui->page_splitterRoot->addWidget(w);

    //    on_actionLoad_Factory_Settings_triggered();
    //    loadLastSession();
//    saveEnv("factory.dat");
}

MainWindow::~MainWindow()
{
    delete editor;
    delete ui;
    //    delete m_views;
    //    delete m_splitterRoot;
}

void MainWindow::loadEnv(std::string filename)
{

    //    std::cout << *ui->page_splitterRoot;

    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        //        exit(1);
    } else {
        ui->stackedWidget->removeWidget(ui->page_splitterRoot);
        delete ui->page_splitterRoot;
        //        ui->page_splitterRoot = new QSplitterNode(ui->stackedWidget);
        ui->page_splitterRoot = new QSplitterNode;
        //        QSplitterNode * node = new QSplitterNode;
        //        node->load(file);
        ui->page_splitterRoot->load(file);
        ui->stackedWidget->addWidget(ui->page_splitterRoot);
        ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);

        //        g_env.load(file);
//        editor->clear();
        editor->load(file);
//        m_fileOpennedModel.load(file);

        file.close();
    }

    //        ui->page_splitterRoot->setParent(ui->stackedWidget);
}

void MainWindow::saveEnv(std::string filename)
{
    //    std::cout << *ui->page_splitterRoot;
    //    const CameraWorld * camera = static_cast<QOpenGLWidget_3dView*>(static_cast<MainWindowEditor*>(ui->page_splitterRoot->widget(0))->centralWidget())->camera();
    //    const CameraWorld * camera2 = m_views.front()->camera();
    //    Q_ASSERT(camera == camera2);
    //    for (const QOpenGLWidget_3dView * view : m_views) {

    //        const CameraWorld * camera = view->camera();
    //        qDebug() << camera;

    //    }
    std::ofstream file;
    file.open(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        exit(1);
    }
    ui->page_splitterRoot->save(file);
    //    g_env.save(file);
    editor->save(file);
//    m_fileOpennedModel.save(file);

    file.close();
}

void MainWindow::showSystemBrowser()
{

    //    setCentralWidget(&m_systemBrowser);
    editor->hide();
    ui->stackedWidget->setCurrentWidget(ui->page_systemBrowser);
    //    centralWidget() = &m_systemBrowser;
}

void MainWindow::showEditors()
{
    editor->show();
    ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);
    editor->update();
}

void MainWindow::loadLastSession()
{
    loadEnv("temp.dat");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("maps/de_aztec/de_aztec.obj");
    editor->loadNewModel("models/player/gign/gign.fbx");
}

void MainWindow::saveSession()
{
    saveEnv("temp.dat");
}

void MainWindow::keyPressEvent(QKeyEvent* ev)
{
    //    qDebug() << this << ": keyPressEvent";

    switch (ev->key()) {
    case Qt::Key_Escape:
        //        loadFile("temp.dat");
        //        std::cout << *ui->page_splitterRoot;
        showEditors();
        break;
    }
    //    ev->ignore();
}

//void MainWindow::focusInEvent(QFocusEvent*)
//{
//    qDebug() << this << ": focusInEvent";
//}

void MainWindow::resizeEvent(QResizeEvent* ev)
{
    //    qDebug() << "[MAIN APPLICATION] : resizeEvent" << ev;
    //        qDebug() << "[MainApplication]" << QWidget::mapToGlobal(ui->stackedWidget->pos());

    //    qDebug() << ui->centralWidget->size();
    editor->resize(ui->centralWidget->width(), ui->centralWidget->height());
}

void MainWindow::on_actionQuit_triggered()
{
//    saveSession();
    //    ui->splitter_root->saveSetting();
    //    std::cout << std::flush;
    QCoreApplication::quit();
}

void MainWindow::on_actionSave_As_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
    loadLastSession();
    //    loadEnv("temp.dat");
}

void MainWindow::on_actionLoad_Factory_Settings_triggered()
{
    loadEnv("factory.dat");
}

void MainWindow::on_actionSave_Startup_File_triggered()
{
    //    saveEnv("startup.dat");
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
    showEditors();

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
    showEditors();
    editor->loadNewModel(filename.toStdString());

    //    g_env.m_scene.push_back(model);
}

void MainWindow::on_actionSave_triggered()
{
    saveSession();
    //    saveEnv("temp.dat");
}

//std::list<const QOpenGLWidget_3dView *> MainWindow::views() const
//{
//    return m_views;
//}
