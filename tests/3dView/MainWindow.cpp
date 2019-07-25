#include "MainWindow.h"
#include "ui_MainWindow.h"

//#include <QTextEdit>
//#include <QSplitterHandle>
//#include <QMetaType>
//#include <Gui/TillingWindow/QSplitterNode.h>
#include <gui/editor/3dview/QOpenGLWidget_3dView.h>

//#include <QVariant>
//Q_DECLARE_METATYPE(QList<QList<int>>);
//Q_DECLARE_METATYPE(Qt::Orientation);

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //    qRegisterMetaTypeStreamOperators<QList<int>>("QList<int>");
    //    qRegisterMetaTypeStreamOperators<Qt::Orientation>("Qt::Orientation");

    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    //    openglWidget = new QOpenGLWidget_World(this);

    QOpenGLWidget_3dView* widget = new QOpenGLWidget_3dView(this);
    setCentralWidget(widget);
    widget->setFocus();

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

//void MainWindow::focusInEvent(QFocusEvent *)
//{

//}

//void MainWindow::on_actionQuit_triggered()
//{
//    ui->splitter_root->saveSetting();
////    std::cout << std::flush;
//    QCoreApplication::quit();
//}
