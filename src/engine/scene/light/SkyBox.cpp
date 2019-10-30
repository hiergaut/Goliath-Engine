#include "SkyBox.h"

#include <image/stb_image.h>
#include <opengl/geometry/SkyBoxGeometry.h>

SkyBox::SkyBox(std::string author, std::string name)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

//    unsigned int cubemapTexture = loadCubemap(faces);
    m_cubeMap = loadCubemap(author, name);
    m_shader = new Shader("skybox.vsh", "skybox.fsh");
}

unsigned int SkyBox::loadCubemap(std::string author, std::string name)
{
    std::vector<std::string> faces
    {
        "ft.",
        "bk.",
        "up.",
        "dn.",
        "rt.",
        "lf.",
    };

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
//    std::string extension = "jpg";
    std::string extension = "tga";
    for (unsigned int i = 0; i < faces.size(); i++) {
        std::string path = g_resourcesPath + "models/light/skyBox/" + author + "_" + name + "/" + name + "_";

        unsigned char* data = stbi_load((path + faces[i] + extension).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << path + faces[i] + extension << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void SkyBox::draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
//    glDepthFunc(GL_ALWAYS);
    m_shader->use();
    m_shader->setBool("debug", false);
//    glm::mat4 localTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * 100.0f);
//    glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f) * 1.0f);
//    m_shader->setMat4("view", viewMatrix * localTransform);
    m_shader->setMat4("view", glm::mat4(glm::mat3(viewMatrix)));
//    m_shader->setMat4("view", glm::rotate(glm::mat4(glm::mat3(viewMatrix)), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_shader->setMat4("projection", projectionMatrix);

    m_shader->setInt("skybox", 0);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);
    SkyBoxGeometry::draw();
    glDepthFunc(GL_LESS);

    glDepthMask(GL_TRUE);

}

void SkyBox::draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix, const glm::vec3 &sunDirection)
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
//    glDepthFunc(GL_ALWAYS);
    m_shader->use();
    m_shader->setBool("debug", false);
//    glm::mat4 localTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * 100.0f);
//    glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f) * 1.0f);
//    m_shader->setMat4("view", viewMatrix * localTransform);
    m_shader->setMat4("view", glm::mat4(glm::mat3(viewMatrix)));
//    m_shader->setMat4("view", glm::rotate(glm::mat4(glm::mat3(viewMatrix)), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_shader->setMat4("projection", projectionMatrix);

    m_shader->setVec3("lightDir", sunDirection);

    m_shader->setInt("skybox", 0);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);
    SkyBoxGeometry::draw();
    glDepthFunc(GL_LESS);

    glDepthMask(GL_TRUE);


}

void SkyBox::draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix, uint cubeMap)
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
//    glDepthFunc(GL_ALWAYS);
    m_shader->use();
    m_shader->setBool("debug", true);
//    glm::mat4 localTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * 100.0f);
//    glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f) * 1.0f);
//    m_shader->setMat4("view", viewMatrix * localTransform);
    m_shader->setMat4("view", glm::mat4(glm::mat3(viewMatrix)));
//    m_shader->setMat4("view", glm::rotate(glm::mat4(glm::mat3(viewMatrix)), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    m_shader->setMat4("projection", projectionMatrix);

    m_shader->setInt("skybox", 0);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
    SkyBoxGeometry::draw();
    glDepthFunc(GL_LESS);

    glDepthMask(GL_TRUE);


}
