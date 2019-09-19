#include "MainWindowEditor.h"
#include "ui_MainWindowEditor.h"

#include "3dview/MainWindow3dView.h"
#include "outliner/QTreeView_outliner.h"

#include <QOpenGLContext>
//#include <gui/editor/MainWindowEditor.h>
#include <fstream>
//#include <iostream>
#include <QDebug>
//#include <engine/Environment.h>
//#include "fileOpenned/QListView_FileOpenned.h"
#include "properties/MainWindowProperties.h"
//#include <QThread>
//#include <QTime>
#include <QDateTime>
//#include <AnimTimeline/FormAnimTimeline.h>
#include "timeline/FormTimeline.h"
//#include <gui/QOpenGLWidget_Editor.h>

MainWindowEditor::MainWindowEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowEditor)
{
    ui->setupUi(this);

//    auto time = QTime::currentTime().msec();

    qsrand(QDateTime::currentMSecsSinceEpoch());
//    int rand1 =  64 + qrand() % 128;
//    int rand2 =  64 + qrand() % 128;
//    int rand3 =  64 + qrand() % 128;
    int rand1 =  qrand() % 128;
    int rand2 =  qrand() % 128;
    int rand3 =  qrand() % 128;
//    int rand1 = qrand() % 155;
//    int rand2 = qrand() % 155;
//    int rand3 = qrand() % 155;
    setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

//    setStyleSheet("background-color: black;");

    //    setCentralWidget(widget);
//    qDebug() << "[MainWindowEditor]" << this << "created";
//    *m_defaultMenuBar = *ui->menubar;
//    *m_defaultMenuBar = std::move(*(ui->menubar));
//    connect(ui->menubar, &QMenuBar::mousePressEvent, this, &MainWindowEditor::mousePressEvent);

}

MainWindowEditor::~MainWindowEditor()
{
//    qDebug() << "[MainWindowEditor]" << this << "deleted";
    delete m_centralWidget;
    //    delete centralWidget();
    delete ui;
}

void MainWindowEditor::setEditor(Editor::id id)
{
    //    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    //    qDebug() << "[CONTEXT] Editor : " << ctx;
    if (m_centralWidget != nullptr)
        delete m_centralWidget;


//    QOpenGLWidget_Editor::m_editor->

//    for (QMenu * menu : m_menus) {
//        ui->menubar.d
//    }
//    m_menus.clear();
//    QMenu * menu;

//    bar->addMenu(menu);

//    bar->resize(10, 10);

    //    QWidget* widget;
    switch (id) {
    case Editor::id::VIEW:
        m_centralWidget = new MainWindow3dView;
        ui->menuEditor_Type->setIcon(ui->action3D_View->icon());
        ui->menuEditor_Type_2->setTitle("3dView");
//        m_menus.push_back(menu);
//        ui->menubar->addMenu(menu);
//        menu->setParent(ui->menubar);
//        for (QMenu & menu : m_centralWidget->menus()) {
//        qDebug() << menu.title();
//        }
        break;

    case Editor::id::OUTLINER:
//        int rand1 = qrand() % 155;
//        int rand2 = qrand() % 155;
//        int rand3 = qrand() % 155;
//        setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(qrand() % 127 + 127).arg(qrand() % 127 + 127).arg(qrand() % 127 + 127));

        m_centralWidget = new QTreeView_outliner;
        ui->menuEditor_Type->setIcon(ui->actionOutliner->icon());
        ui->menuEditor_Type_2->setTitle("Outliner");
        break;

//    case Editor::id::FILE_OPENNED:
//        m_centralWidget = new QListView_FileOpenned;
//        break;

    case Editor::id::PROPERTIES:
//        MainWindowProperties * widget = new MainWindowProperties;
//        widget->setContext(Properties::e_context::MATERIAL);
        m_centralWidget = new MainWindowProperties;
        static_cast<MainWindowProperties*>(m_centralWidget)->setContext(Properties::e_context::MATERIAL);
        ui->menuEditor_Type->setIcon(ui->actionProperties->icon());
        ui->menuEditor_Type_2->setTitle("Properties");
        break;

    case Editor::id::TIMELINE:
        m_centralWidget = new FormTimeline;
        ui->menuEditor_Type->setIcon(ui->actionTimeline->icon());
        ui->menuEditor_Type_2->setTitle("Timeline");
        break;


    default:
        Q_ASSERT(false);
    }

//    for (QMenu * menu : m_menus) {
//        ui->menubar->addMenu(menu);
//    }
//    QMenuBar * bar = new QMenuBar(this);
    ui->menubar->clear();
//    bar->setStyleSheet(ui->menubar->styleSheet());
    ui->menubar->addMenu(ui->menuEditor_Type);
    ui->menubar->addMenu(ui->menuEditor_Type_2);

    for (QMenu * menu : m_centralWidget->menus()) {
//        qDebug() << "add menu " << &menu;
        ui->menubar->addMenu(menu);
    }

//    this->setMenuBar(bar);


    m_centralWidget->setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(m_centralWidget->widget());
    m_id = id;
//    ui->menuEditor_Type->setTitle(text());
}

