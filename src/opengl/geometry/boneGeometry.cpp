#include "boneGeometry.h"
#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>

BoneGeometry::BoneGeometry()
    : m_sphere(0.05)
{
    m_fun = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctionsCore>();

    float radius = 0.1;
    float max = 0.3;

    m_vertices.push_back(glm::vec3(0, 0, 0));
    m_vertices.push_back(glm::vec3(1, 0, 0));
    m_vertices.push_back(glm::vec3(max, 0, -radius));
    m_vertices.push_back(glm::vec3(max, -radius, 0));
    m_vertices.push_back(glm::vec3(max, 0, radius));
    m_vertices.push_back(glm::vec3(max, radius, 0));

    float root2 = sqrtf(2) / 2;
    m_normals.push_back(glm::vec3(-1, 0, 0));
    m_normals.push_back(glm::vec3(1, 0, 0));
    m_normals.push_back(glm::vec3(0, 0, -1));
    m_normals.push_back(glm::vec3(0, -1, 0));
    m_normals.push_back(glm::vec3(0, 0, 1));
    m_normals.push_back(glm::vec3(0, 1, 0));

    m_indices.emplace_back(0, 4, 5);
    m_indices.emplace_back(0, 3, 4);
    m_indices.emplace_back(0, 2, 3);
    m_indices.emplace_back(0, 5, 2);

    m_indices.emplace_back(5, 4, 1);
    m_indices.emplace_back(4, 3, 1);
    m_indices.emplace_back(3, 2, 1);
    m_indices.emplace_back(2, 5, 1);

    //        assert(m_indices.size() == 8);

    setup();

    //    m_shader = new Shader("bone.vsh", "bone.fsh");
}

void BoneGeometry::setup()
{
    m_fun->glGenVertexArrays(1, &m_vao);
    //    uint vbo;
    m_fun->glGenBuffers(1, &m_vbo);
    m_fun->glGenBuffers(1, &m_ebo);
    m_fun->glGenBuffers(1, &m_nbo);

    m_fun->glBindVertexArray(m_vao);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
    m_fun->glEnableVertexAttribArray(0);
    m_fun->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
    m_fun->glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
    m_fun->glEnableVertexAttribArray(1);
    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    m_fun->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3), &m_indices[0], GL_STATIC_DRAW);
    //    m_fun->glEnableVertexAttribArray(1);
    //    m_fun->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    m_fun->glBindVertexArray(0);
}

void BoneGeometry::draw(glm::mat4 model, const Shader& shader, glm::vec3 source, glm::vec3 destination) const
{
    //    shader.use();
    //    m_shader->use();
    glm::mat4 identity(1.0);
    glm::vec3 vDir = destination - source;
    glm::vec3 vX = glm::vec3(1, 0, 0);

    float dirLength = glm::length(vDir);
    glm::mat4 m(1);
        m = glm::translate(m, source);

    glm::vec3 vRot = glm::cross(vX, vDir);
//    std::cout << "vRot length : " << vRot.length() << std::endl;
    if (glm::length(vRot) > 0.01) {
        //        vRot = glm::vec3(0, -1, 0);
        //    }
        //    m = glm::rotate(m, )
        glm::vec3 dirUnit = vDir / dirLength;
        float angle = glm::acos(glm::dot(dirUnit, vX));

        m = glm::rotate(m, angle, vRot);
    }

    m = glm::scale(m, glm::vec3(dirLength));

    shader.setMat4("model", model * m);

    m_fun->glBindVertexArray(m_vao);
    //    m_fun->glDrawArrays(GL_LINES, 0, m_vertices.size());
    m_fun->glDrawElements(GL_TRIANGLES, m_indices.size() * 3, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    //    glm::translate(m, source);
    //    shader.setMat4("model", glm::translate(m, source));
    m_sphere.draw();

    //    shader.setMat4("model", m * glm::translate(glm::mat4(1), glm::vec3(1, 0, 0)));
    shader.setMat4("model", model * glm::translate(m, glm::vec3(1, 0, 0)));
    m_sphere.draw();
}
