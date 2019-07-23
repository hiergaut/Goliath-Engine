#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextEdit>
//#include <QSplitterHandle>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QSurfaceFormat format;
//    format.setVersion(3, 3);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setDepthBufferSize(24);
//    format.setSamples(4);
//    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

//    ui->splitter_root->setup();
//    ui->splitter_root->loadSetting();
    ui->splitter_root->setup();


//    QTextEdit * editor1 = new QTextEdit;
//    QTextEdit * editor2 = new QTextEdit;
//    QTextEdit * editor3 = new QTextEdit;

////    splitter = new QSplitter(Qt::Horizontal);
//    splitter = new QSplitter(Qt::Vertical);
//    splitter->addWidget(editor1);
//    splitter->addWidget(editor2);
//    splitter->addWidget(editor3);

//    setCentralWidget(splitter);


//    openglWidget = new QOpenGLWidget_World(this);
//    openglWidget->resize(ui->centralWidget->size());
//    openglWidget->setFocus();

//    openglWidget->resize(openglWidget->sizeHint());

//    setCentralWidget(openglWidget);

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
