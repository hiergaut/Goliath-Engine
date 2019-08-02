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
#include <opengl/OpenglContext.h>

//#include <opengl/version.h>
//#include <QOpenGLFunctionsCore>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->page_systemBrowser, &FormSystemBrowser::canceled, this, &MainWindow::on_systemBrowserCanceled);
    connect(ui->page_systemBrowser, &FormSystemBrowser::openned, this, &MainWindow::on_systemBrowserLoaded);

    editor = new QOpenGLWidget_Editor(centralWidget(), this);
    editor->setViews(&m_views);
    QOpenGLWidget_3dView::setViews(&m_views);


    QSplitterNode* node = new QSplitterNode(ui->page_splitterRoot);
    //        QWidgetTemplate * w = new QWidgetTemplate;
    MainWindowEditor* w = new MainWindowEditor;
    w->setEditor(Editor::id::VIEW);
    //        w->setEditor(VIEW);
    node->addWidget(w);
    //        setCentralWidget(ui->page_splitterRoot);
    ui->page_splitterRoot->addWidget(node);

    //    g_env.m_scene.initialize();
    //    loadEnv("temp.dat");
}

MainWindow::~MainWindow()
{
    delete ui;
    //    delete m_splitterRoot;
}

void MainWindow::loadEnv(std::string filename)
{

    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        //        exit(1);
    } else {
        ui->stackedWidget->removeWidget(ui->page_splitterRoot);
        delete ui->page_splitterRoot;
        ui->page_splitterRoot = new QSplitterNode(ui->stackedWidget);
        ui->page_splitterRoot->load(file);
        ui->stackedWidget->addWidget(ui->page_splitterRoot);
        ui->stackedWidget->setCurrentWidget(ui->page_splitterRoot);

        //        g_env.load(file);
        editor->load(file);
        file.close();
    }

    //        ui->page_splitterRoot->setParent(ui->stackedWidget);

}

void MainWindow::saveEnv(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        exit(1);
    }
    ui->page_splitterRoot->save(file);
    //    g_env.save(file);
    editor->save(file);
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

void MainWindow::keyPressEvent(QKeyEvent* ev)
{
    //    qDebug() << this << ": keyPressEvent";

    switch (ev->key()) {
    case Qt::Key_Escape:
        //        loadFile("temp.dat");
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

    //    qDebug() << ui->centralWidget->size();
    editor->resize(ui->centralWidget->width(), ui->centralWidget->height());
}

void MainWindow::on_actionQuit_triggered()
{
    //    ui->splitter_root->saveSetting();
    //    std::cout << std::flush;
    QCoreApplication::quit();
}

void MainWindow::on_actionSave_As_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
    loadEnv("temp.dat");
}

void MainWindow::on_actionLoad_Factory_Settings_triggered()
{
    //    loadEnv("factory.dat");
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
    saveEnv("temp.dat");
}

//std::list<const QOpenGLWidget_3dView *> MainWindow::views() const
//{
//    return m_views;
//}
