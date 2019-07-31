#include "MainWindowEditor.h"
#include "ui_MainWindowEditor.h"

#include "3dview/QOpenGLWidget_3dView.h"
#include "outliner/QTreeView_outliner.h"

#include <QOpenGLContext>
//#include <gui/editor/MainWindowEditor.h>
#include <fstream>
//#include <iostream>
#include <QDebug>

MainWindowEditor::MainWindowEditor(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowEditor)
{
    ui->setupUi(this);

    int rand1 = 100 + qrand() % 155;
    int rand2 = 100 + qrand() % 155;
    int rand3 = 100 + qrand() % 155;
    setStyleSheet(QString("background-color: rgb(%1,%2,%3);").arg(rand1).arg(rand2).arg(rand3));

    //    setCentralWidget()
    //    QWidget * widget = new QWidget;
    //    QOpenGLWidget_3dView * widget = new QOpenGLWidget_3dView;

    //    setEditor(VIEW);

    //    QTreeView_outliner * widget = new QTreeView_outliner;

    ////    centralWidget()->setFocus();
    ////    setFocus();
    ////    widget->setFocus();
    //    widget->setFocusPolicy(Qt::ClickFocus);
    ////    widget->setFocus();
    ////    connect(widget, &QWidget::, this, &MainWindowEditor::keyPressEvent);


    //    setCentralWidget(widget);
}

MainWindowEditor::~MainWindowEditor()
{
    delete ui;
    delete centralWidget();
}

void MainWindowEditor::setEditor(WidgetEditorId id)
{
//    QOpenGLContext* ctx = QOpenGLContext::currentContext();
//    qDebug() << "[CONTEXT] Editor : " << ctx;

    QWidget* widget;
    switch (id) {
    case VIEW:
        widget = new QOpenGLWidget_3dView;
        break;

    case OUTLINER:
        widget = new QTreeView_outliner;
        break;
    }
    widget->setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(widget);
    m_id = id;
}

void MainWindowEditor::save(std::ofstream& file)
{
    //        WidgetEditorId id = static_cast<MainWindowEditor*>(widget(0))->id();
    file.write(reinterpret_cast<const char*>(&m_id), sizeof(m_id));
//    qDebug() << "save " << m_id;
    return;
}

void MainWindowEditor::load(std::ifstream& file)
{
//        WidgetEditorId id;
        file.read(reinterpret_cast<char*>(&m_id), sizeof (m_id));
//        MainWindowEditor * w = new MainWindowEditor;
//        w->load(file);
        setEditor(m_id);
//        addWidget(w);
//        qDebug() << "load " << m_id;
}

void MainWindowEditor::keyPressEvent(QKeyEvent*)
{
    qDebug() << this << ": keyPressEvent";
}

void MainWindowEditor::focusInEvent(QFocusEvent*)
{
    qDebug() << this << ": focusInEvent";
}

void MainWindowEditor::on_action3D_View_triggered()
{
    setEditor(VIEW);
    //    QOpenGLWidget_3dView * widget = new QOpenGLWidget_3dView;
    ////    centralWidget()->setFocus();
    ////    setFocus();
    ////    widget->setFocus();
    //    widget->setFocusPolicy(Qt::ClickFocus);

    //    setCentralWidget(widget);
}

void MainWindowEditor::on_actionOutliner_triggered()
{
    setEditor(OUTLINER);
    //    QTreeView_outliner * widget = new QTreeView_outliner;

    ////    centralWidget()->setFocus();
    ////    setFocus();
    ////    widget->setFocus();
    //    widget->setFocusPolicy(Qt::ClickFocus);

    //    setCentralWidget(widget);
}

WidgetEditorId MainWindowEditor::id() const
{
    return m_id;
}
