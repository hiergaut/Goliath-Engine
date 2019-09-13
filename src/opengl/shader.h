#ifndef SHADER_H
#define SHADER_H

#include "version.h"

//#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int ID;
    QOpenGLFunctionsCore* m_fun;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    //    Shader() {}
    enum Type {
        //        WIRE_FRAME = 0,
        SOLID = 0,
        LOOK_DEV,
        RENDERED,
        NORMAL,
        DEPTH,
        VERTEX_GROUP,
        size
    } m_shade;

    static Shader* m_shaders[Shader::Type::size];

    static void glInitialize();

    //    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    Shader(const std::string vertexPath, const std::string fragmentPath, const std::string geometryPath = "", Shader::Type shade = Shader::Type::size);

    ~Shader();
    // activate the shader
    // ------------------------------------------------------------------------
    void use() const;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type);
};
#endif
