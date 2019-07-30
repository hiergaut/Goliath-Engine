#ifndef VERSION_H
#define VERSION_H

#include <QOpenGLFunctions_3_3_Core>

//QOpenGLFunctions_3_3_Core * gl = new QOpenGLFunctions_3_3_Core;
//gl->initializeOpenGLFunctions();
//QOpenGLVersionProfile g_versionProfile(Q)
using QOpenGLFunctionsCore = QOpenGLFunctions_3_3_Core;

static std::string g_resourcesPath = "../../../Goliath-Engine/resources/";
static std::string g_shaderPath = g_resourcesPath + "shader/";

//#define RESOURCES_PATH ../../../Goliath-Engine/resources/

#endif // VERSION_H
