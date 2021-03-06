#ifndef SKYBOXGEOMETRY_H
#define SKYBOXGEOMETRY_H


#include <opengl/version.h>


class SkyBoxGeometry
{
public:

    static void initializeGL();

    static void draw();


private:
    static QOpenGLFunctionsCore * m_fun;

    static uint m_vao;

private:
};


#endif // SKYBOXGEOMETRY_H
