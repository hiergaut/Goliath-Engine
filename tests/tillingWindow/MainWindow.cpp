#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

#include <QTextEdit>
//#include <QSplitterHandle>
#include <QMetaType>
//#include <Gui/TillingWindow/QSplitterNode.h>

#include <QVariant>
Q_DECLARE_METATYPE(QList<QList<int>>);
//Q_DECLARE_METATYPE(Qt::Orientation);

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaTypeStreamOperators<QList<int>>("QList<int>");
//    qRegisterMetaTypeStreamOperators<Qt::Orientation>("Qt::Orientation");

    //    QSurfaceFormat format;
    //    format.setVersion(3, 3);
    //    format.setProfile(QSurfaceFormat::CoreProfile);
    //    format.setDepthBufferSize(24);
    //    format.setSamples(4);
    //    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    //    ui->splitter_root->setup();
    //    ui->splitter_root->loadSetting();
//    ui->splitter_root->setup();

//    ui->splitter_root->setParent(ui->splitter_root);

//    ui->splitter_root->loadSetting();
    setCentralWidget(ui->splitter_root);
    ui->splitter_root->setFocus();


    //    QTextEdit * editor1 = new QTextEdit;
    //    QTextEdit * editor2 = new QTextEdit;
    //    QTextEdit * editor3 = new QTextEdit;

    ////    splitter = new QSplitter(Qt::Horizontal);
    //    splitter = new QSplitter(Qt::Vertical);
    //    splitter->addWidget(editor1);
    //    splitter->addWidget(editor2);
    //    splitter->addWidget(editor3);

//    node = new QSplitterNode;

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

void MainWindow::on_actionQuit_triggered()
{
    ui->splitter_root->saveSetting();
//    std::cout << std::flush;
    QCoreApplication::quit();
}

void MainWindow::keyPressEvent(QKeyEvent *) {
    qDebug() << this << ": keyPressEvent";

}


void MainWindow::focusInEvent(QFocusEvent *ev) {
    qDebug() << this << ": focusInEvent";

}
