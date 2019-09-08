#include "TriangleGeometry.h"

//TriangleGeometry::TriangleGeometry()
//{

//}

#include <glm/gtc/matrix_transform.hpp>

QOpenGLFunctionsCore* TriangleGeometry::m_fun = nullptr;
uint TriangleGeometry::m_vao;
uint TriangleGeometry::m_vbo;


void TriangleGeometry::initializeGL()
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    //    float radius = 0.1;
    //    float max = 0.3;
    std::vector<glm::vec3> m_vertices;
    m_vertices.resize(MAX_TRIANGLES * 3);
//    std::vector<glm::vec3> m_normals;

//    m_vertices.push_back(glm::vec3(-1, 0, 0));
//    m_vertices.push_back(glm::vec3(1, 0, 0));
//    m_vertices.push_back(glm::vec3(0, 1, 0));

//    std::vector<glm::uvec2> m_indices;
//    m_indices.emplace_back(0, 1);
//    m_indices.emplace_back(1, 2);
//    m_indices.emplace_back(2, 0);

//    m_normals.push_back(glm::vec3(-1, -1, 0));
//    m_normals.push_back(glm::vec3(1, -1, 0));
//    m_normals.push_back(glm::vec3(0, 1, 0));

    m_fun->glGenVertexArrays(1, &m_vao);
    //    uint vbo;
    //    uint m_vbo;
    m_fun->glGenBuffers(1, &m_vbo);
    //    m_fun->glGenBuffers(1, &m_ebo);
    uint m_nbo;
    m_fun->glGenBuffers(1, &m_nbo);
//    uint m_ebo;
//    m_fun->glGenBuffers(1, &m_ebo);

    m_fun->glBindVertexArray(m_vao);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(float), &m_vertices[0], GL_STREAM_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
//    m_fun->glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
//    m_fun->glEnableVertexAttribArray(1);
//    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

//    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3), &m_indices[0], GL_STATIC_DRAW);

    //    m_fun->glGenVertexArrays(1, &m_vao2);
    //    m_fun->glBindVertexArray(m_vao2);
    //    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);

    //    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
    //    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesLine.size() * sizeof(glm::uvec2), &m_indicesLine[0], GL_STATIC_DRAW);
    //    m_fun->glEnableVertexAttribArray(1);
    //    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindVertexArray(0);
}
void TriangleGeometry::draw(const std::vector<glm::vec3> & triangles) {
    Q_ASSERT(m_fun != nullptr);
    Q_ASSERT(triangles.size() < MAX_TRIANGLES);

    m_fun->glBindVertexArray(m_vao);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, triangles.size() * 3 * sizeof(float), &triangles[0]);
    //    m_fun->glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr);
    //    m_fun->glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(8 * sizeof(glm::vec3)));
//    m_fun->glDrawArrays(GL_LINES, 0, 2);
    m_fun->glDrawArrays(GL_TRIANGLES, 0, triangles.size());
//    m_fun->glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    //    m_sphere.draw();
}

void TriangleGeometry::draw(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
{
    Q_ASSERT(m_fun != nullptr);
    //    m_shader->use();
    //    glm::mat4 identity(1.0);
    //    glm::vec3 vDir = destination - source;
    //    glm::vec3 vX = glm::vec3(1, 0, 0);

    //    float dirLength = glm::length(vDir);
    //    glm::mat4 m(1);
    //    m = glm::translate(m, source);

    //    //     m = glm::lookAt(source, destination, glm::vec3(0, 0, 1)) * m;
    //    glm::vec3 vRot = glm::cross(vX, vDir);
    //    //    std::cout << "vRot length : " << vRot.length() << std::endl;
    //    if (glm::length(vRot) > 0.01) {
    //        //        vRot = glm::vec3(0, -1, 0);
    //        //    }
    //        //    m = glm::rotate(m, )
    //        glm::vec3 dirUnit = vDir / dirLength;
    //        float angle = glm::acos(glm::dot(dirUnit, vX));

    //        m = glm::rotate(m, angle, vRot);
    glm::vec3 v012[3] { v0, v1, v2 };
    //    }

    //    m = glm::scale(m, glm::vec3(dirLength));

    //    shader.setMat4("model", modelMatrix * m);

    m_fun->glBindVertexArray(m_vao);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v012), v012);
    //    m_fun->glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr);
    //    m_fun->glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(8 * sizeof(glm::vec3)));
//    m_fun->glDrawArrays(GL_LINES, 0, 2);
    m_fun->glDrawArrays(GL_TRIANGLES, 0, 3);
//    m_fun->glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    //    m_sphere.draw();

    //        shader.setMat4("model", m * glm::translate(glm::mat4(1), glm::vec3(1, 0, 0)));
    //    shader.setMat4("model", model * glm::translate(m, glm::vec3(1, 0, 0)));
    //    m_sphere.draw();
    //    glm::translate(m, source);
    //    shader.setMat4("model", glm::translate(m, source));
    //    m_sphere.draw();

    //    //    shader.setMat4("model", m * glm::translate(glm::mat4(1), glm::vec3(1, 0, 0)));
    //    m_shader->setMat4("model", model * glm::translate(m, glm::vec3(1, 0, 0)));
    //    m_sphere.draw();
}
