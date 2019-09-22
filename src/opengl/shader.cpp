
#include "shader.h"

Shader* Shader::m_shaders[Shader::Type::size];

void Shader::glInitialize()
{
    m_shaders[Shader::Type::SOLID] = new Shader("shading/solid.vsh", "shading/solid.fsh", "", Shader::Type::SOLID);
    m_shaders[Shader::Type::LOOK_DEV] = new Shader("shading/lookDev.vsh", "shading/lookDev.fsh", "", Shader::Type::LOOK_DEV);
    m_shaders[Shader::Type::RENDERED] = new Shader("shading/rendered.vsh", "shading/rendered.fsh", "", Shader::Type::RENDERED);
    m_shaders[Shader::Type::NORMAL] = new Shader("shading/normal.vsh", "shading/normal.fsh", "", Shader::Type::NORMAL);
    m_shaders[Shader::Type::DEPTH] = new Shader("shading/depth.vsh", "shading/depth.fsh", "", Shader::Type::DEPTH);
    m_shaders[Shader::Type::VERTEX_GROUP] = new Shader("shading/vertexGroup.vsh", "shading/vertexGroup.fsh", "", Shader::Type::VERTEX_GROUP);
}

//Shader::Shader(const std::string vertexPath, const std::string fragmentPath, Shader::Type shade, const std::string geometryPath)
Shader::Shader(const std::string vertexPath, const std::string fragmentPath, const std::string geometryPath, Shader::Type shade)
    : m_shade(shade)
{
    //        vertexPath = shaderPath + vertexPath;
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
    //        m_fun = fun;
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
        vShaderFile.open(g_shaderPath + vertexPath);
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
        fShaderFile.open(g_shaderPath + fragmentPath);
        std::stringstream fShaderStream;
        // read file's buffer contents into streams
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        fShaderFile.close();
        // convert stream into string
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        //            if (geometryPath != nullptr) {
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ " << fragmentPath << std::endl;
        exit(0);
    }

    if (!geometryPath.empty()) {
        try {
            gShaderFile.open(g_shaderPath + geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::GEOMETRY::FILE_NOT_SUCCESFULLY_READ " << geometryPath << std::endl;
            exit(0);
        }
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = m_fun->glCreateShader(GL_VERTEX_SHADER);
    m_fun->glShaderSource(vertex, 1, &vShaderCode, NULL);
    m_fun->glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = m_fun->glCreateShader(GL_FRAGMENT_SHADER);
    m_fun->glShaderSource(fragment, 1, &fShaderCode, NULL);
    m_fun->glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    //        if (geometryPath != nullptr) {
    if (!geometryPath.empty()) {
        const char* gShaderCode = geometryCode.c_str();
        geometry = m_fun->glCreateShader(GL_GEOMETRY_SHADER);
        m_fun->glShaderSource(geometry, 1, &gShaderCode, NULL);
        m_fun->glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    ID = m_fun->glCreateProgram();
    m_fun->glAttachShader(ID, vertex);
    m_fun->glAttachShader(ID, fragment);
    //        if (geometryPath != nullptr)
    if (!geometryPath.empty())
        m_fun->glAttachShader(ID, geometry);
    m_fun->glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    m_fun->glDeleteShader(vertex);
    m_fun->glDeleteShader(fragment);
    //        if (geometryPath != nullptr)
    if (!geometryPath.empty())
        m_fun->glDeleteShader(geometry);

    //        std::cout << "[SHADER] load : " << vertexPath << std::endl;
}

Shader::~Shader()
{
    std::cout << "\033[31m";
    std::cout << "[SHADER] '" << ID << "' destruct " << this << std::endl;
    std::cout << "\033[0m";
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use() const
{
    m_fun->glUseProgram(ID);
}

void Shader::apply(const Material& material) const
{
    //        setVec3("viewPos", m_camera->position());
    setVec3("material.ambient", material.m_colors[Color::AMBIENT]);
    setVec3("material.diffuse", material.m_colors[Color::DIFFUSE]);
    setVec3("material.specular", material.m_colors[Color::SPECULAR]);
    setFloat("material.shininess", material.m_shininess);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const
{
    m_fun->glUniform1i(m_fun->glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const
{
    m_fun->glUniform1i(m_fun->glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const
{
    m_fun->glUniform1f(m_fun->glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    m_fun->glUniform2fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
    m_fun->glUniform2f(m_fun->glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    m_fun->glUniform3fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    m_fun->glUniform3f(m_fun->glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    m_fun->glUniform4fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    m_fun->glUniform4f(m_fun->glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    m_fun->glUniformMatrix2fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    m_fun->glUniformMatrix3fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    m_fun->glUniformMatrix4fv(m_fun->glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        m_fun->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            m_fun->glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        m_fun->glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            m_fun->glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
