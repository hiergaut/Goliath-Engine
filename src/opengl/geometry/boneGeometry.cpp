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

    //    m_indicesLine.emplace_back(0, 1);
    m_indices.emplace_back(0, 1, 0);

    //        assert(m_indices.size() == 8);

    setup();

    m_shader = new Shader("bone.vsh", "bone.fsh");
    m_shader->use();
    m_shader->setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
//    m_shader->setVec3("material.diffuse", 0.3f, 0.3f, 0.3f);
    m_shader->setVec3("material.specular", 1.0f, 1.0f, 0.5f);
    m_shader->setFloat("material.shininess", 1.0f);
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

void BoneGeometry::draw(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const
{
    //    m_shader->use();
//    m_shader->setBool("isSkeleton", false);
    //    shader.use();
    //    m_shader->use();
    //    shader.use();

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

    m_shader->setMat4("model", model * m);

    m_fun->glBindVertexArray(m_vao);
    //    m_fun->glDrawArrays(GL_LINES, 0, m_vertices.size());
    m_fun->glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr);
    m_fun->glBindVertexArray(0);

    //    glm::translate(m, source);
    //    shader.setMat4("model", glm::translate(m, source));
    m_sphere.draw();

    //    shader.setMat4("model", m * glm::translate(glm::mat4(1), glm::vec3(1, 0, 0)));
    m_shader->setMat4("model", model * glm::translate(m, glm::vec3(1, 0, 0)));
    m_sphere.draw();
}

void BoneGeometry::drawLine(glm::mat4 model, glm::vec3 source, glm::vec3 destination) const
{
//    m_shader->setBool("isSkeleton", false);

    glm::mat4 identity(1.0);
    glm::vec3 vDir = destination - source;
    glm::vec3 vX = glm::vec3(1, 0, 0);

    float dirLength = glm::length(vDir);
    glm::mat4 m(1);
    m = glm::translate(m, source);

    //     m = glm::lookAt(source, destination, glm::vec3(0, 0, 1)) * m;
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

    m_shader->setMat4("model", model * m);

    m_fun->glBindVertexArray(m_vao);
//    m_fun->glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr);
    m_fun->glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(8 * sizeof(glm::vec3)));
    m_fun->glBindVertexArray(0);

    //    m_sphere.draw();

    //        shader.setMat4("model", m * glm::translate(glm::mat4(1), glm::vec3(1, 0, 0)));
    //    shader.setMat4("model", model * glm::translate(m, glm::vec3(1, 0, 0)));
    //    m_sphere.draw();
}

//void BoneGeometry::setVP(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const
//{
//    m_shader->use();
//    m_shader->setMat4("view", viewMatrix);
//    m_shader->setMat4("projection", projectionMatrix);
//}

void BoneGeometry::updateShader(const MainWindow3dView &view) const
{
    m_shader->use();
    m_shader->setMat4("view", view.viewMatrix());
    m_shader->setMat4("projection", view.projectionMatrix());

    m_shader->setVec3("viewPos", view.camera()->position());
}
