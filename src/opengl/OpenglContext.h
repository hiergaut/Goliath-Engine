#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include <opengl/version.h>
#include <QOpenGLContext>
//#include <QOpenGLContext>


class OpenglContext
{
public:
//    QOpenGLFunctionsCore * m_fun;
    QOpenGLContext * m_context;
public:
    OpenglContext();
};

//extern OpenglContext * g_openglContext;
extern QOpenGLContext * g_ctx;

//extern QOpenGLContext * g_context;
//extern QOpenGLFunctionsCore * g_fun;

#endif // OPENGLCONTEXT_H
