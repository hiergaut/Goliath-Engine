#include "MainWindow.h"
//#include "QOpenGLWindow_Application.h"
#include <QApplication>

//#include <QDebug>
#include <QSurfaceFormat>
//#include <opengl/OpenglContext.h>
//#include <opengl/version.h>

//#include <QThread>
//#include <QOpenGLFunctionsCokk>

int main(int argc, char* argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    //    g_openglContext = new OpenglContext;

    //    qDebug() << "[CONTEXT] main : " << QOpenGLContext::globalShareContext();
    QApplication a(argc, argv);


    //    QOpenGLContext::globalShareContext()->
//    QOpenGLFunctionsCore* fun = QOpenGLContext::globalShareContext()->versionFunctions<QOpenGLFunctionsCore>();
//    fun->initializeOpenGLFunctions();

    MainWindow w;
//    QOpenGLWindow_Application w;
//    qDebug() << QThread::currentThreadId() <<"[main][SHARED CONTEXT]" << QOpenGLContext::globalShareContext()->functions();

//    qDebug() << "[main][CONTEXT] " << QOpenGLContext::currentContext()->functions();
    //    qDebug() << "[CONTEXT] main : " << QOpenGLContext::globalShareContext()->extraFunctions();

    //        QOpenGLContext * ctx = QOpenGLContext::currentContext();
    //        qDebug() << "[CONTEXT] mainWindow : " << ctx;

    w.show();
//    w.showSystemBrowser();
//    w.loadFile("temp.dat");

    return a.exec();
}

//#include <cstdlib>
//#include <iostream>
//#include <QApplication>
//#include <QOffscreenSurface>
//#include <QOpenGLContext>
//#include <QOpenGLFunctions_3_3_Core>
//#include <QOpenGLShader>
//#include <QOpenGLShaderProgram>

//int main (int argc, char **argv)
//{
//  try {
//    QApplication app(argc, argv);

//    QSurfaceFormat format;
//    format.setMajorVersion(3);
//    format.setMinorVersion(3);
//    format.setProfile(QSurfaceFormat::CoreProfile);

//    QOpenGLContext gl_ctx;
//    gl_ctx.setFormat(format);
//    if (!gl_ctx.create())
//      throw std::runtime_error("context creation failed");

//    QOffscreenSurface surface;
//    surface.create();
//    gl_ctx.makeCurrent(&surface);

//    QOpenGLFunctions_3_3_Core opengl_functions;
//    if (!opengl_functions.initializeOpenGLFunctions())
//      throw std::runtime_error("initialization failed");

//    QOpenGLShader vertex_shader(QOpenGLShader::Vertex);
//    if (!vertex_shader.compileSourceCode(
//          "#version 330 core\n"
//          "\n"
//          "void main ()\n"
//          "{\n"
//          "  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n"
//          "}\n"
//          )) {
//      throw std::runtime_error("vertex shader compilaton failed");
//    }

//    QOpenGLShader fragment_shader(QOpenGLShader::Fragment);
//    if (!fragment_shader.compileSourceCode(
//          "#version 330 core\n"
//          "\n"
//          "layout(location = 0) out vec4 colour;\n"
//          "\n"
//          "void main ()\n"
//          "{\n"
//          "  colour = vec4(0.0, 0.0, 0.0, 1.0);\n"
//          "}\n"
//          )) {
//      throw std::runtime_error("fragment shader compilaton failed");
//    }

//    QOpenGLShaderProgram program;
//    if (!program.addShader(&vertex_shader))
//      throw std::runtime_error("failed to add vertex shader to program");
//    if (!program.addShader(&fragment_shader))
//      throw std::runtime_error("failed to add fragment shader to program");
//    if (!program.link())
//      throw std::runtime_error("failed to link failed");
//    if (!program.bind())
//      throw std::runtime_error("glUseProgram failed");

//    app.exec();
//  }
//  catch (std::exception &ex) {
//    std::clog << "\n" << ex.what();
//  }
//  catch (...) {
//    std::clog << "\nunrecognized exception";
//  }
//  exit(0);
//}
