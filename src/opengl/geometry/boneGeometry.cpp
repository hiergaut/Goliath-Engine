#include "boneGeometry.h"

BoneGeometry::BoneGeometry()
    : m_sphere(10)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    m_vertices.push_back(glm::vec3(0, 0, 0));
    m_vertices.push_back(glm::vec3(10, 10, 10));

    setup();

//    m_shader = new Shader("bone.vsh", "bone.fsh");
}

void BoneGeometry::setup()
{
//    m_fun->glGenVertexArrays(1, &m_vao);
//    uint vbo;
//    m_fun->glGenBuffers(1, &vbo);

//    m_fun->glBindVertexArray(m_vao);
//    m_fun->glBindBuffer(GL_ARRAY_BUFFER, vbo);


//    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

//    m_fun->glEnableVertexAttribArray(0);
//    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

//    m_fun->glBindVertexArray(0);

}

void BoneGeometry::draw(const Shader & shader, glm::vec3 source, glm::vec3 destination) const
{
//    shader.use();
//    m_shader->use();

    m_sphere.draw();


//    m_fun->glBindVertexArray(m_vao);
//    m_fun->glDrawArrays(GL_LINES, 0, m_vertices.size());
//    m_fun->glBindVertexArray(0);

}
