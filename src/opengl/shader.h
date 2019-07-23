#ifndef SHADER_H
#define SHADER_H

#include "editor/version.h"

//#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int ID;
    QOpenGLFunctionsCore * fun;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader() {}

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {
        fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
//        initializeOpenGLFunctions();

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            std::stringstream vShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ " << vertexPath << std::endl;
            exit(0);
        }
        try {
            // open files
            fShaderFile.open(fragmentPath);
            std::stringstream fShaderStream;
            // read file's buffer contents into streams
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            fShaderFile.close();
            // convert stream into string
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
            if (geometryPath != nullptr) {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ " << fragmentPath << std::endl;
            exit(0);
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = fun->glCreateShader(GL_VERTEX_SHADER);
        fun->glShaderSource(vertex, 1, &vShaderCode, NULL);
        fun->glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = fun->glCreateShader(GL_FRAGMENT_SHADER);
        fun->glShaderSource(fragment, 1, &fShaderCode, NULL);
        fun->glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (geometryPath != nullptr) {
            const char* gShaderCode = geometryCode.c_str();
            geometry = fun->glCreateShader(GL_GEOMETRY_SHADER);
            fun->glShaderSource(geometry, 1, &gShaderCode, NULL);
            fun->glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        ID = fun->glCreateProgram();
        fun->glAttachShader(ID, vertex);
        fun->glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
            fun->glAttachShader(ID, geometry);
        fun->glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        fun->glDeleteShader(vertex);
        fun->glDeleteShader(fragment);
        if (geometryPath != nullptr)
            fun->glDeleteShader(geometry);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        fun->glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value)
    {
        fun->glUniform1i(fun->glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value)
    {
        fun->glUniform1i(fun->glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value)
    {
        fun->glUniform1f(fun->glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value)
    {
        fun->glUniform2fv(fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y)
    {
        fun->glUniform2f(fun->glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value)
    {
        fun->glUniform3fv(fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z)
    {
        fun->glUniform3f(fun->glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value)
    {
        fun->glUniform4fv(fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        fun->glUniform4f(fun->glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat)
    {
        fun->glUniformMatrix2fv(fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat)
    {
        fun->glUniformMatrix3fv(fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat)
    {
        fun->glUniformMatrix4fv(fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            fun->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                fun->glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            fun->glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                fun->glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif
