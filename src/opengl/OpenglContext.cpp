#include "OpenglContext.h"

#include <opengl/version.h>
#include <QtDebug>
#include <QOpenGLContext>

QOpenGLContext * g_ctx;
//OpenglContext * g_openglContext;
//QOpenGLContext * g_context;
//QOpenGLFunctionsCore * g_fun;

OpenglContext::OpenglContext()
{
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setSamples(4);
//    QSurfaceFormat::setDefaultFormat(format);


    m_context = new QOpenGLContext;
    m_context->setFormat(format);
//    QOpenGLContext::create();
    m_context->create();

    qDebug() << "[CONTEXT] global : " << m_context;


//    QOpenGLContext context(this);
//    setFormat(format);
//    create();
//    if (!create())
//        throw std::runtime_error("context creation failed");

    //    QOpenGLContext::create(this);
//    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//    fun = new QOpenGLFunctionsCore;
//    fun->initializeOpenGLFunctions();
//    fun->initializeOpenGLFunctions();
//    m_fun = versionFunctions<QOpenGLFunctionsCore>();
//    m_fun->initializeOpenGLFunctions();


}
