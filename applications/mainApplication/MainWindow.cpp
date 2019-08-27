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
#include <QStringListModel>
//#include <QItemSelectionModel>
#include <QInputDialog>

//#include <opengl/version.h>
//#include <QOpenGLFunctionsCore>
//#include <gui/editor/fileOpenned/QListView_FileOpenned.h>

const QString opennedFile = "opennedFile";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings("Goliath-Engine", opennedFile)
    , m_dialogInput(this)
{

    ui->setupUi(this);

    connect(ui->page_systemBrowser, &FormSystemBrowser::canceled, this, &MainWindow::on_systemBrowserCanceled);
    connect(ui->page_systemBrowser, &FormSystemBrowser::openned, this, &MainWindow::on_systemBrowserLoaded);
    connect(ui->page_systemBrowser, &FormSystemBrowser::saved, this, &MainWindow::on_systemBrowserSaved);
    connect(ui->page_systemBrowser, &FormSystemBrowser::imported, this, &MainWindow::on_systemBrowserImported);

    m_views = new std::list<const MainWindow3dView*>;
    MainWindow3dView::setViews(m_views);

    editor = new QOpenGLWidget_Editor(centralWidget(), this);
    editor->setViews(m_views);
    editor->setStatusBar(ui->statusBar);

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
//    saveEnv(g_resourcesPath + "dat/factory.dat");

    //    loadNewSession();
    setFocus();

    m_previousEnv = new QStringListModel(this);
    QStringList previous = m_settings.value(opennedFile).value<QStringList>();
    m_previousEnv->setStringList(previous);

    m_dialogInput.setModel(m_previousEnv);
    connect(&m_dialogInput, &DialogInputGetItem::openEnv, this, &MainWindow::on_dialogOpenPrevious);
    //    connect(m_previousEnv, &QStringListModel::layoutChanged, &m_dialogInput, &DialogInputGetItem::on_dataChange);
    //    m_dialogInput.show();
}

MainWindow::~MainWindow()
{
    delete m_previousEnv;
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
        exit(1);
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

        //        ui->page_splitterRoot->setFocus();

        //        g_env.load(file);
        //        editor->clear();
        editor->load(file);
        //        m_fileOpennedModel.load(file);

        file.close();
    }

    //    ui->me
    //    m_currentEnvFile = filename.c_str();
    ui->menuCurrentEnvFile->setTitle(filename.c_str());
    //        ui->page_splitterRoot->setParent(ui->stackedWidget);
    setFocus();

    previousEnvAdd(filename);
}

