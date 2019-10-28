#ifndef CUBEMAPGEOMETRY_H
#define CUBEMAPGEOMETRY_H


#include <opengl/version.h>

#include <opengl/shader.h>

class CubeMapGeometry
{
public:

    static void initializeGL();

    static void draw();


private:
    static QOpenGLFunctionsCore * m_fun;

    static uint m_vao;
//    static Shader * m_shader;

};



#endif // CUBEMAPGEOMETRY_H
