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

MainWindowEditor::MainWindowEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowEditor)
{
    ui->setupUi(this);

    int rand1 = 100 + qrand() % 155;
    int rand2 = 100 + qrand() % 155;
    int rand3 = 100 + qrand() % 155;
    setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    //    setCentralWidget(widget);
}

MainWindowEditor::~MainWindowEditor()
{
    delete m_centralWidget;
//    delete centralWidget();
    delete ui;
}

void MainWindowEditor::setEditor(Editor::id id)
{
    //    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    //    qDebug() << "[CONTEXT] Editor : " << ctx;

//    QWidget* widget;
    switch (id) {
    case Editor::id::VIEW:
        m_centralWidget = new QOpenGLWidget_3dView;
        break;

    case Editor::id::OUTLINER:
        m_centralWidget = new QTreeView_outliner;
        break;

    default:
        Q_ASSERT(false);
    }
    m_centralWidget->setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(m_centralWidget);
    m_id = id;
}

void MainWindowEditor::save(std::ofstream& file)
{
        qDebug() << "save " << this;
    //        Editor::id id = static_cast<MainWindowEditor*>(widget(0))->id();
    file.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
    switch (m_id) {
    case Editor::id::VIEW:
        static_cast<QOpenGLWidget_3dView*>(m_centralWidget)->save(file);
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

    default:
        Q_ASSERT(false);
    }
    //    qDebug() << "save " << m_id;
    //    return;
}

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

//Editor::id MainWindowEditor::id() const
//{
//    return m_id;
//}