void MainWindow::saveEnv(std::string filename)
{
    //    std::cout << *ui->page_splitterRoot;
    //    const CameraWorld * camera = static_cast<MainWindow3dView*>(static_cast<MainWindowEditor*>(ui->page_splitterRoot->widget(0))->centralWidget())->camera();
    //    const CameraWorld * camera2 = m_views.front()->camera();
    //    Q_ASSERT(camera == camera2);
    //    for (const MainWindow3dView * view : m_views) {

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

    ui->menuCurrentEnvFile->setTitle(filename.c_str());
    //        ui->page_splitterRoot->setParent(ui->stackedWidget);
    setFocus();

    previousEnvAdd(filename);
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

//void MainWindow::loadLastSession()
//{
//    loadEnv("temp.dat");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("models/camera/camera.obj");
//    editor->loadNewModel("maps/de_aztec/de_aztec.obj");
//    editor->loadNewModel("models/player/gign/gign.fbx");
//    editor->loadNewModel("models/Dana.fbx");
//}

//void MainWindow::saveSession()
//{
//    saveEnv("temp.dat");
//}

void MainWindow::loadLastSession() // call by main
{
    if (m_previousEnv->rowCount() > 0) {
        loadEnv(m_previousEnv->index(0).data().toString().toStdString());

    } else {
        QFileInfo file(m_settings.fileName());
        QDir dir(file.path());
        m_startupPath = (file.path() + "/startup.dat").toStdString();

        //    std::string startupFile = file.path().toStdString() + "/startup.dat";
        QFile startupFile(file.path() + "/startup.dat");

        if (startupFile.exists()) {
            //        QDir::mkpath(dir.path());
            //        dir.mkpath(".");
            loadEnv(startupFile.fileName().toStdString());
        } else {
//            loadEnv(g_resourcesPath + "dat/factory.dat");

            dir.mkpath(".");
            saveEnv(startupFile.fileName().toStdString());
        }
    }
}

void MainWindow::previousEnvAdd(std::string file)
{
//    if (file != m_startupPath && file != std::string(g_resourcesPath + "dat/factory.dat")) {
    if (file != m_startupPath) {
        //        qDebug() << "same " << filename.c_str() << m_startupPath.c_str();
        QStringList files = m_settings.value(opennedFile).value<QStringList>();
        //    QString file = ui->lineEdit_currentPath->text();
        if (!files.contains(file.c_str())) {
            //            files += file.c_str();
            files.insert(0, file.c_str());

        } else {
            int idx = files.indexOf(file.c_str());
            files.move(idx, 0);
        }

        m_settings.setValue(::opennedFile, QVariant::fromValue(files));
        //    pullSettingsRecentModel();
        m_previousEnv->setStringList(files);
        //    m_previousEnv->layoutChanged();
    }
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

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    qDebug() << "fuck";

//}

void MainWindow::on_actionQuit_triggered()
{
    //    saveSession();
    //    ui->splitter_root->saveSetting();
    //    std::cout << std::flush;
    on_actionSave_triggered();
    QCoreApplication::quit();
}

void MainWindow::on_actionSave_As_triggered()
{
    //    ui->page_systemBrowser->setGoliathFilter();
    ui->page_systemBrowser->setMode(Mode::SAVE);
    showSystemBrowser();
}

void MainWindow::on_actionOpen_triggered()
{
    //    ui->page_systemBrowser->setGoliathFilter();
    ui->page_systemBrowser->setMode(Mode::OPEN);
    showSystemBrowser();

    //    loadLastSession();
    //    loadEnv("temp.dat");
}

void MainWindow::on_actionLoad_Factory_Settings_triggered()
{
    //    loadEnv("factory.dat");
//    loadEnv(g_resourcesPath + "dat/factory.dat");
}

void MainWindow::on_actionSave_Startup_File_triggered()
{
    //    saveEnv("factory.dat");
    //    saveEnv(g_resourcesPath + "dat/factory.dat");

    //    saveEnv("$PWD/.config/Goliath-Engine/startup.dat");
    //    qDebug() << QDir(m_settings.fileName());
    QFileInfo file(m_settings.fileName());
    QDir dir(file.path());
    if (!dir.exists()) {
        //        QDir::mkpath(dir.path());
        dir.mkpath(".");
    }
    saveEnv((file.path() + "/startup.dat").toStdString());
    //    qDebug() << file.path();
}

void MainWindow::on_actionNew_triggered()
{
    //    loadEnv("/home/gauthier/.config/Goliath-Engine/startup.dat");
    QFileInfo file(m_settings.fileName());
    loadEnv((file.path() + "/startup.dat").toStdString());
}

void MainWindow::on_actionImport_triggered()
{
    //    qDebug() << m_splitterRoot;
    //    ui->page_systemBrowser->setAssimpFilter();
    ui->page_systemBrowser->setMode(Mode::IMPORT);
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
    loadEnv(filename.toStdString());

    //    g_env.m_scene.push_back(model);
}

void MainWindow::on_systemBrowserSaved(QString file)
{

    showEditors();
    saveEnv(file.toStdString());
}

void MainWindow::on_systemBrowserImported(QString file)
{
    showEditors();
    editor->loadNewModel(file.toStdString());
}

void MainWindow::on_actionSave_triggered()
{
    saveEnv(ui->menuCurrentEnvFile->title().toStdString());

    //    saveSession();
    //    saveEnv("temp.dat");
}

//void MainWindow::on_setFps(float fps)
//{
//    ui->statusBar->showMessage(QString::number(fps));

//}

//std::list<const MainWindow3dView *> MainWindow::views() const
//{
//    return m_views;
//}

void MainWindow::on_actionOpen_Recent_triggered()
{
    //    for (QString str : m_previousEnv->stringList()) {
    //        qDebug() << str;
    //    }
    //    QInputDialog dialog;
    m_dialogInput.show();
    //    //    dialog.show();
    //    QStringList items = m_previousEnv->stringList();
    ////       items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

    //       bool ok;
    //       QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
    //                                            tr("Season:"), items, 0, false, &ok);
    //       if (ok && !item.isEmpty())
    //           qDebug() << item;
    ////           itemLabel->setText(item);

    //    bool ok;
    //    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
    //        tr("User name:"), QLineEdit::Normal,
    //        QDir::home().dirName(), &ok);

    //    if (ok && !text.isEmpty())
    //        qDebug() << text;
    //    //        textLabel->setText(text);
}

void MainWindow::on_dialogOpenPrevious(const QModelIndex& index)
{
    //    qDebug() << "openPrevious " << index.data().toString();

    m_dialogInput.hide();
    loadEnv(index.data().toString().toStdString());
}
