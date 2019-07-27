#include "MainWindowEditor.h"
#include "ui_MainWindowEditor.h"

#include "3dview/QOpenGLWidget_3dView.h"
#include "outliner/QTreeView_outliner.h"

//#include <gui/editor/MainWindowEditor.h>

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
    QTreeView_outliner * widget = new QTreeView_outliner;

    setCentralWidget(widget);
//    centralWidget()->setFocus();
//    setFocus();
//    widget->setFocus();
    widget->setFocusPolicy(Qt::ClickFocus);
//    widget->setFocus();
//    connect(widget, &QWidget::, this, &MainWindowEditor::keyPressEvent);



}

MainWindowEditor::~MainWindowEditor()
{
    delete ui;
}

void MainWindowEditor::keyPressEvent(QKeyEvent *)
{
    qDebug() << this << ": keyPressEvent";

}

void MainWindowEditor::focusInEvent(QFocusEvent *)
{
    qDebug() << this << ": focusInEvent";

}
