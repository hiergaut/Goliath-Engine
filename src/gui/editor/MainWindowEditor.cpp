#include "MainWindowEditor.h"
#include "ui_MainWindowEditor.h"

#include "3dview/QOpenGLWidget_3dView.h"
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

MainWindowEditor::MainWindowEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowEditor)
{
    ui->setupUi(this);

//    auto time = QTime::currentTime().msec();

    qsrand(QDateTime::currentMSecsSinceEpoch());
    int rand1 = 100 + qrand() % 155;
    int rand2 = 100 + qrand() % 155;
    int rand3 = 100 + qrand() % 155;
    setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    //    setCentralWidget(widget);
//    qDebug() << "[MainWindowEditor]" << this << "created";
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
    delete m_centralWidget;

    //    QWidget* widget;
    switch (id) {
    case Editor::id::VIEW:
        m_centralWidget = new QOpenGLWidget_3dView;
        ui->menuEditor_Type->setIcon(ui->action3D_View->icon());
        ui->menuEditor_Type_2->setTitle("3dView");
        break;

    case Editor::id::OUTLINER:
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

    default:
        Q_ASSERT(false);
    }


    m_centralWidget->setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(m_centralWidget);
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
        static_cast<QOpenGLWidget_3dView*>(m_centralWidget)->save(file);
        break;

    case Editor::id::OUTLINER:
        break;

//    case Editor::id::FILE_OPENNED:
//        break;

    case Editor::id::PROPERTIES:
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
        static_cast<QOpenGLWidget_3dView*>(m_centralWidget)->load(file);
        break;

    case Editor::id::OUTLINER:
        break;

//    case Editor::id::FILE_OPENNED:
//        break;

    case Editor::id::PROPERTIES:
//        static_cast<MainWindowProperties*>(centralWidget())->setContext(Properties::e_context::MATERIAL);
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
    setEditor(Editor::id::VIEW);
}

void MainWindowEditor::on_actionOutliner_triggered()
{
    setEditor(Editor::id::OUTLINER);
}

QWidget* MainWindowEditor::centralWidget()
{
    return m_centralWidget;
}

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
