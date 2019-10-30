#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <vector>
#include <opengl/version.h>
#include <opengl/shader.h>

class SkyBox
{
public:
    SkyBox(std::string author, std::string name);
    unsigned int loadCubemap(std::string author, std::string name);

    void draw(const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);
    void draw(const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix, const glm::vec3 & sunDirection);
    void draw(const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix, uint cubeMap);

private:
    QOpenGLFunctionsCore* m_fun;

    uint m_cubeMap;
    Shader * m_shader;

};

#endif // SKYBOX_H
