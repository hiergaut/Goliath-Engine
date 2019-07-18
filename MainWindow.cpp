#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->openGLWidget->setFocus();
//    setCentralWidget(ui->openGLWidget);
//    ui->openGLWidget->setAcceptDrops(true);
//    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