void MainWindowEditor::save(std::ofstream& file)
{
        Q_ASSERT(m_centralWidget != nullptr);
//    qDebug() << "[MainWindowEditor]" << this << "save";
    //        Editor::id id = static_cast<MainWindowEditor*>(widget(0))->id();
    file.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
    switch (m_id) {
    case Editor::id::VIEW:
        static_cast<MainWindow3dView*>(m_centralWidget)->save(file);
        break;

    case Editor::id::OUTLINER:
        break;

//    case Editor::id::FILE_OPENNED:
//        break;

    case Editor::id::PROPERTIES:
        break;

    case Editor::id::TIMELINE:
        break;

    default:
        Q_ASSERT(false);
    }
    //    qDebug() << "save " << m_id;
    //    return;
}

void MainWindowEditor::load(std::ifstream& file)
{
    //        Editor::id id;
    file.read(reinterpret_cast<char*>(&m_id), sizeof(m_id));
    //        MainWindowEditor * w = new MainWindowEditor;
    //        w->load(file);
    setEditor(m_id);
    //        addWidget(w);
    //        qDebug() << "load " << m_id;
    switch (m_id) {
    case Editor::id::VIEW:
        static_cast<MainWindow3dView*>(m_centralWidget)->load(file);
        break;

    case Editor::id::OUTLINER:
        break;

//    case Editor::id::FILE_OPENNED:
//        break;

    case Editor::id::PROPERTIES:
//        static_cast<MainWindowProperties*>(centralWidget())->setContext(Properties::e_context::MATERIAL);
        break;

    case Editor::id::TIMELINE:
//        static_cast<FormAnimTimeline*>(m_centralWidget)->;
        break;

    default:
        Q_ASSERT(false);
    }
    //    qDebug() << "save " << m_id;
    //    return;
}

//QString MainWindowEditor::text()
//{
//    switch (m_id) {
//    case Editor::VIEW:
//        return "3dView";

//    case Editor::OUTLINER:
//        return "Outliner";

////    case Editor::id::FILE_OPENNED:
////        return "File Openned";

//    case Editor::id::PROPERTIES:
//        return "Properties";

//    default:
//        Q_ASSERT(false);
//    }

//}

void MainWindowEditor::keyPressEvent(QKeyEvent*)
{
    //    qDebug() << this << ": keyPressEvent";
}

void MainWindowEditor::focusInEvent(QFocusEvent*)
{
    //    qDebug() << this << ": focusInEvent";
}

void MainWindowEditor::on_action3D_View_triggered()
{
    //    if (m_id == VIEW) {
    ////        g_env.m_views.remov
    //    }
//    delete m_centralWidget;
//    m_centralWidget = nullptr;
//    Scene::m_scene->removeNoViewCamera();
    setEditor(Editor::id::VIEW);
}

void MainWindowEditor::on_actionOutliner_triggered()
{
    setEditor(Editor::id::OUTLINER);
//    Scene::m_scene->removeHideCamera();
}

//QWidget* MainWindowEditor::centralWidget()
//{
//    return m_centralWidget;
//}

//Editor::id MainWindowEditor::id() const
//{
//    return m_id;
//}

//void MainWindowEditor::on_actionFile_Openned_triggered()
//{
//    setEditor(Editor::id::FILE_OPENNED);
//}

void MainWindowEditor::on_actionProperties_triggered()
{
    setEditor(Editor::id::PROPERTIES);
//    ui->menuEditor_Type->setIcon(ui->action3D_View->icon());
//    ui->menuEditor_Icon->setIcon(ui->action3D_View->icon());
}

void MainWindowEditor::on_actionTimeline_triggered()
{
    setEditor(Editor::id::TIMELINE);

}
