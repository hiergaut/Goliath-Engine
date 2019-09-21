#ifndef DOTGEOMETRY_H
#define DOTGEOMETRY_H

#include <glm/glm.hpp>
#include <opengl/shader.h>
#include <opengl/version.h>


class DotGeometry
{
public:
//    DotGeometry();
    static void initializeGL();

//    static void draw(const glm::mat4& modelMatrix, const Shader& shader, glm::vec3 source, glm::vec3 destination);
    //    void drawLine(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const;

    //    void setVP(const glm::mat4 & viewMatrix, const glm::mat4 &projectionMatrix) const;

    static void draw(const glm::mat4 &modelMatrix, const Shader &shader, const glm::vec4 & color = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f), const float size = 5.0f);
private:
    static QOpenGLFunctionsCore* m_fun;

    //    UvSphereGeometry m_sphere;

    static uint m_vao;
    //    uint m_vao2;

    //    uint m_vbo;
};

#endif // DOTGEOMETRY_H
