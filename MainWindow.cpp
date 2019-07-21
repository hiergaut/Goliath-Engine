#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    openglWidget = new QOpenGLWidget_World(this);
    openglWidget->resize(ui->centralWidget->size());
    openglWidget->setFocus();
//    openglWidget->resize(openglWidget->sizeHint());


    setCentralWidget(openglWidget);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
