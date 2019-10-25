#ifndef VERSION_H
#define VERSION_H

#include <QOpenGLFunctions_4_1_Core>

//QOpenGLFunctions_3_3_Core * gl = new QOpenGLFunctions_3_3_Core;
//gl->initializeOpenGLFunctions();
//QOpenGLVersionProfile g_versionProfile(Q)
using QOpenGLFunctionsCore = QOpenGLFunctions_4_1_Core;

static std::string g_resourcesPath = "../../../Goliath-Engine/resources/";
//static std::string g_resourcesPath = "../../resources/";
static std::string g_shaderPath = g_resourcesPath + "shader/";

//#include <ope
//#define GL_GLEXT_PROTOTYPES 1
//#include <GL/gl.h>
//#include <GL/glext.h>


//#include "CameraWorld.h"
//static std::vector<CameraWorld*> * g_cameras;

//#include <gui/editor/3dview/QOpenGLWidget_3dView.h>
//static std::list<QOpenGLWidget_3dView *> g_views;
//#include <list>
//static std::list<QOpenGLWidget_3dView> * m_views = nullptr;

//#define RESOURCES_PATH ../../../Goliath-Engine/resources/

#endif // VERSION_H
