#ifndef AXIS_H
#define AXIS_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <opengl/version.h>
#include <opengl/shader.h>

class Axis {
public:
    Axis() {
        glm::vec3 origin(0.0);
        glm::vec3 x(1.0, 0, 0);
        glm::vec3 y(0.0, 1.0, 0.0);
        glm::vec3 z(0.0, 0.0, 1.0);

        m_vertices.push_back(origin);
        m_vertices.push_back(x);

        m_vertices.push_back(origin);
        m_vertices.push_back(y);

        m_vertices.push_back(origin);
        m_vertices.push_back(z);

        fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();
        setup();


        m_shader = new Shader(shaderPath + "axis.vsh", shaderPath + "axis.fsh");


        m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
//        m_projection = glm::perspective(1.0f, 1.0f, 0.1f, 100.0f);

    }


    void draw(glm::mat4 view) {
        m_shader->use();
        m_shader->setMat4("view", glm::mat4(glm::mat3(view)));
//        m_shader->setMat4("view", view);
        m_shader->setMat4("projection", m_projection);
//        m_shader->setMat4("projection", projection);

        fun->glBindVertexArray(m_vao);
        fun->glDrawArrays(GL_LINES, 0, m_vertices.size());
        fun->glBindVertexArray(0);

    }

private:
    void setup() {
        unsigned int vbo;
        fun->glGenVertexArrays(1, &m_vao);
        fun->glGenBuffers(1, &vbo);

        fun->glBindVertexArray(m_vao);
        fun->glBindBuffer(GL_ARRAY_BUFFER, vbo);

        fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

        fun->glEnableVertexAttribArray(0);
        fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        fun->glBindVertexArray(0);
    }

private:
    std::vector<glm::vec3> m_vertices;
    unsigned int m_vao;
    Shader * m_shader;
    glm::mat4 m_projection;


    QOpenGLFunctionsCore * fun;

};

#endif // AXIS_H
